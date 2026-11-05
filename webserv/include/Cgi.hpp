#ifndef CGI_HPP
#define CGI_HPP

#include <fcntl.h>
#include <string>
#include <unistd.h>

class Client;

class CGI {
public:
  std::string do_cgi(std::string cgi_path, std::string filepath,
                     std::string query, Client* client);
  std::string do_cgi_post(std::string cgi_path, std::string filepath,
                          std::string body, Client* client);
};

#endif
