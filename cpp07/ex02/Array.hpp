#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>

template <typename T>
class Array {
private:
  T *_array;
  unsigned int _size;

public:
  Array();
  Array(unsigned int n);
  Array(const Array &other);
  Array &operator=(const Array &other);
  virtual ~Array();
  unsigned int size() const;
  T &operator[](unsigned int i);
  const T &operator[](unsigned int i) const;
};

#include "Array.tpp"

#endif
