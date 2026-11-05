#include "ConfigServer.hpp"

ConfigServer::ConfigServer() {
  this->_port = 0;
}

ConfigServer::~ConfigServer() {}

void ConfigServer::printServerConfig() const {

  const std::vector<Location>& locs = this->getLocation();

  for (size_t i = 0; i < locs.size(); ++i) {
    const Location& loc = locs[i];
    std::pair<int, std::string> ret = loc.getReturn();
    const std::set<std::string>& methods = loc.getLimitExcept();
    for (std::set<std::string>::const_iterator it = methods.begin();
         it != methods.end(); ++it) {}

    const std::map<std::string, std::string>& cgis = loc.getCgiHandlersMap();
    for (std::map<std::string, std::string>::const_iterator it = cgis.begin();
         it != cgis.end(); ++it) {}
  }
}

void ConfigServer::setPort(uint16_t portNum) {
  this->_port = portNum;
}

void ConfigServer::setServerName(std::string serverName) {
  this->_server_name = serverName;
}

void ConfigServer::setRoot(std::string root) {
  this->_root = root;
}

const uint16_t& ConfigServer::getPort() const {
  return this->_port;
}

const std::string& ConfigServer::getRoot() const {
  return this->_root;
}

void ConfigServer::addLocation(const Location& loc) {
  this->_locations.push_back(loc);
}

const std::vector<Location>& ConfigServer::getLocation() const {
  return this->_locations;
}

void ConfigServer::addErrorPage(const short& code, const std::string& path) {
  this->_error_pages[code] = path;
}

Session& ConfigServer::getSession(std::string sessionId) {
  if (_sessions.size() > 1000) {
    _sessions.clear();
  }
  return _sessions[sessionId];
}

const std::map<int, std::string>& ConfigServer::getErrorPagesMap() const {
  return this->_error_pages;
}

const std::string& ConfigServer::getServerName() const {
  return this->_server_name;
}
