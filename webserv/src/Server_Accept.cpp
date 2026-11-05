#include "Server.hpp"
#include "Utils.hpp"


int Server::acceptListeningSocket(int listen_fd,
                                  std::vector<ConfigServer>& servers) {
  int conn_sock = this->acceptConnection(listen_fd);
  if (conn_sock == -1)
    return -1;

  int connected_port = this->_fd_to_port_map[listen_fd];
  ConfigServer* default_server =
      this->findDefaultServerForPort(connected_port, servers);

  this->registerNewClient(conn_sock, connected_port, default_server);

  return conn_sock;
}

int Server::acceptConnection(int listen_fd) {
  int conn_sock =
      accept(listen_fd, NULL, NULL);
  if (conn_sock == -1) {
    if (errno != EAGAIN && errno != EWOULDBLOCK)
      ft_throw("accept");
    return -1;
  }
  return conn_sock;
}

// 全サーバー設定の中から、このポートを担当している「最初のサーバー」を探す
// Hostヘッダーが一致しなかった場合のデフォルトサーバー
ConfigServer*
Server::findDefaultServerForPort(int port, std::vector<ConfigServer>& servers) {
  for (size_t i = 0; i < servers.size(); i++) {
    if (servers[i].getPort() == port)
      return &servers[i];
  }
  return NULL;
}

void Server::registerNewClient(int conn_sock, int connected_port,
                               ConfigServer* default_server) {
  Client new_client;

  if (default_server != NULL)
    new_client.setServer(*default_server);
  new_client.setServerPort(connected_port);

  this->_client[conn_sock] = new_client;
}
