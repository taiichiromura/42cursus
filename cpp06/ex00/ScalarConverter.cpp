#include "ScalarConverter.hpp"
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &other) { (void)other; }
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other) {
  (void)other;
  return *this;
}
ScalarConverter::~ScalarConverter() {}

static bool is_printable(char c) { return (c >= ' ' && c <= '~'); }

static bool is_pseudo_literal(const std::string &str) {
  return (str == "nan" || str == "nanf" || str == "-nan" || str == "-nanf" ||
          str == "inf" || str == "inff" || str == "+inf" || str == "+inff" ||
          str == "-inf" || str == "-inff");
}

static void handle_pseudo(const std::string &str) {
  std::cout << "char: impossible" << std::endl;
  std::cout << "int: impossible" << std::endl;
  if (str == "nan" || str == "nanf" || str == "-nan" || str == "-nanf") {
    if (str[0] == '-') {
      std::cout << "float: -nanf" << std::endl;
      std::cout << "double: -nan" << std::endl;
    } else {
      std::cout << "float: nanf" << std::endl;
      std::cout << "double: nan" << std::endl;
    }
  } else if (str == "-inf" || str == "-inff") {
    std::cout << "float: -inff" << std::endl;
    std::cout << "double: -inf" << std::endl;
  } else {
    std::cout << "float: inff" << std::endl;
    std::cout << "double: inf" << std::endl;
  }
}

static void print_all_types(double val) {
  if (val < 0 || val > 127 || std::isnan(val)) {
    std::cout << "char: impossible" << std::endl;
  } else {
    char c = static_cast<char>(val);
    if (is_printable(c)) {
      std::cout << "char: '" << c << "'" << std::endl;
    } else {
      std::cout << "char: Non displayable" << std::endl;
    }
  }

  if (val < INT_MIN || val > INT_MAX || std::isnan(val)) {
    std::cout << "int: impossible" << std::endl;
  } else {
    std::cout << "int: " << static_cast<int>(val) << std::endl;
  }

  std::cout << "float: " << static_cast<float>(val) << "f" << std::endl;
  std::cout << "double: " << val << std::endl;
}

static void print_pure_char(char c) {
  std::cout << "char: '" << c << "'" << std::endl;
  std::cout << "int: " << static_cast<int>(c) << std::endl;
  std::cout << "float: " << static_cast<float>(c) << "f" << std::endl;
  std::cout << "double: " << static_cast<double>(c) << std::endl;
}

static void print_impossible_all() {
  std::cout << "char: impossible" << std::endl;
  std::cout << "int: impossible" << std::endl;
  std::cout << "float: impossible" << std::endl;
  std::cout << "double: impossible" << std::endl;
}

static bool is_invalid_numeric_literal(const std::string &str,
                                       const char *end) {
  if (end == str.c_str()) {
    return true;
  }
  if (*end != '\0') {
    if (*end == 'f' && *(end + 1) == '\0') {
      return false;
    }
    return true;
  }
  return false;
}

void ScalarConverter::convert(const std::string &str) {
  if (is_pseudo_literal(str)) {
    handle_pseudo(str);
    return;
  }

  if (str.length() == 1 && !std::isdigit(str[0])) {
    print_pure_char(str[0]);
    return;
  }

  char *end;
  double val = std::strtod(str.c_str(), &end);

  if (is_invalid_numeric_literal(str, end)) {
    print_impossible_all();
    return;
  }

  print_all_types(val);
}
