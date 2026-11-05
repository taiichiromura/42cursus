#ifndef UTILS_HPP
#define UTILS_HPP

#include <csignal>
#include <string>
#include <sys/stat.h>
#include <cerrno>
#include <fstream>
#include <sstream>
#include <string.h>
#include <sys/types.h>
#include <cctype>
#include <cstdlib>

extern volatile sig_atomic_t g_shutdown_requested;
void handleShutdownSignal(int signum);
size_t ft_stoi(std::string str);
std::string ft_to_string(int num);
int is_file_exist_posix(const std::string& filename);
std::string ft_trim(const std::string& str);
void ft_throw(const std::string& msg);
bool readFileToString(const std::string& path, std::string& out);

struct CaseInsensitiveLess {
  bool operator()(const std::string& a, const std::string& b) const;
};

std::string urlDecode(const std::string& str);

#endif
