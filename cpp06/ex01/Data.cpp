#include "Data.hpp"

Data::Data() : num(0), str("") {}

Data::Data(int n, const std::string &text) : num(n), str(text) {}

Data::Data(const Data &other) { *this = other; }

Data &Data::operator=(const Data &other) {
  if (this != &other) {
    this->num = other.num;
    this->str = other.str;
  }
  return *this;
}

Data::~Data() {}
