#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie() : _name("") {}

Zombie::Zombie(const Zombie &src) {
  std::cout << "Copy constructor called" << std::endl;
  *this = src;
}

Zombie &Zombie::operator=(const Zombie &rhs) {
  std::cout << "Copy assignment operator called" << std::endl;
  if (this != &rhs) {
    this->_name = rhs._name;
  }
  return *this;
}
Zombie::~Zombie() {
  std::cout << "Zombie " << this->_name << " is destroyed." << std::endl;
}

void Zombie::announce() const {
  std::cout << this->_name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setName(const std::string &name) { this->_name = name; }
