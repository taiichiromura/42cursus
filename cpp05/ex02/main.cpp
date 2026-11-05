#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

void test_shrubbery_execution_success() {
  try {
    Bureaucrat elite_bureaucrat("EliteSato", 1);
    ShrubberyCreationForm valid_shrubbery("home");

    elite_bureaucrat.signForm(valid_shrubbery);
    elite_bureaucrat.executeForm(valid_shrubbery);
  } catch (const std::exception &e) {
    std::cout << "FAILURE: " << e.what() << std::endl;
  }
}

void test_shrubbery_execution_failure_not_signed() {
  try {
    Bureaucrat elite_bureaucrat("EliteSato2", 1);
    ShrubberyCreationForm unsigned_shrubbery("garden");

    elite_bureaucrat.executeForm(unsigned_shrubbery);
  } catch (const std::exception &e) {
    std::cout << "FAILURE: " << e.what() << std::endl;
  }
}

void test_robotomy_execution_success() {
  try {
    Bureaucrat manager_bureaucrat("ManagerTanaka", 40);
    RobotomyRequestForm valid_robotomy("Bender");

    manager_bureaucrat.signForm(valid_robotomy);
    manager_bureaucrat.executeForm(valid_robotomy);
  } catch (const std::exception &e) {
    std::cout << "FAILURE: " << e.what() << std::endl;
  }
}

void test_robotomy_execution_failure_low_grade() {
  try {
    Bureaucrat low_bureaucrat("StaffSuzuki", 80);
    RobotomyRequestForm high_robotomy("Wall-E");

    low_bureaucrat.signForm(high_robotomy);
    low_bureaucrat.executeForm(high_robotomy);
  } catch (const std::exception &e) {
    std::cout << "FAILURE: " << e.what() << std::endl;
  }
}

void test_presidential_execution_success() {
  try {
    Bureaucrat boss_bureaucrat("ThePresident", 1);
    PresidentialPardonForm valid_pardon("Criminal");

    boss_bureaucrat.signForm(valid_pardon);
    boss_bureaucrat.executeForm(valid_pardon);
  } catch (const std::exception &e) {
    std::cout << "FAILURE: " << e.what() << std::endl;
  }
}

void test_presidential_execution_failure_insufficient_execute_grade() {
  try {
    Bureaucrat semi_boss_bureaucrat("VicePresident", 10);
    PresidentialPardonForm tough_pardon("Prisoner");

    semi_boss_bureaucrat.signForm(tough_pardon);
    semi_boss_bureaucrat.executeForm(tough_pardon);
  } catch (const std::exception &e) {
    std::cout << "FAILURE: " << e.what() << std::endl;
  }
}

int main() {
  std::srand(std::time(NULL));
  test_shrubbery_execution_success();
  test_shrubbery_execution_failure_not_signed();

  test_robotomy_execution_success();
  test_robotomy_execution_failure_low_grade();

  test_presidential_execution_success();
  test_presidential_execution_failure_insufficient_execute_grade();

  return 0;
}
