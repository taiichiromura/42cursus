#include "HumanA.hpp"

HumanA::HumanA(const std::string &name, Weapon &weapon)
    : _name(name), _weapon(weapon) {}

HumanA::HumanA(const HumanA &src) : _name(src._name), _weapon(src._weapon) {}

HumanA &HumanA::operator=(const HumanA &rhs) {
  if (this != &rhs) {
    this->_name = rhs._name;
  }
  return *this;
}

HumanA::~HumanA() {}

void HumanA::attack() const {
  std::cout << _name << " attacks with their " << _weapon.getType()
            << std::endl;
}
