#include "Base.hpp"
#include <ctime>
#include <iostream>

int main() {
  std::srand(std::time(NULL));

  std::cout << "=== Test 1 ===" << std::endl;
  Base *ptr1 = generate();

  std::cout << "--- Pointer Identify ---" << std::endl;
  identify(ptr1);

  std::cout << "--- Reference Identify ---" << std::endl;
  identify(*ptr1);

  delete ptr1;

  std::cout << "\n=== Test 2 ===" << std::endl;
  Base *ptr2 = generate();
  identify(ptr2);
  identify(*ptr2);
  delete ptr2;

  return 0;
}
