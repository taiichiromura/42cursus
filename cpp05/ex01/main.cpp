#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

void test_bureaucrat_initialization_with_minimum_valid_grade() {
  try {
    Bureaucrat valid_low_bureaucrat("LowLevel", 150);
    std::cout << "SUCCESS: " << valid_low_bureaucrat << std::endl;
  } catch (const std::exception &e) {
    std::cout << "FAILURE: " << e.what() << std::endl;
  }
}

void test_bureaucrat_initialization_with_grade_too_low() {
  try {
    Bureaucrat invalid_low_bureaucrat("TooLow", 151);
    std::cout << "FAILURE: Exception not thrown" << std::endl;
  } catch (const std::exception &e) {
    std::cout << "SUCCESS: " << e.what() << std::endl;
  }
}

void test_bureaucrat_initialization_with_grade_too_high() {
  try {
    Bureaucrat invalid_high_bureaucrat("TooHigh", 0);
    std::cout << "FAILURE: Exception not thrown" << std::endl;
  } catch (const std::exception &e) {
    std::cout << "SUCCESS: " << e.what() << std::endl;
  }
}

void test_bureaucrat_increment_beyond_maximum_limit() {
  try {
    Bureaucrat max_grade_bureaucrat("The Boss", 1);
    max_grade_bureaucrat.incrementGrade();
    std::cout << "FAILURE: Exception not thrown" << std::endl;
  } catch (const std::exception &e) {
    std::cout << "SUCCESS: " << e.what() << std::endl;
  }
}

void test_bureaucrat_decrement_beyond_minimum_limit() {
  try {
    Bureaucrat min_grade_bureaucrat("The Minion", 150);
    min_grade_bureaucrat.decrementGrade();
    std::cout << "FAILURE: Exception not thrown" << std::endl;
  } catch (const std::exception &e) {
    std::cout << "SUCCESS: " << e.what() << std::endl;
  }
}

void test_form_initialization_with_valid_grades() {
  try {
    Form valid_form("TaxForm", 100, 50);
    std::cout << "SUCCESS:" << valid_form << std::endl;
  } catch (const std::exception &e) {
    std::cout << "FAILURE: " << e.what() << std::endl;
  }
}

void test_form_initialization_with_sign_grade_too_low() {
  try {
    Form invalid_form("InvalidForm", 160, 50);
    std::cout << "FAILURE: Exception not thrown" << std::endl;
  } catch (const std::exception &e) {
    std::cout << "SUCCESS: " << e.what() << std::endl;
  }
}

void test_form_signing_by_bureaucrat_with_insufficient_grade() {
  try {
    Form high_tier_form("TopSecretPaper", 10, 10);
    Bureaucrat low_grade_bureaucrat("Staff T", 50);

    low_grade_bureaucrat.signForm(high_tier_form);
  } catch (const std::exception &e) {
    std::cout << "FAILURE: " << e.what() << std::endl;
  }
}

void test_form_signing_by_bureaucrat_with_sufficient_grade() {
  try {
    Form low_tier_form("PublicPaper", 50, 50);
    Bureaucrat high_grade_bureaucrat("Elite S", 1);

    high_grade_bureaucrat.signForm(low_tier_form);
  } catch (const std::exception &e) {
    std::cout << "FAILURE: " << e.what() << std::endl;
  }
}

int main() {
  test_bureaucrat_initialization_with_minimum_valid_grade();
  test_bureaucrat_initialization_with_grade_too_low();
  test_bureaucrat_initialization_with_grade_too_high();

  test_bureaucrat_increment_beyond_maximum_limit();
  test_bureaucrat_decrement_beyond_minimum_limit();

  test_form_initialization_with_valid_grades();
  test_form_initialization_with_sign_grade_too_low();

  test_form_signing_by_bureaucrat_with_insufficient_grade();
  test_form_signing_by_bureaucrat_with_sufficient_grade();

  return 0;
}
