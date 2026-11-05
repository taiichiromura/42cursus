#include "Location.hpp"
#include "ConfigServer.hpp"
#include "Utils.hpp"
#include <cstdlib>
#include <stdexcept>

Location::Location() {
  this->_autoindex = false;
  this->_client_max_body_size = 1000000;
}

Location::~Location() {}

Location::Location(const Location& other) {
  *this = other;
}

Location& Location::operator=(const Location& other) {
  if (this != &other) {
    this->_location_path = other._location_path;
    this->_root = other._root;
    this->_index = other._index;
    this->_client_max_body_size = other._client_max_body_size;
    this->_autoindex = other._autoindex;
    this->_error_pages_map = other._error_pages_map;
    this->_cgi_handlers_map = other._cgi_handlers_map;
    this->_limit_except = other._limit_except;
    this->_upload_store = other._upload_store;
    this->_return = other._return;
  }
  return *this;
}

void Location::parseLocation(const std::vector<std::string>& tokens,
                             size_t start, size_t end, ConfigServer* confserv) {
  Location new_location;
  if (start + 1 < end)
    new_location.setLocationPath(tokens[start + 1]);
  for (size_t i = start; i < end; i++) {
    if (tokens[i] == "root" && i + 1 < end) {
      new_location.setRoot(tokens[i + 1]);
    } else if (tokens[i] == "autoindex") {
      if (tokens[i + 1] == "on")
        new_location.setAutoindex(true);
      else if (tokens[i + 1] == "off")
        new_location.setAutoindex(false);
      else
        throw std::runtime_error("invalid setting in autoindex");
    } else if (tokens[i] == "index") {
      if (i + 1 < end && tokens[i + 1] != ";") {
        new_location.setIndex(tokens[i + 1]);
      }
    } else if ((tokens[i] == "max_body_size" ||
                tokens[i] == "client_max_body_size") &&
               i + 1 < end) {
      new_location.setClientMaxBodySize(
          static_cast<size_t>(ft_stoi(tokens[i + 1])));
      i++;
    } else if ((tokens[i] == "method" || tokens[i] == "allow_methods") &&
               i + 1 < end) {
      std::set<std::string> methods;
      i++;
      while (i < end && tokens[i] != ";") {
        methods.insert(tokens[i]);
        i++;
      }
      new_location.setLimitExcept(methods);
    } else if ((tokens[i] == "upload_path" || tokens[i] == "upload_store") &&
               i + 1 < end) {
      new_location.setUploadStore(tokens[i + 1]);
      i++;
    } else if (tokens[i] == "return" && i + 2 < end) {
      int code = ft_stoi(tokens[i + 1]);
      std::string url = tokens[i + 2];
      new_location.setReturn(code, url);
      i += 2;
    } else if (tokens[i] == "cgi_path" && i + 2 < end) {
      std::map<std::string, std::string> cgi_map =
          new_location.getCgiHandlersMap();
      std::string file_type = tokens[i + 1];
      std::string path = tokens[i + 2];

      cgi_map[file_type] = path;
      new_location.setCgiHandlersMap(cgi_map);
      i += 2;
    }
  }
  confserv->addLocation(new_location);
}

const std::string& Location::getLocationPath() const {
  return this->_location_path;
}

const std::string& Location::getRoot() const {
  return this->_root;
}

const std::string& Location::getIndex() const {
  return this->_index;
}

std::size_t Location::getClientMaxBodySize() const {
  return this->_client_max_body_size;
}

bool Location::getAutoindex() const {
  return this->_autoindex;
}

const std::map<std::string, std::string>& Location::getCgiHandlersMap() const {
  return this->_cgi_handlers_map;
}

const std::set<std::string>& Location::getLimitExcept() const {
  return this->_limit_except;
}

const std::string& Location::getUploadStore() const {
  return this->_upload_store;
}

std::pair<int, std::string> Location::getReturn() const {
  return this->_return;
}

// ==========================================
//                   Setters
// ==========================================

void Location::setLocationPath(const std::string& location_path) {
  this->_location_path = location_path;
}

void Location::setRoot(const std::string& root) {
  this->_root = root;
}

void Location::setIndex(const std::string& index) {
  this->_index = index;
}

void Location::setClientMaxBodySize(std::size_t size) {
  this->_client_max_body_size = size;
}

void Location::setAutoindex(bool autoindex) {
  this->_autoindex = autoindex;
}

void Location::setCgiHandlersMap(
    const std::map<std::string, std::string>& cgi_handlers) {
  this->_cgi_handlers_map = cgi_handlers;
}

void Location::setLimitExcept(const std::set<std::string>& limit_except) {
  this->_limit_except = limit_except;
}

void Location::setUploadStore(const std::string& upload_store) {
  this->_upload_store = upload_store;
}

void Location::setReturn(int code, const std::string& url) {
  this->_return = std::make_pair(code, url);
}
