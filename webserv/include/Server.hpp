#ifndef SERVER_HPP
#define SERVER_HPP

#include "Client.hpp"
#include "ConfigServer.hpp"
#include "Response.hpp"
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fcntl.h>
#include <netinet/in.h>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

#include <cerrno>
#include <cstdio>
#include <cstdlib>

#include <csignal>
#include <iostream>
#include <sstream>


#define MAX_EVENTS 10

class Server {
private:
  ConfigServer _server;
  std::vector<ConfigServer>* _allServers;
  int _socket;
  bool _sentRequest;
  std::string _request;
  time_t _lastRequest;
  std::string _requestPayload;
  std::string _method;
  std::string _resource;
  size_t _contentLength;
  std::map<int, Client> _client;
  std::map<int, int> _cgiFdToClientFd;
  struct sockaddr_in _addr;
  int _addrLen;
  struct epoll_event _monitor;
  struct epoll_event _events[MAX_EVENTS];
  Response response;
  int _listen_sock;
  int _conn_sock;
  int _nfds;
  int _epollfd;
  ssize_t len_recv;
  Client* client_recv;
  char _buffer[30000];
  std::set<int> _listen_fds;
  std::map<int, int> _fd_to_port_map;

  void createEpollBase();
  int createSingleListenSocket();
  void setAddrForPort(int port);
  void bindSingleSocket(int sockfd);
  void listenSingleSocket(int sockfd);
  void fcntlSingleSocket(int sockfd);
  void addSocketToEpoll(int sockfd);
  void setMonitorEpollout(int n);
  void closeClient(int n);
  bool getClientRequest(int n);
  void connectToListeningSocket(int listen_fd,
                                std::vector<ConfigServer>& servers);
  void setMonitorEpollin(int fd);
  void setSocketNonblocking(int conn_sock);
  int acceptListeningSocket(int listen_fd, std::vector<ConfigServer>& servers);
  void epollWait();
  bool checkFinishReceive(int n);
  void processClient(int n);
  bool isCgiFd(int fd) const;
  void dispatchCgiEvent(int current_fd);
  void handleClientRecv(int n);
  bool handleCompletedRequest(int n, int current_fd);
  void handleClientSend(int n);
  bool sendResponseChunk(int current_fd, Client& curr_client);
  void modMonitorEpollin(int conn_sock);
  void modMonitorEpollout(int conn_sock);
  void checkCgiTimeout();
  void checkClientTimeout();
  void registerCgiPipes(int clientFd, Client* client);
  void handleCgiOutput(int current_fd, std::map<int, Client>::iterator it);
  void handleCgiInput(int current_fd, std::map<int, Client>::iterator it);
  bool finishCgiOutput(int current_fd, std::map<int, Client>::iterator it);
  bool reapCgiProcess(int current_fd, std::map<int, Client>::iterator it);
  bool finishCgiInput(int current_fd, std::map<int, Client>::iterator it);
  void closeCgiInPipe(int current_fd, std::map<int, Client>::iterator it);
  std::string buildCgiResponse(const std::string& cgi_output);
  bool receiveIntoClient(int fd);
  void parseHeaderPhase();
  void parseBodyPhase();
  int acceptConnection(int listen_fd);
  ConfigServer* findDefaultServerForPort(int port,
                                         std::vector<ConfigServer>& servers);
  void registerNewClient(int conn_sock, int connected_port,
                         ConfigServer* default_server);
  void abortCgi(std::map<int, Client>::iterator it);
  void selectVirtualHost();

public:
  Server();
  ~Server();
  std::map<int, Client> getClient() const;
  void createSocketAndEpoll(const std::vector<ConfigServer>& parsed_servers);
  void run(std::vector<ConfigServer>& servers);
  void runServer(std::vector<ConfigServer>& servers);
};

#endif
