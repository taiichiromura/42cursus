#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include <string>

class Bureaucrat;

class Form {
private:
  const std::string _name;
  bool _sign;
  const int _gradeToSign;
  const int _gradeToExecute;
  void _checkGrades() const;

  Form();

public:
  Form(const std::string &name, int gradeToSign, int gradeToExecute);
  Form(const Form &other);
  Form &operator=(const Form &other);
  ~Form();
  const std::string getName() const;
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
};

std::ostream &operator<<(std::ostream &os, const Form &obj);


#endif
