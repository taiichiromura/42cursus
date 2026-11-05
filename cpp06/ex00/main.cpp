#include "ScalarConverter.hpp"
#include <iostream>

void test_char_literal() {
  std::cout << "=== Test 1: Char Literal ===" << std::endl;
  ScalarConverter::convert("");
  std::cout << std::endl;

  ScalarConverter::convert("*");
  std::cout << std::endl;
}

void test_int_literal() {
  std::cout << "=== Test 2: Int Literal ===" << std::endl;
  ScalarConverter::convert("0");
  std::cout << std::endl;

  ScalarConverter::convert("-42");
  std::cout << std::endl;

  ScalarConverter::convert("2147483647");
  std::cout << std::endl;
}

void test_float_double_literal() {
  std::cout << "=== Test 3: Float & Double Literal ===" << std::endl;
  ScalarConverter::convert("42.0f");
  std::cout << std::endl;

  ScalarConverter::convert("3.14159");
  std::cout << std::endl;

  ScalarConverter::convert("-0.0f");
  std::cout << std::endl;
}

void test_pseudo_literal() {
  std::cout << "=== Test 4: Pseudo Literal ===" << std::endl;
  ScalarConverter::convert("nan");
  std::cout << std::endl;

  ScalarConverter::convert("-inff");
  std::cout << std::endl;
}

void test_invalid_literal() {
  std::cout << "=== Test 5: Invalid Literal ===" << std::endl;
  ScalarConverter::convert("42abcdef");
  std::cout << std::endl;

  ScalarConverter::convert("abcdef42");
  std::cout << std::endl;
}

int main() {
  std::cout << std::fixed << std::setprecision(1);
  test_char_literal();
  test_int_literal();
  test_float_double_literal();
  test_pseudo_literal();
  test_invalid_literal();

  return 0;
}
