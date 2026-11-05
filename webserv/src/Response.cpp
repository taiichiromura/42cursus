#include "Response.hpp"
#include "Client.hpp"
#include "Utils.hpp"

Response::Response() {
  this->_errorMap[400] = "400 Bad Request";
  this->_errorMap[403] = "403 Forbidden";
  this->_errorMap[404] = "404 Not Found";
  this->_errorMap[405] = "405 Method Not Allowed";
  this->_errorMap[413] = "413 Payload Too Large";
  this->_errorMap[414] = "414 URI Too Long";
  this->_errorMap[500] = "500 Internal Server Error";
  this->_errorMap[501] = "501 Not Implemented";
  this->_errorMap[505] = "505 HTTP Version Not Supported";
}

Response::~Response() {}

std::string Response::buildResponse(Location& loc, std::string& statusCode,
                                    std::string& contentType,
                                    std::string& body) {
  std::string ResponseHtml;
  ResponseHtml = "HTTP/1.1 " + statusCode + "\r\n";
  ResponseHtml += "Content-Type: " + contentType + "\r\n";

  // 405のときは受け入れてるリクエストタイプを提示する
  std::set<std::string> methods = loc.getLimitExcept();
  if (statusCode == "405") {
    ResponseHtml += "Allow: ";
    for (std::set<std::string>::iterator it = methods.begin();
         it != methods.end(); ++it) {
      ResponseHtml += *it;
    }
    ResponseHtml += "\r\n";
  }

  ResponseHtml += "Content-Length: " + ft_to_string(body.size()) + "\r\n\r\n";
  ResponseHtml += body;
  return ResponseHtml;
}

std::string Response::errorResponse(Location& loc, ConfigServer& server,
                                    int errorNum) {
  std::map<int, std::string> errorPageMap = server.getErrorPagesMap();
  std::string root = server.getRoot();
  std::string filePath = root + errorPageMap[errorNum];
  std::string errorCode = this->_errorMap[errorNum];

  std::string body;
  if (!readFileToString(filePath, body) || body.empty())
    body = "<html><body><h1>" + errorCode + "</h1></body></html>";

  std::string contentType = "text/html";
  return this->buildResponse(loc, errorCode, contentType, body);
}

std::string Response::redirect301Response(Client* client, std::string url) {
  std::string response;
  std::string hostname = "Host";
  std::string host = client->getField(hostname);
  if (host[0] == ' ')
    host = host.substr(1);

  response = "HTTP/1.1 301 Moved Permanently\r\n";
  response += "Location:";
  if (url.find("http://") != 0 || url.find("https://") != 0) {
    response += url;
  } else {
    response += "http://";
    response += host;
    response += url;
  }
  response += "\r\n";
  response += "Content-Length: 0\r\n\r\n";
  return response;
}

void Response::createResponse(Client* client) {
  ConfigServer& server = client->getServer();
  Location loc = this->longestPrefixMatch(client->getRequestTarget(),
                                          server.getLocation());

  std::map<int, std::string>::iterator it =
      this->_errorMap.find(client->getStatusCode());
  if (it != _errorMap.end()) {
    this->_response = this->errorResponse(loc, server, client->getStatusCode());
    return;
  }

  std::set<std::string> methods = loc.getLimitExcept();
  std::string client_method = client->getMethod();

  if (methods.size() == 0) {
    methods.insert("GET");
    methods.insert("POST");
    methods.insert("DELETE");
  }

  if (client->getStatusCode() != 200) {
    this->_response = this->errorResponse(loc, server, client->getStatusCode());
    return;
  }

  if (loc.getReturn().first == 301) {
    this->_response = this->redirect301Response(client, loc.getReturn().second);
    return;
  }

  if (methods.find(client_method) == methods.end()) {
    client->setStatusCode(405);
    this->_response = this->errorResponse(loc, server, 405);
    return;
  }

  if (client_method == "POST")
    this->_response = this->postResponse(loc, client);
  else if (client_method == "GET")
    this->_response = this->getResponse(loc, client);
  else if (client_method == "DELETE")
    this->_response = this->deleteResponse(loc, client);
}

const std::string& Response::getResponseStr() const {
  return this->_response;
}

void Response::setResponseStr(const std::string& response) {
  this->_response = response;
}
