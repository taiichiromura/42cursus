#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap() {
  this->_hitPoints = _initHitPoints;
  this->_energyPoints = _initEnergyPoints;
  this->_attackDamage = _initAttackDamage;
  std::cout << "ScavTrap " << this->_name << " appeared!" << std::endl;
  printStatus();
}

ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name) {
  std::cout << "ScavTrap " << this->_name << " is ready!" << std::endl;
  this->_hitPoints = _initHitPoints;
  this->_energyPoints = _initEnergyPoints;
  this->_attackDamage = _initAttackDamage;
  printStatus();
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other) {
  std::cout << "ScavTrap Copy constructor called" << std::endl;
  *this = other;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
  std::cout << "ScavTrap Copy assignment operator called" << std::endl;
  if (this != &other) {
    this->_name = other._name;
    this->_hitPoints = other._hitPoints;
    this->_energyPoints = other._energyPoints;
    this->_attackDamage = other._attackDamage;
  }
  return *this;
}

ScavTrap::~ScavTrap() {
  std::cout << "ScavTrap " << _name << " is gone!" << std::endl;
}

void ScavTrap::attack(const std::string& target) {
  if (this->_hitPoints <= 0 || this->_energyPoints <= 0) {
    std::cout << "ScavTrap " << _name << " is exhausted to attack..."
              << std::endl;
    return;
  }
  this->_energyPoints--;
  std::cout << "ScavTrap " << _name << " fiercely attacks " << target
            << ", dealing " << _attackDamage << " damage!" << std::endl;
}

void ScavTrap::takeDamage(unsigned int amount) {
  if (amount > static_cast<unsigned int>(_hitPoints)) {
    std::cout << "ScavTrap " << _name << " takes " << _hitPoints << " damage!"
              << std::endl;
    std::cout << "ScavTrap " << _name << " has no hit points" << std::endl;
    _hitPoints = 0;
    printStatus();
  } else {
    _hitPoints -= amount;
    std::cout << "ScavTrap " << _name << " takes " << amount << " damage!"
              << std::endl;
    printStatus();
  }
}

void ScavTrap::beRepaired(unsigned int amount) {
  if (_hitPoints <= 0 || _energyPoints <= 0) {
    std::cout << "ScavTrap " << _name << " can't repair!" << std::endl;
    return;
  }
  // 最大値までの残り空き容量よりも回復させたい量の方が多い場合、空き容量の分だけ回復,そうでなければ、指定された量だけ回復
  unsigned int actualAmount = (amount > _initHitPoints - _hitPoints)
                                  ? (_initHitPoints - _hitPoints)
                                  : amount;

  _energyPoints -= 1;
  if (amount > _initHitPoints - _hitPoints)
    _hitPoints = _initHitPoints;
  else
    _hitPoints += amount;
  std::cout << "ScavTrap " << _name << " repairs " << actualAmount << " points!"
            << std::endl;
  printStatus();
}

void ScavTrap::guardGate() {
  std::cout << "ScavTrap " << _name << " is now in Gate keeper mode!"
            << std::endl;
}
