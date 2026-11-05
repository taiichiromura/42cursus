#ifndef DATA_HPP
#define DATA_HPP

#include <string>

struct Data {
  int num;
  std::string str;

  Data();
  Data(int n, const std::string &text);
  Data(const Data &other);
  Data &operator=(const Data &other);
  ~Data();
};

#endif
