#include "DiamondTrap.hpp"

void DiamondTrap::printStatus(void) const {
  std::cout << std::setw(15) << "NAME";
  std::cout << std::setw(10) << "HP";
  std::cout << std::setw(10) << "EP";
  std::cout << std::setw(10) << "AD" << std::endl;
  std::cout << std::string(45, '-') << std::endl;

  std::cout << std::setw(15) << _name;
  std::cout << std::setw(10) << _hitPoints;
  std::cout << std::setw(10) << _energyPoints;
  std::cout << std::setw(10) << _attackDamage << std::endl;
  std::cout << std::endl;
}

DiamondTrap::DiamondTrap()
    : ClapTrap("Diamond_clap_name"), ScavTrap(), FragTrap(), _name("Diamond") {
  std::cout << "DiamondTrap " << this->_name << " finally created!"
            << std::endl;
  this->_hitPoints = FragTrap::_initHitPoints;
  this->_energyPoints = ScavTrap::_initEnergyPoints;
  this->_attackDamage = FragTrap::_initAttackDamage;
  printStatus();
}

DiamondTrap::DiamondTrap(const std::string& name)
    : ClapTrap(name + "_clap_name"), ScavTrap(), FragTrap(), _name(name) {
  std::cout << "DiamondTrap " << this->_name << " finally created!"
            << std::endl;
  this->_hitPoints = FragTrap::_initHitPoints;
  this->_energyPoints = ScavTrap::_initEnergyPoints;
  this->_attackDamage = FragTrap::_initAttackDamage;
  printStatus();
}

DiamondTrap::~DiamondTrap() {
  std::cout << "DiamondTrap " << this->_name << " destroyed!" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& other)
    : ClapTrap(other), ScavTrap(other), FragTrap(other) {
  std::cout << "DiamondTrap Copy constructor called" << std::endl;
  *this = other;
  printStatus();
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other) {
  std::cout << "DiamondTrap assignment operator called" << std::endl;
  if (this != &other) {
    this->_name = other._name;
    ClapTrap::_name = other.ClapTrap::_name;
    this->_hitPoints = other._hitPoints;
    this->_energyPoints = other._energyPoints;
    this->_attackDamage = other._attackDamage;
  }
  return *this;
}

void DiamondTrap::attack(const std::string& target) {
  ScavTrap::attack(target);
}

void DiamondTrap::takeDamage(unsigned int amount) {
  if (amount > static_cast<unsigned int>(_hitPoints)) {
    std::cout << "DiamondTrap " << _name << " has no hit points" << std::endl;
    std::cout << "DiamondTrap " << _name << " takes " << _hitPoints
              << " damage!" << std::endl;
    _hitPoints = 0;
    printStatus();
  } else {
    _hitPoints -= amount;
    std::cout << "DiamondTrap " << _name << " takes " << amount << " damage!"
              << std::endl;
    printStatus();
  }
}

void DiamondTrap::beRepaired(unsigned int amount) {
  if (_hitPoints <= 0 || _energyPoints <= 0) {
    std::cout << "DiamondTrap " << _name << " can't repair!" << std::endl;
    return;
  }
  // 最大値までの残り空き容量よりも回復させたい量の方が多い場合、空き容量の分だけ回復,そうでなければ、指定された量だけ回復
  unsigned int actualAmount = (amount > FragTrap::_hitPoints - _hitPoints)
                                  ? (FragTrap::_hitPoints - _hitPoints)
                                  : amount;

  _energyPoints -= 1;
  if (amount > FragTrap::_hitPoints - _hitPoints)
    _hitPoints = FragTrap::_hitPoints;
  else
    _hitPoints += amount;
  std::cout << "DiamondTrap " << _name << " repairs " << actualAmount
            << " points!" << std::endl;
  printStatus();
}

void DiamondTrap::whoAmI() {
  std::cout << "My name is " << this->_name << " and my ClapTrap name is "
            << ClapTrap::_name << std::endl;
}
