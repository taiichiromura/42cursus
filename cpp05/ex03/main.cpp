#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

void test_intern_creates_presidential_pardon() {
  std::cout << "\n--- Test: Presidential Pardon ---" << std::endl;
  Intern some_intern;
  Bureaucrat ceo("The CEO", 1);
  AForm *form = NULL;

  form = some_intern.makeForm("presidential pardon", "TargetA");
  if (form != NULL) {
    std::cout << "SUCCESS: Form created -> " << form->getName() << std::endl;

    ceo.signForm(*form);
    ceo.executeForm(*form);

    delete form;
  } else {
    std::cout << "FAILURE: Form was NULL" << std::endl;
  }
}

void test_intern_creates_robotomy_request() {
  std::cout << "\n--- Test: Robotomy Request ---" << std::endl;
  Intern some_intern;
  Bureaucrat ceo("The CEO", 1);
  AForm *form = NULL;

  form = some_intern.makeForm("robotomy request", "Bender");
  if (form != NULL) {
    std::cout << "SUCCESS: Form created -> " << form->getName() << std::endl;

    ceo.signForm(*form);
    ceo.executeForm(*form);

    delete form;
  } else {
    std::cout << "FAILURE: Form was NULL" << std::endl;
  }
}

void test_intern_creates_shrubbery_creation() {
  std::cout << "\n--- Test: Shrubbery Creation ---" << std::endl;
  Intern some_intern;
  Bureaucrat ceo("The CEO", 1);
  AForm *form = NULL;

  form = some_intern.makeForm("shrubbery creation", "Garden");
  if (form != NULL) {
    std::cout << "SUCCESS: Form created -> " << form->getName() << std::endl;

    ceo.signForm(*form);
    ceo.executeForm(*form);

    delete form;
  } else {
    std::cout << "FAILURE: Form was NULL" << std::endl;
  }
}

void test_intern_creates_unknown_form_failure() {
  std::cout << "\n--- Test: Invalid Form ---" << std::endl;
  Intern some_intern;
  AForm *form = NULL;

  form = some_intern.makeForm("invalid request name", "Nobody");
  if (form == NULL) {
    std::cout << "SUCCESS: Correctly returned NULL for invalid form name."
              << std::endl;
  } else {
    std::cout << "FAILURE: Created an unknown form unexpectedly." << std::endl;
    delete form;
  }
}

int main() {
  std::srand(std::time(NULL));

  test_intern_creates_presidential_pardon();
  test_intern_creates_robotomy_request();
  test_intern_creates_shrubbery_creation();
  test_intern_creates_unknown_form_failure();

  return 0;
}
