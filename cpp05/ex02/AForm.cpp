#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(std::string const &name, bool sign, int gradeToSign,
             int gradeToExecute)
    : _name(name), _sign(sign), _gradeToSign(gradeToSign),
      _gradeToExecute(gradeToExecute) {
  this->_checkGrades();
}

AForm::AForm(const AForm &other)
    : _name(other._name), _sign(other._sign), _gradeToSign(other._gradeToSign),
      _gradeToExecute(other._gradeToExecute) {}

AForm &AForm::operator=(const AForm &other) {
  if (this != &other) {
    this->_sign = other._sign;
  }
  return *this;
}

AForm::~AForm() {}

const std::string &AForm::getName() const { return this->_name; }

bool AForm::getSign() const { return this->_sign; }

int AForm::getGradeToSign() const { return this->_gradeToSign; }

int AForm::getGradeToExecute() const { return this->_gradeToExecute; }

bool AForm::beSigned(Bureaucrat &obj) {
  if (obj.getGrade() <= this->getGradeToSign()) {
    this->_sign = true;
    return true;
  } else {
    throw AForm::GradeTooLowException();
  }
}

void AForm::execute(Bureaucrat const &executor) const {
  if (this->getSign() != true) {
    throw AForm::FormNotSignedException();
  }
  if (executor.getGrade() > this->getGradeToExecute()) {
    throw AForm::GradeTooLowException();
  }
  if (executor.getGrade() <= 0) {
    throw AForm::GradeTooHighException();
  }
  this->executeAction();
}

void AForm::_checkGrades() const {
  if (this->_gradeToSign < 1 || this->_gradeToExecute < 1) {
    throw AForm::GradeTooHighException();
  }
  if (this->_gradeToSign > 150 || this->_gradeToExecute > 150) {
    throw AForm::GradeTooLowException();
  }
}

const char* AForm::GradeTooHighException::what() const throw() {
  return "Grade is too high!";
}

const char* AForm::GradeTooLowException::what() const throw() {
  return "Grade is too low!";
}

const char* AForm::FormNotSignedException::what() const throw() {
  return "Form is not signed yet.";
}

std::ostream& operator<<(std::ostream& os, const AForm& form) {
    os << " Form Name is " << form.getName()
       << " Signed: " << (form.getSign() ? "Yes" : "No")
       << ", Sign Grade: " << form.getGradeToSign()
       << ", Execute Grade: " << form.getGradeToExecute();
    return os;
}
