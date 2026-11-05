#include "whatever.hpp"
int main(void) {
  int a = 2;
  int b = 3;
  ::swap(a, b);
  std::cout << "a = " << a << ", b = " << b << std::endl;
  std::cout << "address of a = " << &a << ", address of b = " << &b << std::endl;
  std::cout << "min( a, b ) = " << ::min(a, b) << std::endl;
  std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;
  std::cout << "minaddress = " << &::min(a, b) << std::endl;
  std::cout << "maxaddress = " << &::max(a, b) << std::endl;
  
  a = 2;
  std::cout << "a = " << a << ", b = " << b << std::endl;
  std::cout << "address of a = " << &a << ", address of b = " << &b << std::endl;
  std::cout << "min( a, b ) = " << ::min(a, b) << std::endl;
  std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;
  std::cout << "minaddress = " << &::min(a, b) << std::endl;
  std::cout << "maxaddress = " << &::max(a, b) << std::endl;
  
  std::string c = "chaine1";
  std::string d = "chaine2";
  ::swap(c, d);
  std::cout << "c = " << c << ", d = " << d << std::endl;
  std::cout << "min( c, d ) = " << ::min(c, d) << std::endl;
  std::cout << "max( c, d ) = " << ::max(c, d) << std::endl;
  return 0;
}
