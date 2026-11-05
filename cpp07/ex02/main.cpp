#include "Array.hpp"

int main() {
  Array<int> a(5);
  a[0] = 42;
  for (int i = 0; i < 5; i++) {
    std::cout << a[i] << std::endl;
  }
  Array<int> b = a;
  b[0] = 999;

  for (int i = 0; i < 5; i++) {
    std::cout << b[i] << std::endl;
  }

  // 例外
  try {
    a[10];
  } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
  }
  //const呼ばれるか
  const Array<int> c(5);

  std::cout << c[0];

  //スコープ抜けデストラクタ
  {
    Array<int> a(100);
  }

  //string
  Array<std::string> s(3);
  s[0] = "hello";
  s[1] = "good bye";
  s[2] = "hello";
  for (int i = 0; i < 3; i++) {
    std::cout << s[i] << std::endl;
  }

  std::cout << s.size() << std::endl;
}
