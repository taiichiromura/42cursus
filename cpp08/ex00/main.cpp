#include <list>

#include "easyfind.hpp"

int main() {
  std::cout << "=== 1. 基本: 見つかる/見つからない ===" << std::endl;
  std::vector<int> n(10, 0);
  n[3] = 42;

  try {
    const int res = easyfind(n, 42);
    std::cout << "found: " << res << std::endl;
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  try {
    const int res = easyfind(n, 2);
    std::cout << "found: " << res << std::endl;
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << "\n=== 2. 空のコンテナ ===" << std::endl;
  std::vector<int> empty;
  try {
    const int res = easyfind(empty, 1);
    std::cout << "found: " << res << std::endl;
  } catch (const std::exception& e) {
    std::cout << "exception: " << e.what() << std::endl;
  }

  std::cout << "\n=== 3. 先頭にある場合 ===" << std::endl;
  std::vector<int> front;
  front.push_back(7);
  front.push_back(1);
  front.push_back(2);
  try {
    std::cout << "found: " << easyfind(front, 7) << std::endl;
  } catch (const std::exception& e) {
    std::cout << "exception: " << e.what() << std::endl;
  }

  std::cout << "\n=== 4. 末尾にある場合 ===" << std::endl;
  std::vector<int> back;
  back.push_back(1);
  back.push_back(2);
  back.push_back(9);
  try {
    std::cout << "found: " << easyfind(back, 9) << std::endl;
  } catch (const std::exception& e) {
    std::cout << "exception: " << e.what() << std::endl;
  }

  std::cout << "\n=== 5. 重複した値がある場合 ===" << std::endl;
  std::vector<int> dup;
  dup.push_back(5);
  dup.push_back(5);
  dup.push_back(5);
  try {
    std::cout << "found: " << easyfind(dup, 5) << std::endl;
  } catch (const std::exception& e) {
    std::cout << "exception: " << e.what() << std::endl;
  }

  std::cout << "\n=== 6. const vector でも動くか ===" << std::endl;
  const std::vector<int> constVec(n);
  try {
    std::cout << "found: " << easyfind(constVec, 42) << std::endl;
  } catch (const std::exception& e) {
    std::cout << "exception: " << e.what() << std::endl;
  }

  std::cout << "\n=== 7. std::list でも動くか===" << std::endl;
  std::list<int> lst;
  lst.push_back(10);
  lst.push_back(20);
  lst.push_back(30);
  try {
    std::cout << "found: " << easyfind(lst, 20) << std::endl;
  } catch (const std::exception& e) {
    std::cout << "exception: " << e.what() << std::endl;
  }

  std::cout << "\n=== 8. 負の数を含む場合 ===" << std::endl;
  std::vector<int> negs;
  negs.push_back(-5);
  negs.push_back(0);
  negs.push_back(5);
  try {
    std::cout << "found: " << easyfind(negs, -5) << std::endl;
  } catch (const std::exception& e) {
    std::cout << "exception: " << e.what() << std::endl;
  }

  return 0;
}
