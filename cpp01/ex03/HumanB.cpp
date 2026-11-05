#include "HumanB.hpp"

HumanB::HumanB(const std::string name) : _name(name), _weapon(NULL) {}
HumanB::HumanB(const HumanB &src) { *this = src; }
HumanB &HumanB::operator=(const HumanB &rhs) {
  if (this != &rhs) {
    this->_name = rhs._name;
    this->_weapon = rhs._weapon;
  }
  return *this;
}
HumanB::~HumanB() {}

void HumanB::setWeapon(Weapon &weapon) { this->_weapon = &weapon; }

void HumanB::attack() const {
  if (_weapon) {
    std::cout << _name << " attacks with their " << _weapon->getType()
              << std::endl;
  } else {
    std::cout << _name << " has no weapon to attack with!" << std::endl;
  }
}
