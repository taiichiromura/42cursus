#include "Response.hpp"

#include <cstdlib>
#include <dirent.h>

std::string Response::getEffectiveRoot(Location& loc, ConfigServer& server) {
  std::string root_path = loc.getRoot();
  if (root_path.empty())
    root_path = server.getRoot();
  return root_path;
}

std::string Response::joinRootAndRelative(std::string root_path,
                                          const std::string& relative) {
  if (!root_path.empty() && root_path[root_path.length() - 1] != '/')
    root_path += "/";
  return root_path + relative;
}

Location Response::longestPrefixMatch(std::string requestTarget,
                                      const std::vector<Location>& locations) {
  size_t matched_length = 0;
  int pos = 0;
  for (size_t i = 0; i < locations.size(); i++) {
    std::string loc_path = locations[i].getLocationPath();
    if (loc_path.empty())
      continue;
    if (requestTarget.compare(0, loc_path.size(), loc_path) == 0) {
      if (loc_path.size() > matched_length) {
        matched_length = loc_path.size();
        pos = i;
      }
    }
  }
  return locations[pos];
}

std::string Response::getContentType(const std::string& filePath) {
  if (filePath.size() >= 5 && filePath.substr(filePath.size() - 5) == ".html")
    return "text/html";
  if (filePath.size() >= 4 && filePath.substr(filePath.size() - 4) == ".css")
    return "text/css";
  if (filePath.size() >= 3 && filePath.substr(filePath.size() - 3) == ".js")
    return "application/javascript";
  if (filePath.size() >= 4 && filePath.substr(filePath.size() - 4) == ".png")
    return "image/png";
  if (filePath.size() >= 4 && filePath.substr(filePath.size() - 4) == ".jpg")
    return "image/jpeg";
  return "application/octet-stream";
}

std::string Response::getFileType(const std::string& filePath) {
  size_t dot_pos = filePath.rfind('.');
  if (dot_pos == std::string::npos || dot_pos == filePath.size() - 1)
    return "";
  return filePath.substr(dot_pos);
}

std::string Response::generateSessionId() {
  const char* hex = "0123456789abcdef";
  std::string id;
  for (int i = 0; i < 16; i++)
    id += hex[rand() % 16];
  return id;
}

bool Response::checkFileName(std::string filename) {
  if (filename.empty())
    return false;
  if (filename == "." || filename == "..")
    return false;
  std::string invalid_chars = "/\\:*?\"<>|\0";
  if (filename.find_first_of(invalid_chars) != std::string::npos)
    return false;
  return true;
}

bool Response::isDirectory(const std::string& filename) {
  DIR* dir = opendir(filename.c_str());
  if (dir == NULL)
    return false;
  closedir(dir);
  return true;
}
