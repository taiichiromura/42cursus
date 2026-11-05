#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <climits>
#include <iomanip>
#include <iostream>
#include <string>

class ClapTrap {
 private:
  std::string _name;
  unsigned int _hitPoints;
  unsigned int _energyPoints;
  unsigned int _attackDamage;

  static unsigned int const _initHitPoints = 10;
  static unsigned int const _initEnergyPoints = 10;
  static unsigned int const _initAttackDamage = 0;

 public:
  ClapTrap();
  ClapTrap(const std::string& name);
  ClapTrap(const ClapTrap& other);
  ClapTrap& operator=(const ClapTrap& other);
  virtual ~ClapTrap();

  void attack(const std::string& target);
  void takeDamage(unsigned int amount);
  void beRepaired(unsigned int amount);
  void printStatus(void) const;
};

#endif
