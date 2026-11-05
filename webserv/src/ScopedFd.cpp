#include "ScopedFd.hpp"
#include <unistd.h>

ScopedFd::ScopedFd() : _fd(-1) {}

ScopedFd::ScopedFd(int fd) : _fd(fd) {}

ScopedFd::~ScopedFd() {
  if (_fd != -1)
    close(_fd);
}

int ScopedFd::get() const {
  return _fd;
}

void ScopedFd::reset(int fd) {
  if (_fd != -1)
    close(_fd);
  _fd = fd;
}

int ScopedFd::release() {
  int fd = _fd;
  _fd = -1;
  return fd;
}
