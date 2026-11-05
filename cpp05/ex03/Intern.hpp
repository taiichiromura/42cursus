#ifndef INTERN_HPP
#define INTERN_HPP

#include <iostream>
#include <string>

#include "AForm.hpp"

class Intern {
public:
  Intern();
  Intern(const Intern &other);
  Intern &operator=(const Intern &other);
  virtual ~Intern();

  AForm *makeForm(const std::string &formName, const std::string &formTarget);
};

#endif
