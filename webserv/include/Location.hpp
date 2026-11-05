#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <map>
#include <set>
#include <string>
#include <vector>
class ConfigServer;

class Location {

private:
  std::string _location_path;
  std::string _root;
  std::string _index;
  std::size_t _client_max_body_size;
  bool _autoindex;
  std::map<int, std::string> _error_pages_map;
  std::map<std::string, std::string> _cgi_handlers_map;
  std::set<std::string> _limit_except;
  std::string _upload_store;
  std::pair<int, std::string> _return;

public:
  Location();
  ~Location();
  Location(const Location& other);
  Location& operator=(const Location& other);
  static void parseLocation(const std::vector<std::string>& tokens,
                            size_t start, size_t len, ConfigServer* confserv);

public:
  const std::string& getLocationPath() const;
  const std::string& getRoot() const;
  const std::string& getIndex() const;
  std::size_t getClientMaxBodySize() const;
  bool getAutoindex() const;
  const std::map<std::string, std::string>& getCgiHandlersMap() const;
  const std::set<std::string>& getLimitExcept() const;
  const std::string& getUploadStore() const;
  std::pair<int, std::string> getReturn() const;

  void setLocationPath(const std::string& location_path);
  void setRoot(const std::string& root);
  void setIndex(const std::string& index);
  void setClientMaxBodySize(std::size_t size);
  void setAutoindex(bool autoindex);
  void
  setCgiHandlersMap(const std::map<std::string, std::string>& cgi_handlers);
  void setLimitExcept(const std::set<std::string>& limit_except);
  void setUploadStore(const std::string& upload_store);
  void setReturn(int code, const std::string& url);
};

#endif
