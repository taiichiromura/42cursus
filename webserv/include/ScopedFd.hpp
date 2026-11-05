#ifndef SCOPEDFD_HPP
#define SCOPEDFD_HPP

class ScopedFd {
public:
  ScopedFd();
  explicit ScopedFd(int fd);
  ~ScopedFd();

  int get() const;
  void reset(int fd = -1);
  int release();

private:
  ScopedFd(const ScopedFd&);
  ScopedFd& operator=(const ScopedFd&);

  int _fd;
};

#endif
