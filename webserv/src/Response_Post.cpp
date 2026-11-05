#include "Client.hpp"
#include "Response.hpp"
#include "Utils.hpp"

#include <fstream>
#include <sstream>

std::string Response::postResponse(Location& loc, Client* client) {
  ConfigServer& server = client->getServer();

  std::string sizeError = this->checkBodySize(loc, server, client);
  if (!sizeError.empty())
    return sizeError;

  std::string root_path = this->getEffectiveRoot(loc, server);
  std::string request_target = client->getRequestTarget();
  std::string relative = request_target.substr(loc.getLocationPath().size());

  if (relative.empty() || relative == "/")
    return this->buildRootPostResponse(client);

  if (!this->checkFileName(relative))
    return this->errorResponse(loc, server, 400);

  std::string filePath = this->joinRootAndRelative(root_path, relative);

  std::string cgiResponse =
      this->tryCgiPostResponse(loc, client, filePath, relative);
  if (!cgiResponse.empty())
    return cgiResponse;

  return this->writeUploadedFile(loc, server, client, filePath);
}

std::string Response::checkBodySize(Location& loc, ConfigServer& server,
                                    Client* client) {
  if (client->getBody().size() > loc.getClientMaxBodySize())
    return this->errorResponse(loc, server, 413);
  return "";
}

std::string Response::buildRootPostResponse(Client* client) {
  std::string body = client->getBody();
  std::stringstream ss;
  ss << "HTTP/1.1 200 OK\r\n"
     << "Server: Webserv\r\n"
     << "Content-Type: text/plain\r\n"
     << "Content-Length: " << body.size() << "\r\n"
     << "\r\n"
     << body;
  return ss.str();
}

std::string Response::tryCgiPostResponse(Location& loc, Client* client,
                                         const std::string& filePath,
                                         const std::string& relative) {
  std::string filetype = getFileType(relative);
  std::map<std::string, std::string> cgi_map = loc.getCgiHandlersMap();
  std::map<std::string, std::string>::iterator cgi_it = cgi_map.find(filetype);
  if (cgi_it == cgi_map.end())
    return "";

  std::string cgi_path = cgi_it->second;
  std::string body =
      this->cgi.do_cgi_post(cgi_path, filePath, client->getBody(), client);

  std::stringstream ss;
  ss << "HTTP/1.1 200 OK\r\n"
     << "Content-Type: text/plain\r\n"
     << "Content-Length: " << body.size() << "\r\n"
     << "\r\n"
     << body;
  return ss.str();
}

std::string Response::writeUploadedFile(Location& loc, ConfigServer& server,
                                        Client* client,
                                        const std::string& filePath) {
  int fileStatus = is_file_exist_posix(filePath);
  std::string response;

  if (fileStatus == 1) {
    std::ofstream ofs(filePath.c_str());
    if (!ofs.is_open())
      ft_throw("open");
    ofs << client->getBody();
    response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Length: 0\r\n\r\n";
  } else if (fileStatus == -1) {
    std::ofstream ofs(filePath.c_str());
    if (!ofs.is_open())
      ft_throw("open");
    ofs << client->getBody();
    response = "HTTP/1.1 201 Created\r\n";
    response += "Content-Length: 0\r\n\r\n";
  } else if (fileStatus == 0) {
    response = this->errorResponse(loc, server, 403);
  }
  return response;
}
