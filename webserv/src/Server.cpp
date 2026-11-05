#include "Server.hpp"
#include "Utils.hpp"


Server::Server() : _allServers(NULL), _epollfd(-1) {}

Server::~Server() {
  for (std::set<int>::iterator it = this->_listen_fds.begin();
       it != this->_listen_fds.end(); ++it) {
    close(*it);
  }
  if (this->_epollfd != -1)
    close(this->_epollfd);
}

void Server::selectVirtualHost() {
  if (this->_allServers == NULL)
    return;

  std::string hostHeader = ft_trim(this->client_recv->getFields("Host"));
  std::string hostname = hostHeader.substr(0, hostHeader.find(':'));
  int port = this->client_recv->getServerPort();

  for (size_t i = 0; i < this->_allServers->size(); i++) {
    if ((*this->_allServers)[i].getPort() == port &&
        (*this->_allServers)[i].getServerName() == hostname) {
      this->client_recv->setServer((*this->_allServers)[i]);
      break;
    }
  }
}

std::map<int, Client> Server::getClient() const {
  return this->_client;
}

void Server::createEpollBase() {
  this->_epollfd = epoll_create(1);
  if (this->_epollfd == -1) {
    ft_throw("epoll_create");
  }
}

// ソケットを作って返す
int Server::createSingleListenSocket() {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    ft_throw("In socket");
  }
  int opt = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
  	ft_throw("In setscokopt");
  return sockfd;
}

// 指定されたポート用にアドレスを設定
void Server::setAddrForPort(int port) {
  this->_addr.sin_family = AF_INET;
  this->_addr.sin_addr.s_addr = INADDR_ANY;
  this->_addr.sin_port = htons(port);
  memset(this->_addr.sin_zero, '\0', sizeof this->_addr.sin_zero);
}

// sockfdをbindする
void Server::bindSingleSocket(int sockfd) {
  if (bind(sockfd, (struct sockaddr*)&this->_addr, sizeof(this->_addr)) < 0) {
    ft_throw("In bind");
  }
}

// 指定されたfdをlistenする
void Server::listenSingleSocket(int sockfd) {
  if (listen(sockfd, 128) < 0) {
    ft_throw("In listen");
  }
}

// 指定されたfdをノンブロッキングにする
void Server::fcntlSingleSocket(int sockfd) {
  int flg = fcntl(sockfd, F_GETFL, 0);
  flg |= O_NONBLOCK;
  if (fcntl(sockfd, F_SETFL, flg)) {
    ft_throw("In fcntl");
  }
}

// 指定されたfdをepollに登録する
void Server::addSocketToEpoll(int sockfd) {
  struct epoll_event ev;
  ev.events = EPOLLIN;
  ev.data.fd = sockfd;
  if (epoll_ctl(this->_epollfd, EPOLL_CTL_ADD, sockfd, &ev) == -1) {
    ft_throw("epoll_ctl: add listen sock");
  }
}

void Server::createSocketAndEpoll(
  const std::vector<ConfigServer>& parsed_servers) {
  // 重複のないポートリストをsetで作る
  std::set<int> unique_ports;
  for (size_t i = 0; i < parsed_servers.size(); i++) {
    unique_ports.insert(parsed_servers[i].getPort());
  }

  this->createEpollBase();

  for (std::set<int>::iterator it = unique_ports.begin();
       it != unique_ports.end(); ++it) {
    int port = *it;

    int sockfd = this->createSingleListenSocket();
    this->setAddrForPort(port);
    this->bindSingleSocket(sockfd);
    this->listenSingleSocket(sockfd);
    this->fcntlSingleSocket(sockfd);

    this->_listen_fds.insert(sockfd);
    this->_fd_to_port_map[sockfd] = port;
    this->addSocketToEpoll(sockfd);
  }
}

void Server::checkCgiTimeout() {
  time_t now = time(NULL);
  for (std::map<int, Client>::iterator it = _client.begin();
       it != _client.end(); ++it) {
    if (it->second.getIsCgiRunning() &&
        now - it->second.getCgiLastActivity() >= 10) {
      this->abortCgi(it);
      it->second.setResponseStr(
          "HTTP/1.1 504 Gateway Timeout\r\nContent-Length: 0\r\n\r\n");
      this->modMonitorEpollout(it->first);
    }
  }
}

void Server::checkClientTimeout() {
  time_t now = time(NULL);
  for (std::map<int, Client>::iterator it = _client.begin();
       it != _client.end();) {
    if (now - it->second.getClientLastRequest() >= 60) {
      int fd = it->first;
      ++it;
      this->closeClient(fd);
    } else {
      ++it;
    }
  }
}

