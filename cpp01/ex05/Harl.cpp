#include "Harl.hpp"

Harl::Harl() {}
Harl::Harl(const Harl &src) { *this = src; }
Harl &Harl::operator=(const Harl &rhs) {
  (void)rhs;
  return *this;
}
Harl::~Harl() {}

void Harl::debug(void) {
  std::cout << "[ DEBUG ]\nI love having extra bacon... I really do!"
            << std::endl;
}

void Harl::info(void) {
  std::cout
      << "[ INFO ]\nI cannot believe adding extra bacon costs more money..."
      << std::endl;
}

void Harl::warning(void) {
  std::cout
      << "[ WARNING ]\nI think I deserve to have some extra bacon for free..."
      << std::endl;
}

void Harl::error(void) {
  std::cout
      << "[ ERROR ]\nThis is unacceptable! I want to speak to the manager now."
      << std::endl;
}

void Harl::complain(std::string level) {
  void (Harl::*functions[])(void) = {&Harl::debug, &Harl::info, &Harl::warning,
                                     &Harl::error};

  std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

  for (int i = 0; i < 4; i++) {
    if (levels[i] == level) {
      (this->*functions[i])();
      return;
    }
  }
}
