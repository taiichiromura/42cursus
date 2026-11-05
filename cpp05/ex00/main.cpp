#include "Bureaucrat.hpp"

void regular_create() {
  try {
    Bureaucrat c("regular_create", 2);
    std::cout << "SUCCESS: " << c << std::endl;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}

void irregular_create_over() {
  try {
    Bureaucrat d("irregular_create", 151);
    std::cout << "SUCCESS: " << d << std::endl;
  } catch (std::exception &e) {
    std::cout << "FAILURE: " << e.what() << std::endl;
  }
}

void irregular_create_under() {
  try {
    Bureaucrat d("irregular_create", 0);
    std::cout << "SUCCESS: " << d << std::endl;
  } catch (std::exception &e) {
    std::cout << "FAILURE: " << e.what() << std::endl;
  }
}

void regular_increment(Bureaucrat &a) {
  try {
    a.incrementGrade();
    std::cout << "SUCCESS: " << a << std::endl;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}

void irregular_increment(Bureaucrat &a) {
  try {
    a.incrementGrade();
    std::cout << "SUCCESS: " << a << std::endl;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}

void regular_decrement(Bureaucrat &a) {
  try {
    a.decrementGrade();
    std::cout << "SUCCESS: " << a << std::endl;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}

void irregular_decrement(Bureaucrat &a) {
  try {
    a.decrementGrade();
    std::cout << "SUCCESS: " << a << std::endl;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}

int main() {
  regular_create();
  irregular_create_over();
  irregular_create_under();
  Bureaucrat p("jack", 2);
  regular_increment(p);
  irregular_increment(p);
  Bureaucrat n("marcom", 149);
  regular_decrement(n);
  irregular_decrement(n);
}
