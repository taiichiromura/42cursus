
#include "iter.hpp"

template <typename T>
void display(const T &str) {
  std::cout << str << std::endl;
}

template <typename T>
void increment(T& x)
{
  ++x;
}

template <typename T, typename F>
void iter(T *array, const std::size_t length, F func) {
  if (array == NULL)
    return;
  for (std::size_t i = 0; i < length; i++) {
    func(array[i]);
  }
}

int main() {
  const int constintarray[4] = {1, 2, 3, 4};
  int intarray[4] = {1, 2, 3, 4};
  iter(constintarray, 4, display<int>);
// iter(constintarray, 4, increment<int>); // コンパイルできない
  iter(intarray, 4, increment<int>);
  iter(intarray, 4, display<int>);

  std::string strarray[4] = {"abcdefg", "hijklmn", "opqrstu", "vwxyz"};
  iter(strarray, 4, display<std::string>);

  char chararray[4] = {'a', 'b', 'c', 'd'};
  iter(chararray, 4, display<char>);

  float farray[4] = {1.1f, 2.2f, 3.3f, 4.4f};
  iter(farray, 4, display<float>);

  double darray[4] = {1.1, 2.2, 3.3, 4.4};
  iter(darray, 4, display<double>);
}
