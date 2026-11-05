#include "Server.hpp"
#include "Utils.hpp"


bool Server::getClientRequest(int n) {
  int fd = this->_events[n].data.fd;
  std::map<int, Client>::iterator it = this->_client.find(fd);
  if (it == this->_client.end()) {
    this->client_recv = NULL;
    this->len_recv = -1;
    return false;
  }
  this->client_recv = &it->second;

  if (!this->receiveIntoClient(fd))
    return false;

  if (this->client_recv->getPhase() == PARSE_HEADER)
    this->parseHeaderPhase();

  if (this->client_recv->getPhase() == PARSE_BODY)
    this->parseBodyPhase();
  return true;
}

bool Server::receiveIntoClient(int fd) {
  std::memset(this->_buffer, 0, sizeof(this->_buffer));
  this->len_recv = recv(fd, this->_buffer, sizeof(this->_buffer) - 1, 0);
  if (this->len_recv <= 0)
  {
    closeClient(fd);
    return false;
  }

  this->client_recv->setRequest(this->_buffer, this->len_recv);
  this->client_recv->setClientLastRequest(time(NULL));
  return true;
}

void Server::parseHeaderPhase() {
  std::string& req = this->client_recv->getRefRequest();

  size_t s = req.find_first_not_of("\r\n");
  if (s == std::string::npos) {
    if (req.find("\r\n\r\n") != std::string::npos) {
      this->client_recv->setStatusCode(400);
      this->client_recv->setPhase(COMPLETE);
    }
	return;
  }

  if (s > 0)
    req = req.substr(s);

  if (req.find("\r\n\r\n") == std::string::npos)
    return;

  if (this->client_recv->parseHeader(req) == 1) {
    this->client_recv->setStatusCode(400);
    this->client_recv->setPhase(COMPLETE);
  } else {
	this->selectVirtualHost();
    this->client_recv->setPhase(PARSE_BODY);
  }
}

void Server::parseBodyPhase() {
  if (this->client_recv->getIsChunked()) {
    this->client_recv->processChunkedRequest(this->client_recv->getRefRequest());
  } else if (!this->client_recv->getFields("Content-Length").empty()) {
    this->client_recv->processNormalBody(this->client_recv->getRefRequest());
  } else if (this->client_recv->getMethod() == "GET" ||
             this->client_recv->getMethod() == "DELETE" ||
             this->client_recv->getMethod() == "HEAD" ||
            this->client_recv->getMethod() == "POST") {
    this->client_recv->setPhase(COMPLETE);
  }
}
