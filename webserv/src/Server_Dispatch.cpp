#include "Server.hpp"
#include "Utils.hpp"

// CGI,通常のクライアントソケットの処理
void Server::processClient(int n) {
  int current_fd = this->_events[n].data.fd;

  if (this->isCgiFd(current_fd)) {
    this->dispatchCgiEvent(current_fd);
    return ;
  }

  if (this->_events[n].events & EPOLLIN) {
    this->handleClientRecv(n);
    return ;
  }
  if (this->_events[n].events & EPOLLOUT) {
    this->handleClientSend(n);
    return ;
  }
  return ;
}

bool Server::isCgiFd(int fd) const {
  return this->_cgiFdToClientFd.find(fd) != this->_cgiFdToClientFd.end();
}

void Server::dispatchCgiEvent(int current_fd) {
  std::map<int, int>::iterator cgiIt = this->_cgiFdToClientFd.find(current_fd);
  std::map<int, Client>::iterator it = this->_client.find(cgiIt->second);

  if (it == this->_client.end() || !it->second.getIsCgiRunning()) {
    this->_cgiFdToClientFd.erase(cgiIt);
    return ;
  }
  if (it->second.getCgiOutFd() == current_fd) {
    this->handleCgiOutput(current_fd, it);
    return ;
  }
  if (it->second.getCgiInFd() == current_fd) {
    this->handleCgiInput(current_fd, it);
    return ;
  }

  this->_cgiFdToClientFd.erase(cgiIt);
  return ;
}

void Server::handleClientRecv(int n) {
  int current_fd = this->_events[n].data.fd;

  if (!this->getClientRequest(n))
    return ;

  if (this->client_recv->getPhase() != COMPLETE ||
      this->client_recv->getIsCgiRunning())
    return ;

  this->handleCompletedRequest(n, current_fd);
  return ;
}

bool Server::handleCompletedRequest(int n, int current_fd) {
  Response response;
  response.createResponse(this->client_recv);

  if (this->client_recv->getIsCgiRunning()) {
    this->registerCgiPipes(current_fd, this->client_recv);
    return true;
  }

  this->client_recv->setResponseStr(response.getResponseStr());
  this->setMonitorEpollout(n);
  return true;
}

void Server::handleClientSend(int n) {
  int current_fd = this->_events[n].data.fd;
  Client& curr_client = this->_client[current_fd];

  if (!this->sendResponseChunk(current_fd, curr_client))
    return ;

  if (curr_client.getResponseBytesSent() >= curr_client.getResponseStr().size()) {
    if (curr_client.getCloseAfterSend()) {
      this->closeClient(current_fd);
      return ;
    }
    curr_client.clearForNextRequest();
    this->modMonitorEpollin(current_fd);
  }
  return ;
}

bool Server::sendResponseChunk(int current_fd, Client& curr_client) {
  const std::string& resStr = curr_client.getResponseStr();
  size_t& sent_sum = curr_client.getResponseBytesSent();
  size_t total_send = resStr.size();
  const char* ptr = resStr.c_str();

  ssize_t sent = send(current_fd, ptr + sent_sum, total_send - sent_sum, 0);
  if (sent <= 0) {
    this->closeClient(current_fd);
    return false;
  }
  sent_sum += sent;
  return true;
}
