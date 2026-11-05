#include "Utils.hpp"


bool CaseInsensitiveLess::operator()(const std::string& a, const std::string& b) const {
  size_t len = (a.size() < b.size()) ? a.size() : b.size();
  for (size_t i = 0; i < len; i++) {
    unsigned char ca = static_cast<unsigned char>(std::tolower(static_cast<unsigned char>(a[i])));
    unsigned char cb = static_cast<unsigned char>(std::tolower(static_cast<unsigned char>(b[i])));
    if (ca != cb) return ca < cb;
  }
  return a.size() < b.size();
}

void ft_throw(const std::string& msg) {
  if (errno != 0) {
    throw std::runtime_error(msg + ": " + strerror(errno));
  } else {
    throw std::runtime_error(msg);
  }
}

size_t ft_stoi(std::string str) {
  if (str == "")
    return 0;
  std::stringstream ss(str);
  if (str.length() > 10)
    throw std::runtime_error("too long");
  size_t res;
  ss >> res;
  return (res);
}

std::string ft_to_string(int num) {
  std::stringstream ss;
  ss << num;
  return ss.str();
}

int is_file_exist_posix(const std::string& filename) {
  struct stat buffer;
  if (stat(filename.c_str(), &buffer) != 0) {
    return -1;
  }
  if (buffer.st_mode & 0200) {
    return 1;
  } else {
    return 0;
  }
}

std::string ft_trim(const std::string& str) {
  const std::string whitespace = " \t\r\n";

  size_t start = str.find_first_not_of(whitespace);
  if (start == std::string::npos) {
    return "";
  }

  size_t end = str.find_last_not_of(whitespace);
  return str.substr(start, end - start + 1);
}

bool readFileToString(const std::string& path, std::string& out) {
  std::ifstream target(path.c_str(), std::ios::binary);
  if (!target.is_open())
    return false;
  std::stringstream ss;
  ss << target.rdbuf();
  out = ss.str();
  return true;
}

volatile sig_atomic_t g_shutdown_requested = 0;

void handleShutdownSignal(int) {
  g_shutdown_requested = 1;
}

std::string urlDecode(const std::string& str) {
  std::string result;
  for (size_t i = 0; i < str.size(); i++) {
    if (str[i] == '%' && i + 2 < str.size() &&
        std::isxdigit(static_cast<unsigned char>(str[i + 1])) &&
        std::isxdigit(static_cast<unsigned char>(str[i + 2]))) {
      std::string hex = str.substr(i + 1, 2);
      int value = static_cast<int>(std::strtol(hex.c_str(), NULL, 16));
      result += static_cast<char>(value);
      i += 2;
    } else {
      result += str[i];
    }
  }
  return result;
}
