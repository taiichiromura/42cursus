#ifndef CONFIG_SERVER_HPP
#define CONFIG_SERVER_HPP

#include "Location.hpp"
#include <map>
#include <stdint.h>
#include <string>
#include <vector>
struct Session {
  int visitCount;
  std::string username;
};
class ConfigServer {
private:
  uint16_t _port;
  std::string _server_name;
  std::string _root;
  std::string _index;
  std::map<int, std::string> _error_pages;
  std::vector<Location> _locations;
  Session session;
  std::map<std::string, Session> _sessions;

public:
  ConfigServer();
  ~ConfigServer();
  const uint16_t& getPort() const;
  void setPort(uint16_t portNum);
  void setServerName(std::string serverName);
  const std::string& getServerName() const;
  const std::string& getRoot() const;
  void setRoot(std::string root);
  void addLocation(const Location& loc);
  void addErrorPage(const short& code, const std::string& path);

  const std::vector<Location>& getLocation() const;
  void printServerConfig() const;
  Session& getSession(std::string sessionId);

  const std::map<int, std::string>& getErrorPagesMap() const;
};

#endif
