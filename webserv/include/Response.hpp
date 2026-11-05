#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "Cgi.hpp"
#include "ConfigServer.hpp"
#include <ctime>
#include <string>

class Client;

class Response {
private:
  std::string _response;
  std::map<int, std::string> _errorMap;
  Location longestPrefixMatch(std::string requestTarget,
                              const std::vector<Location>& locations);
  std::string errorResponse(Location& loc, ConfigServer& server, int errorNum);
  std::string getContentType(const std::string& filepath);
  std::string postResponse(Location& loc, Client* client);
  std::string deleteResponse(Location& loc, Client* client);
  std::string getFileType(const std::string& filepath);
  std::string redirect301Response(Client* client, std::string url);
  bool checkFileName(std::string filename);
  bool isDirectory(const std::string& filename);
  std::string Autoindex(const std::string& filename, Location& loc);
  std::string generateSessionId();
  std::string buildResponse(Location& loc, std::string& statusCode,
                            std::string& contentType, std::string& body);
  CGI cgi;
  std::string resolveFilePath(Location& loc, Client* client,
                              const std::string& request_target);
  std::string checkDirectoryRedirect(Client* client,
                                     const std::string& filePath,
                                     const std::string& request_target);
  void resolveIndexFile(Location& loc, const std::string& request_target,
                        std::string& filePath);
  void normalizeDoubleSlashes(std::string& filePath);
  std::string checkFileAccessible(Location& loc, ConfigServer& server,
                                  const std::string& filePath);
  std::string tryCgiResponse(Location& loc, Client* client,
                             const std::string& filePath,
                             const std::string& request_target);
  std::string buildStaticFileResponse(Client* client, ConfigServer& server,
                                      const std::string& filePath,
                                      std::ifstream& target);
  std::string buildSessionHeaders(Client* client, ConfigServer& server);
  std::string getEffectiveRoot(Location& loc, ConfigServer& server);
  std::string joinRootAndRelative(std::string root_path,
                                  const std::string& relative);

  // POST
  std::string checkBodySize(Location& loc, ConfigServer& server,
                            Client* client);
  std::string buildRootPostResponse(Client* client);
  std::string tryCgiPostResponse(Location& loc, Client* client,
                                 const std::string& filePath,
                                 const std::string& relative);
  std::string writeUploadedFile(Location& loc, ConfigServer& server,
                                Client* client, const std::string& filePath);

public:
  Response();
  ~Response();
  void createResponse(Client* clinet);
  std::string getResponse(Location& loc, Client* client);
  const std::string& getResponseStr() const;
  void setResponseStr(const std::string& response);
};

#endif
