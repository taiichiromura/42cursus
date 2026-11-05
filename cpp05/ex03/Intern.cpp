#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

Intern::Intern() {}

Intern::Intern(const Intern &other) { (void)other; }

Intern &Intern::operator=(const Intern &other) {
  (void)other;
  return *this;
}

Intern::~Intern() {}

AForm *Intern::makeForm(const std::string &formName,
                        const std::string &formTarget) {
  std::string formNames[3];
  formNames[0] = "presidential pardon";
  formNames[1] = "robotomy request";
  formNames[2] = "shrubbery creation";

  int formNum = -1;
  for (int i = 0; i < 3; i++) {
    if (formNames[i] == formName) {
      formNum = i;
      break;
    }
  }

  AForm *result = NULL;
  switch (formNum) {
  case 0:
    result = new PresidentialPardonForm(formTarget);
    break;
  case 1:
    result = new RobotomyRequestForm(formTarget);
    break;
  case 2:
    result = new ShrubberyCreationForm(formTarget);
    break;
  default:
    std::cout << "Error: Form name '" << formName << "' does not exist."
              << std::endl;
    return NULL;
  }

  std::cout << "Intern creates " << result->getName() << std::endl;
  return result;
}
