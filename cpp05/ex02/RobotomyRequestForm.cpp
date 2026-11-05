#include "RobotomyRequestForm.hpp"
#include <cstdlib>
#include <ctime>

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
    : AForm("RobotomyRequestForm", false, 72, 45), _target(target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other)
    : AForm(other), _target(other._target) {}

RobotomyRequestForm &
RobotomyRequestForm::operator=(const RobotomyRequestForm &other) {
  if (this != &other) {
    AForm::operator=(other);
    this->_target = other._target;
  }
  return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {}

static bool isSuccessFiftyFifty() { return (std::rand() % 2 == 0); }

void RobotomyRequestForm::executeAction() const {
  std::cout << "* BZZZZZZZZZZZZZZZ!!! DRILLING NOISES *" << std::endl;
  std::cout << "Now Hollowing out the brain through the skull in order to be "
               "smart...."
            << std::endl;

  if (isSuccessFiftyFifty()) {
    std::cout << this->getTarget() << " has been robotomized successfully."
              << std::endl;
  } else {
    std::cout << "The robotomy on " << this->getTarget() << " failed."
              << std::endl;
  }
}

const std::string &RobotomyRequestForm::getTarget() const {
  return this->_target;
}
