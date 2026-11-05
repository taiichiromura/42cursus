#include "Server.hpp"
#include "Utils.hpp"


void Server::registerCgiPipes(int clientFd, Client* client) {
  struct epoll_event ev;

  int outFd = client->getCgiOutFd();
  if (outFd != -1) {
    std::memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLIN;
    ev.data.fd = outFd;
    epoll_ctl(this->_epollfd, EPOLL_CTL_ADD, outFd, &ev);
    this->_cgiFdToClientFd[outFd] = clientFd;
  }

  int inFd = client->getCgiInFd();
  if (inFd != -1) {
    std::memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLOUT;
    ev.data.fd = inFd;
    epoll_ctl(this->_epollfd, EPOLL_CTL_ADD, inFd, &ev);
    this->_cgiFdToClientFd[inFd] = clientFd;
  }
}
void Server::handleCgiOutput(int current_fd,
                             std::map<int, Client>::iterator it) {
  char buf[65536];
  ssize_t readnum = read(current_fd, buf, sizeof(buf));

  if (readnum > 0) {
    it->second.appendCgiOutput(buf, readnum);
    it->second.setCgiLastActivity(time(NULL));
    return ;
  }
  this->finishCgiOutput(current_fd, it);
  return ;
}

bool Server::finishCgiOutput(int current_fd,
                             std::map<int, Client>::iterator it) {
  bool exitedOk = this->reapCgiProcess(current_fd, it);

  std::string full_response;
  if (!exitedOk) {
    full_response =
        "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n";
  } else {
    full_response = this->buildCgiResponse(it->second.getCgiOutput());
  }
  it->second.setResponseStr(full_response);

  std::string tmp;
  tmp.swap(it->second.getCgiOutput());

  this->modMonitorEpollout(it->first);
  return true;
}


bool Server::reapCgiProcess(int current_fd,
                            std::map<int, Client>::iterator it) {
  int status;
  waitpid(it->second.getCgiPid(), &status, 0);

  epoll_ctl(this->_epollfd, EPOLL_CTL_DEL, current_fd, NULL);
  close(current_fd);
  this->_cgiFdToClientFd.erase(current_fd);
  it->second.setIsCgiRunning(false);

  return WIFEXITED(status) && WEXITSTATUS(status) == 0;
}

std::string Server::buildCgiResponse(const std::string& cgi_output) {
  size_t delimiter = cgi_output.find("\r\n\r\n");
  size_t offset = 4;
  if (delimiter == std::string::npos) {
    delimiter = cgi_output.find("\n\n");
    offset = 2;
  }

  std::string cgi_headers;
  if (delimiter != std::string::npos)
    cgi_headers = cgi_output.substr(0, delimiter);

  size_t body_start = (delimiter != std::string::npos) ? delimiter + offset : 0;
  size_t body_len = cgi_output.size() - body_start;

  std::string statusLine = "200 OK";
  std::string filteredHeaders;
  std::stringstream headerStream(cgi_headers);
  std::string line;
  while (std::getline(headerStream, line)) {
    if (!line.empty() && line[line.size() - 1] == '\r')
      line.erase(line.size() - 1);
    if (line.compare(0, 8, "Status: ") == 0)
      statusLine = line.substr(8);
    else if (!line.empty())
      filteredHeaders += line + "\r\n";
  }

  std::stringstream ss;
  ss << "HTTP/1.1 " << statusLine << "\r\n";
  if (!filteredHeaders.empty())
    ss << filteredHeaders;
  else
    ss << "Content-Type: text/html\r\n";
  ss << "Content-Length: " << body_len << "\r\n\r\n";

  std::string full_response = ss.str();
  full_response.append(cgi_output, body_start, body_len);
  return full_response;
}

void Server::handleCgiInput(int current_fd,
                            std::map<int, Client>::iterator it) {
  std::string& body = it->second.getBody();
  size_t already_written = it->second.getBodyBytesWritten();

  if (already_written >= body.size()) {
     this->finishCgiInput(current_fd, it);
     return ;
  }
  ssize_t writenum = write(current_fd, body.c_str() + already_written,
                           body.size() - already_written);
  if (writenum <= 0) {
    this->closeCgiInPipe(current_fd, it);
    return ;
  }
  already_written += writenum;
  it->second.addBodyBytesWritten(writenum);

  if (already_written >= body.size()) {
    this->finishCgiInput(current_fd, it);
    return ;
  }

  return ;
}

bool Server::finishCgiInput(int current_fd,
                            std::map<int, Client>::iterator it) {
  this->closeCgiInPipe(current_fd, it);
  std::string tmp;
  tmp.swap(it->second.getBody());
  return true;
}

void Server::closeCgiInPipe(int current_fd,
                            std::map<int, Client>::iterator it) {
  epoll_ctl(this->_epollfd, EPOLL_CTL_DEL, current_fd, NULL);
  close(current_fd);
  this->_cgiFdToClientFd.erase(current_fd);
  it->second.setCgiInFd(-1);
}
