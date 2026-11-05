#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>
#include <stdexcept>
#include <string>

class Bureaucrat;

class AForm {
private:
  const std::string _name;
  bool _sign;
  const int _gradeToSign;
  const int _gradeToExecute;

  void _checkGrades() const;

public:
  AForm(std::string const &name, bool sign, int gradeToSign,
        int gradeToExecute);
  AForm(const AForm &other);
  AForm &operator=(const AForm &other);
  virtual ~AForm();

  const std::string &getName() const;
  bool getSign() const;
  int getGradeToSign() const;
  int getGradeToExecute() const;

  class GradeTooHighException : public std::exception {
  public:
    virtual const char *what() const throw();
  };

  class GradeTooLowException : public std::exception {
  public:
    virtual const char *what() const throw();
  };

  class FormNotSignedException : public std::exception {
  public:
    virtual const char *what() const throw();
  };

  bool beSigned(Bureaucrat &obj);
  void execute(Bureaucrat const &executor) const;
  virtual void executeAction() const = 0;
};

std::ostream &operator<<(std::ostream &os, const AForm &obj);

#endif
