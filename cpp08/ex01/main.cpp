#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Span.hpp"

void testBasic() {
  std::cout << "=== Basic test ===" << std::endl;
  Span sp(5);
  sp.addNumber(6);
  sp.addNumber(3);
  sp.addNumber(17);
  sp.addNumber(9);
  sp.addNumber(11);

  Span same(5);
  same.addNumber(1);
  same.addNumber(1);
  same.addNumber(1);
  same.addNumber(1);
  same.addNumber(1);

  Span bigName(2);
  bigName.addNumber(2147483647);
  bigName.addNumber(-2147483648);

  std::cout << "---3, 6, 9, 11, 17のテスト---" << std::endl;
  std::cout << "shortestSpan: " << sp.shortestSpan() << std::endl;
  std::cout << "longestSpan: " << sp.longestSpan() << std::endl;

  std::cout << "---全部1のテスト---" << std::endl;
  std::cout << "same number shortestSpan: " << same.shortestSpan() << std::endl;
  std::cout << "same number longestSpan: " << same.longestSpan() << std::endl;

  std::cout << "---INTMAX,INTMINのテスト---" << std::endl;
  std::cout << "int max min shortestSpan: " << bigName.shortestSpan()
            << std::endl;
  std::cout << "int max min longestSpan: " << bigName.longestSpan()
            << std::endl;
  try {
    sp.addNumber(100);
  } catch (const std::exception& e) {
    std::cout << "Caught expected exception: " << e.what() << std::endl;
  }
}

void testExceptions() {
  std::cout << "\n---例外のテスト(空データ、データ数１)---" << std::endl;
  Span sp(3);
  try {
    sp.shortestSpan();
  } catch (const std::exception& e) {
    std::cout << "Caught (empty): " << e.what() << std::endl;
  }

  sp.addNumber(42);
  try {
    sp.longestSpan();
  } catch (const std::exception& e) {
    std::cout << "Caught (only one): " << e.what() << std::endl;
  }
}

void testLargeScale(unsigned int n) {
  std::cout << "\n大きなスケールのテスト (" << n << " numbers) ---"
            << std::endl;
  std::srand(static_cast<unsigned int>(std::time(NULL)));

  Span sp(n);
  for (unsigned int i = 0; i < n; ++i) {
    sp.addNumber(std::rand());
  }

  std::cout << "Size: " << sp.getNums().size() << std::endl;
  std::cout << "shortestSpan: " << sp.shortestSpan() << std::endl;
  std::cout << "longestSpan: " << sp.longestSpan() << std::endl;

  try {
    sp.addNumber(1);
  } catch (const std::exception& e) {
    std::cout << "Caught expected exception on full Span: " << e.what()
              << std::endl;
  }
}

void testAddRange() {
  std::cout << "\n---addRangeのtest---" << std::endl;

  // vectorのイテレータで一括追加
  std::vector<int> v;
  v.push_back(10);
  v.push_back(20);
  v.push_back(30);

  Span sp(5);
  sp.addRange(v.begin(), v.end());
  std::cout << "vector経由 addRange後 size: " << sp.getNums().size() << std::endl;
  std::cout << "shortestSpan: " << sp.shortestSpan() << std::endl;
  std::cout << "longestSpan: " << sp.longestSpan() << std::endl;

  // 配列のポインタをイテレータとして使う場合
  int arr[] = {1, 2, 3};
  Span sp2(3);
  sp2.addRange(arr, arr + 3);
  std::cout << "配列経由 addRange後 size: " << sp2.getNums().size() << std::endl;

  // addRangeで容量オーバーする場合、例外を投げるか確認
  Span sp3(2);
  std::vector<int> tooMany;
  tooMany.push_back(1);
  tooMany.push_back(2);
  tooMany.push_back(3);
  try {
    sp3.addRange(tooMany.begin(), tooMany.end());
  } catch (const std::exception& e) {
    std::cout << "Caught expected exception (addRange over capacity): "
              << e.what() << std::endl;
  }

  // addNumberとaddRangeを混ぜて使う場合
  Span sp4(5);
  sp4.addNumber(100);
  std::vector<int> more;
  more.push_back(200);
  more.push_back(300);
  sp4.addRange(more.begin(), more.end());
  std::cout << "混在追加後 size: " << sp4.getNums().size() << std::endl;
}


int main() {
  testBasic();
  testExceptions();
  testAddRange();
  testLargeScale(10000);
  testLargeScale(1000000);
  return 0;
}
