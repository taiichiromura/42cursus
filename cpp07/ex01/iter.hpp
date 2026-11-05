#include <cstddef>
#include <string>
#include <iostream>

template <typename T, typename F>
void iter(T *array, const std::size_t length, F func);

template <typename T>
void display(const T &num);
