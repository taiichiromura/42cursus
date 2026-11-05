#include "Zombie.hpp"

Zombie::Zombie(const std::string &name) : _name(name) {
  std::cout << _name << " is coming...\n" << std::endl;
}

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
Zombie::~Zombie() { std::cout << _name << " died.\n" << std::endl; }

void Zombie::announce() const {
  std::cout << _name << ": BraiiiiiiinnnzzzZ...\n" << std::endl;
}
