#include "ClapTrap.hpp"

void ClapTrap::printStatus(void) const {
  // ヘッダーと区切り線
  std::cout << std::setw(15) << "NAME";
  std::cout << std::setw(10) << "HP";
  std::cout << std::setw(10) << "EP";
  std::cout << std::setw(10) << "AD" << std::endl;
  std::cout << std::string(45, '-') << std::endl;

  // データ本体
  std::cout << std::setw(15) << _name;
  std::cout << std::setw(10) << _hitPoints;
  std::cout << std::setw(10) << _energyPoints;
  std::cout << std::setw(10) << _attackDamage << std::endl;
  std::cout << std::endl;
}

ClapTrap::ClapTrap()
    : _name("ClapDefault"),
      _hitPoints(_initHitPoints),
      _energyPoints(_initEnergyPoints),
      _attackDamage(_initAttackDamage) {
  std::cout << "ClapTrap ClapDefault created!" << std::endl;
  printStatus();
}

ClapTrap::ClapTrap(const std::string& name)
    : _name(name),
      _hitPoints(_initHitPoints),
      _energyPoints(_initEnergyPoints),
      _attackDamage(_initAttackDamage) {
  std::cout << "ClapTrap " << this->_name << " created" << std::endl;
  printStatus();
}

ClapTrap::ClapTrap(const ClapTrap& other) {
  std::cout << "ClapTrap Copy constructor called" << std::endl;
  *this = other;
  printStatus();
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other) {
  std::cout << "ClapTrap Copy assignment operator called" << std::endl;
  if (this != &other) {
    this->_name = other._name;
    this->_hitPoints = other._hitPoints;
    this->_energyPoints = other._energyPoints;
    this->_attackDamage = other._attackDamage;
  }
  return *this;
}

ClapTrap::~ClapTrap() {
  std::cout << "ClapTrap " << _name << " is destroyed" << std::endl;
}

void ClapTrap::attack(const std::string& target) {
  if (_hitPoints <= 0 || _energyPoints <= 0) {
    std::cout << "ClapTrap " << _name << " has no points left to attack"
              << std::endl;
    return;
  }
  _energyPoints--;
  std::cout << "ClapTrap " << _name << " attacks " << target << " ,causing "
            << _attackDamage << " points of damage!" << std::endl;
  printStatus();
}

void ClapTrap::takeDamage(unsigned int amount) {
  if (amount > static_cast<unsigned int>(_hitPoints)) {
    std::cout << "ClapTrap " << _name << " takes " << _hitPoints << " damage!"
              << std::endl;
    std::cout << "ClapTrap " << _name << " has no hit points" << std::endl;
    _hitPoints = 0;
    printStatus();

  } else {
    _hitPoints -= amount;
    std::cout << "ClapTrap " << _name << " takes " << amount << " damage!"
              << std::endl;
    printStatus();
  }
}

void ClapTrap::beRepaired(unsigned int amount) {
  if (_hitPoints <= 0 || _energyPoints <= 0) {
    std::cout << "ClapTrap " << _name << " can't repair!" << std::endl;
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
  std::cout << "ClapTrap " << _name << " repairs " << actualAmount << " points!"
            << std::endl;
  printStatus();
}
