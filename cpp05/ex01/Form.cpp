#include "Form.hpp"
#include "Bureaucrat.hpp"

// Form::Form(){};

Form::Form(const std::string &name, int gradeToSign, int gradeToExecute)
    : _name(name), _sign(false), _gradeToSign(gradeToSign),
      _gradeToExecute(gradeToExecute) {
  this->_checkGrades();
}
Form::Form(const Form &other)
    : _name(other._name), _sign(other._sign), _gradeToSign(other._gradeToSign),
      _gradeToExecute(other._gradeToExecute) {}

Form &Form::operator=(const Form &other) {
  if (this != &other) {
    this->_sign = other._sign;
  }
  return *this;
}
Form::~Form() {}
void Form::_checkGrades() const {
  if (this->_gradeToSign < 1 || this->_gradeToExecute < 1) {
    throw Form::GradeTooHighException();
  }
  if (this->_gradeToSign > 150 || this->_gradeToExecute > 150) {
    throw Form::GradeTooLowException();
  }
}

const std::string Form::getName() const { return this->_name; }

bool Form::getSign() const { return this->_sign; }

int Form::getGradeToSign() const { return this->_gradeToSign; }

int Form::getGradeToExecute() const { return this->_gradeToExecute; }

bool Form::beSigned(Bureaucrat &obj) {
  if (obj.getGrade() <= this->getGradeToSign()) {
    this->_sign = true;
    return true;
  } else {
    throw Form::GradeTooLowException();
  }
}

const char* Form::GradeTooHighException::what() const throw() {
  return "Grade is too high!";
}

const char* Form::GradeTooLowException::what() const throw() {
  return "Grade is too low!";
}

const char* Form::FormNotSignedException::what() const throw() {
  return "Form is not signed yet.";
}

std::ostream& operator<<(std::ostream& os, const Form& form) {
    os << " Form Name is " << form.getName()
       << " Signed: " << (form.getSign() ? "Yes" : "No")
       << ", Sign Grade: " << form.getGradeToSign()
       << ", Execute Grade: " << form.getGradeToExecute();
    return os;
}
