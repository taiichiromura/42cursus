#include "Client.hpp"
#include "Response.hpp"

#include <cstdio>
#include <unistd.h>

std::string Response::deleteResponse(Location& loc, Client* client) {
  ConfigServer& server = client->getServer();
  std::string root_path = this->getEffectiveRoot(loc, server);
  std::string request_target = client->getRequestTarget();
  std::string relative = request_target.substr(loc.getLocationPath().size());

  if (!this->checkFileName(relative))
    return this->errorResponse(loc, server, 400);

  std::string filePath = this->joinRootAndRelative(root_path, relative);

  if (access(filePath.c_str(), F_OK) == -1)
    return this->errorResponse(loc, server, 404);
  if (access(filePath.c_str(), W_OK) == -1)
    return this->errorResponse(loc, server, 403);

  if (std::remove(filePath.c_str()) == 0)
    return "HTTP/1.1 204 No Content\r\nContent-Length: 0\r\n\r\n";
  return this->errorResponse(loc, server, 404);
}
