#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
    : AForm("ShrubberyCreationForm", false, 145, 137), _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
    : AForm(other), _target(other._target) {}

ShrubberyCreationForm &
ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) {
  if (this != &other) {
    AForm::operator=(other);
    this->_target = other._target;
  }
  return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::executeAction() const {
  std::ofstream outputfile((this->getTarget() + "_shrubbery").c_str());

  if (!outputfile.is_open()) {
    return;
  }
  outputfile << "                    .o00o\n"
             << "           o000000oo\n"
             << "          00000000000o\n"
             << "         00000000000000\n"
             << "      oooooo  00000000  o88o\n"
             << "   ooOOOOOOOoo  ```''  888888\n"
             << "  OOOOOOOOOOOO'.qQQQQq. `8888'\n"
             << " oOOOOOOOOOO'.QQQQQQQQQQ/.88'\n"
             << " OOOOOOOOOO'.QQQQQQQQQQ/ /q\n"
             << "  OOOOOOOOO QQQQQQQQQQ/ /QQ\n"
             << "    OOOOOOOOO `QQQQQQ/ /QQ'\n"
             << "      OO:F_P:O `QQQ/  /Q'\n"
             << "         \\\\. \\ |  // |\n"
             << "         d\\ \\\\\\|_////\n"
             << "         qP| \\\\ _' `|Ob\n"
             << "           \\  / \\  \\Op\n"
             << "           |  | O| |\n"
             << "    _      /\\. \\_/ /\\\n"
             << "     `---__/|_\\\\   //|  __\n"
             << "           `-'  `-'`-'-'\n";

  outputfile.close();
}

const std::string &ShrubberyCreationForm::getTarget() const {
  return this->_target;
}
