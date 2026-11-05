#include "Bureaucrat.hpp"
#include "AForm.hpp"

// Bureaucrat::Bureaucrat() : _name("default"), _grade(150) {}

Bureaucrat::Bureaucrat(const std::string &name, int grade)
    : _name(name), _grade(grade) {
  this->_checkGrade();
}

Bureaucrat::Bureaucrat(const Bureaucrat &other)
    : _name(other._name), _grade(other._grade) {}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other) {
  if (this != &other) {
    this->_grade = other._grade;
  }
  return *this;
}

Bureaucrat::~Bureaucrat() {
  std::cout << "Bureaucrat " << this->_name << " fired." << std::endl;
}

const std::string &Bureaucrat::getName() const { return this->_name; }

int Bureaucrat::getGrade() const { return this->_grade; }

void Bureaucrat::signForm(AForm &form) {
  try {
    form.beSigned(*this);
    std::cout << this->_name << " signed " << form.getName() << std::endl;
  } catch (const std::exception &e) {
    std::cout << this->_name << " couldn’t sign " << form.getName()
              << " because " << e.what() << std::endl;
  }
}

void Bureaucrat::executeForm(AForm const &form) const {
  try {
    form.execute(*this);
    std::cout << this->_name << " executed " << form.getName() << std::endl;
  } catch (const std::exception &e) {
    std::cout << this->_name << " couldn't execute " << form.getName()
              << " because " << e.what() << std::endl;
  }
}

void Bureaucrat::incrementGrade() {
  if (this->_grade - 1 < 1)
    throw Bureaucrat::GradeTooHighException();
  this->_grade--;
}

void Bureaucrat::decrementGrade() {
  if (this->_grade + 1 > 150) {
    throw Bureaucrat::GradeTooLowException();
  }
  this->_grade++;
}

std::ostream &operator<<(std::ostream &os, const Bureaucrat &obj) {
  os << obj.getName() << ", bureaucrat grade " << obj.getGrade() << ".";
  return os;
}

void Bureaucrat::_checkGrade() const {
  if (this->_grade < 1) {
    throw Bureaucrat::GradeTooHighException();
  }
  if (this->_grade > 150) {
    throw Bureaucrat::GradeTooLowException();
  }
}

const char* Bureaucrat::GradeTooHighException::what() const throw() {
    return "Grade is too high!";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
    return "Grade is too low!";
}
