#include "Client.hpp"
#include "Response.hpp"
#include "Utils.hpp"

#include <dirent.h>
#include <fstream>
#include <sstream>
#include <unistd.h>

std::string Response::getResponse(Location& loc, Client* client) {
  ConfigServer& server = client->getServer();
  std::string request_target = client->getRequestTarget();
  std::string filePath = this->resolveFilePath(loc, client, request_target);

  std::string redirect =
      this->checkDirectoryRedirect(client, filePath, request_target);
  if (!redirect.empty())
    return redirect;

  std::string autoIndex = this->Autoindex(filePath, loc);
  if (autoIndex != "")
    return autoIndex;

  this->resolveIndexFile(loc, request_target, filePath);
  this->normalizeDoubleSlashes(filePath);

  std::string accessError = this->checkFileAccessible(loc, server, filePath);
  if (!accessError.empty())
    return accessError;

  std::ifstream target(filePath.c_str());
  if (!target)
    return this->errorResponse(loc, server, 405);

  std::string cgiResponse =
      this->tryCgiResponse(loc, client, filePath, request_target);
  if (!cgiResponse.empty())
    return cgiResponse;

  if (!target.is_open())
    return this->errorResponse(loc, server, 405);

  return this->buildStaticFileResponse(client, server, filePath, target);
}

std::string Response::resolveFilePath(Location& loc, Client* client,
                                      const std::string& request_target) {
  ConfigServer& server = client->getServer();
  std::string root_path = this->getEffectiveRoot(loc, server);

  std::string path_only = request_target;
  size_t qpos = path_only.find('?');
  if (qpos != std::string::npos)
    path_only = path_only.substr(0, qpos);

  std::string relative = path_only.substr(loc.getLocationPath().size());
  return root_path + relative;
}

std::string
Response::checkDirectoryRedirect(Client* client, const std::string& filePath,
                                 const std::string& request_target) {
  if (this->isDirectory(filePath) &&
      request_target[request_target.size() - 1] != '/') {
    return this->redirect301Response(client, request_target + '/');
  }
  return "";
}

void Response::resolveIndexFile(Location& loc,
                                const std::string& request_target,
                                std::string& filePath) {
  if (request_target.empty() ||
      request_target[request_target.length() - 1] != '/')
    return;

  if (!filePath.empty() && filePath[filePath.length() - 1] != '/')
    filePath += "/";

  if (!loc.getIndex().empty())
    filePath += loc.getIndex();
  else
    filePath += "index.html";
}

void Response::normalizeDoubleSlashes(std::string& filePath) {
  size_t double_slash;
  while ((double_slash = filePath.find("//")) != std::string::npos)
    filePath.replace(double_slash, 2, "/");
}

std::string Response::checkFileAccessible(Location& loc, ConfigServer& server,
                                          const std::string& filePath) {
  if (access(filePath.c_str(), F_OK) == -1)
    return this->errorResponse(loc, server, 404);
  if (access(filePath.c_str(), R_OK) == -1)
    return this->errorResponse(loc, server, 403);
  return "";
}

std::string Response::tryCgiResponse(Location& loc, Client* client,
                                     const std::string& filePath,
                                     const std::string& request_target) {
  std::string filetype = getFileType(filePath);
  std::map<std::string, std::string> cgifile = loc.getCgiHandlersMap();
  std::map<std::string, std::string>::iterator it = cgifile.find(filetype);
  if (it == cgifile.end())
    return "";

  ConfigServer& server = client->getServer();
  if (access(filePath.c_str(), X_OK) == -1)
    return this->errorResponse(loc, server, 403);

  std::string query_string;
  size_t qpos = request_target.find('?');
  if (qpos != std::string::npos)
    query_string = request_target.substr(qpos + 1);

  std::string cgi_path = it->second;
  std::string cgi_output =
      this->cgi.do_cgi(cgi_path, filePath, query_string, client);

  size_t delimiter = cgi_output.find("\r\n\r\n");
  size_t offset = 4;
  if (delimiter == std::string::npos) {
    delimiter = cgi_output.find("\n\n");
    offset = 2;
  }

  std::string cgi_headers;
  std::string cgi_body;
  if (delimiter != std::string::npos) {
    cgi_headers = cgi_output.substr(0, delimiter);
    cgi_body = cgi_output.substr(delimiter + offset);
  } else {
    cgi_body = cgi_output;
  }

  std::stringstream ss;
  ss << "HTTP/1.1 200 OK\r\n";
  if (!cgi_headers.empty())
    ss << cgi_headers << "\r\n";
  ss << "Content-Length: " << cgi_body.size() << "\r\n";
  ss << "\r\n";

  return ss.str() + cgi_body;
}

std::string Response::buildStaticFileResponse(Client* client,
                                              ConfigServer& server,
                                              const std::string& filePath,
                                              std::ifstream& target) {
  std::string body;
  if (target) {
    std::stringstream ss;
    ss << target.rdbuf();
    body = ss.str();
  }

  std::string response = "HTTP/1.1 200 OK\r\n";
  response += "Content-Type: " + this->getContentType(filePath) + "\r\n";
  response += this->buildSessionHeaders(client, server);
  response += "Content-Length: " + ft_to_string(body.size()) + "\r\n\r\n";
  response += body;
  return response;
}

std::string Response::buildSessionHeaders(Client* client,
                                          ConfigServer& server) {
  std::string headers;
  if (!client->getIsCookie()) {
    std::string sessionId = this->generateSessionId();
    Session& s = server.getSession(sessionId);
    s.visitCount = 1;
    headers += "Set-Cookie: session_id=" + sessionId + "; Path=/; HttpOnly\r\n";
    headers += "Visit-Count:" + ft_to_string(s.visitCount) + "\r\n";
  } else {
    server.getSession(client->getSessionId()).visitCount++;
    headers +=
        "Visit-Count:" +
        ft_to_string(server.getSession(client->getSessionId()).visitCount) +
        "\r\n";
  }
  return headers;
}

std::string Response::Autoindex(const std::string& filename, Location& loc) {
  DIR* dir = opendir(filename.c_str());
  if (dir == NULL)
    return "";

  if (!loc.getAutoindex()) {
    closedir(dir);
    return "";
  }

  std::string body;
  body += "<html><head><title>Index of " + filename + "</title></head>";
  body += "<body><h1>Index of " + filename + "</h1><hr><pre>";
  body += "<a href=\"../\">../</a>\n";

  struct dirent* entry;
  while ((entry = readdir(dir)) != NULL) {
    std::string dName = entry->d_name;
    if (dName == "." || dName == "..")
      continue;
    if (this->isDirectory(dName))
      dName += "/";
    body += "<a href=\"" + dName + "\">" + dName + "</a>\n";
  }
  body += "</pre><hr></body></html>";

  closedir(dir);

  std::stringstream ss;
  ss << "HTTP/1.1 200 OK\r\n";
  ss << "Content-Type: text/html\r\n";
  ss << "Content-Length: " << body.size() << "\r\n";
  ss << "\r\n";
  ss << body;

  return ss.str();
}
