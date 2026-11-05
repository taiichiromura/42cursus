#ifndef CONFIG_PARSER_HPP
#define CONFIG_PARSER_HPP

#include "ConfigServer.hpp"
#include <string>
#include <vector>

class ConfigParser {
private:
  std::vector<std::string> _server_config;
  size_t _nb_server;
  std::vector<ConfigServer> _servers;
  size_t findStartServer(size_t start, std::string& content);
  size_t findEndServer(size_t start, std::string& content);
  void parseServer(const std::string& line, ConfigServer* confserv);
  size_t getBlockSize(const std::vector<std::string>& tokens, size_t start_pos);
  void checkDuplicateServers() const;

public:
  ConfigParser();
  ~ConfigParser();
  void splitConfToServers(std::string& content, ConfigServer* confserv);
  const std::vector<ConfigServer>& getServers() const {
    return this->_servers;
  };
};

#endif
