#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <climits>
#include <iomanip>
#include <iostream>
#include <string>

class ClapTrap {
 private:
  static unsigned int const _initHitPoints = 10;
  static unsigned int const _initEnergyPoints = 10;
  static unsigned int const _initAttackDamage = 0;

 protected:
  std::string _name;
  unsigned int _hitPoints;
  unsigned int _energyPoints;
  unsigned int _attackDamage;

 public:
  ClapTrap();
  ClapTrap(const std::string& name);
  ClapTrap(const ClapTrap& other);
  ClapTrap& operator=(const ClapTrap& other);
  virtual ~ClapTrap();

  void virtual attack(const std::string& target);
  void virtual takeDamage(unsigned int amount);
  void virtual beRepaired(unsigned int amount);
  void printStatus(void) const;
};

#endif