void Server::epollWait() {
  this->_nfds = epoll_wait(this->_epollfd, this->_events, MAX_EVENTS, 1000);
  if (this->_nfds == -1) {
    if (errno == EINTR) {
      this->_nfds = 0;
      return;
    }
    ft_throw("epoll_wait");
  }
}

void Server::setSocketNonblocking(int conn_sock) {
  int flgcon = fcntl(conn_sock, F_GETFL, 0);
  flgcon |= O_NONBLOCK;
  if (fcntl(conn_sock, F_SETFL, flgcon)) {
    ft_throw("In fcntl");
  }
}

void Server::setMonitorEpollin(int conn_sock) {
  struct epoll_event ev;
  ev.events = EPOLLIN;
  ev.data.fd = conn_sock;

  if (epoll_ctl(this->_epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1) {
    ft_throw("epoll_ctl ADD(setMonitorEpollin)");
  }
}

void Server::modMonitorEpollin(int conn_sock) {
  struct epoll_event ev;
  ev.events = EPOLLIN;
  ev.data.fd = conn_sock;

  if (epoll_ctl(this->_epollfd, EPOLL_CTL_MOD, conn_sock, &ev) == -1) {
    ft_throw("epoll_ctl MOD->IN(modMonitorEpollin)");
  }
}

void Server::modMonitorEpollout(int conn_sock) {
  struct epoll_event ev;
  ev.events = EPOLLOUT;
  ev.data.fd = conn_sock;

  if (epoll_ctl(this->_epollfd, EPOLL_CTL_MOD, conn_sock, &ev) == -1) {
    ft_throw("epoll_ctl MOD->OUT(modMonitorEpollout)");
  }
}

void Server::connectToListeningSocket(int listen_fd,
                                      std::vector<ConfigServer>& servers) {
  while (true) {
    int conn_sock = this->acceptListeningSocket(listen_fd, servers);
    if (conn_sock == -1)
      break;
    this->setSocketNonblocking(conn_sock);
    this->setMonitorEpollin(conn_sock);
  }
}

void Server::closeClient(int client_fd) {
  std::map<int, Client>::iterator it = this->_client.find(client_fd);
  if (it == this->_client.end())
    return;

  this->abortCgi(it);

  if (epoll_ctl(this->_epollfd, EPOLL_CTL_DEL, client_fd, NULL) == -1)
    ft_throw("epoll_ctl DEL in closeClient");
  close(client_fd);
  this->_client.erase(client_fd);
}

void Server::setMonitorEpollout(int n) {
  int current_fd = this->_events[n].data.fd;

  struct epoll_event ev;
  std::memset(&ev, 0, sizeof(ev));

  ev.events = EPOLLOUT;
  ev.data.fd = current_fd;

  if (epoll_ctl(this->_epollfd, EPOLL_CTL_MOD, current_fd, &ev) == -1) {
    ft_throw("epoll_ctl: MOD to EPOLLOUT failed");
    close(current_fd);
  }
}

// サーバー稼働を開始
void Server::runServer(std::vector<ConfigServer>& servers) {
  for (int n = 0; n < this->_nfds; ++n) {
    int event_fd = this->_events[n].data.fd;
    if (this->_listen_fds.count(event_fd)) {
      this->connectToListeningSocket(event_fd, servers);
      // listening socket以外=clientを受信した場合
    } else {
      this->processClient(n);
    }
  }
}

void Server::run(std::vector<ConfigServer>& servers) {
  this->_allServers = &servers;
  while (!g_shutdown_requested) {
    this->epollWait();
    this->runServer(servers);
    this->checkCgiTimeout();
    this->checkClientTimeout();
  }
}

void Server::abortCgi(std::map<int, Client>::iterator it) {
  Client& client = it->second;
  if (!client.getIsCgiRunning())
    return;

  kill(client.getCgiPid(), SIGKILL);
  waitpid(client.getCgiPid(), NULL, 0);

  int outfd = client.getCgiOutFd();
  int infd = client.getCgiInFd();
  if (outfd != -1) {
    epoll_ctl(this->_epollfd, EPOLL_CTL_DEL, outfd, NULL);
    close(outfd);
    this->_cgiFdToClientFd.erase(outfd);
  }
  if (infd != -1) {
    epoll_ctl(this->_epollfd, EPOLL_CTL_DEL, infd, NULL);
    close(infd);
    this->_cgiFdToClientFd.erase(infd);
  }

  client.setIsCgiRunning(false);
  client.setCgiOutFd(-1);
  client.setCgiInFd(-1);
}
