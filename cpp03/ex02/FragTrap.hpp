#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

class FragTrap : public ClapTrap {
 private:
  static unsigned int const _initHitPoints = 100;
  static unsigned int const _initEnergyPoints = 100;
  static unsigned int const _initAttackDamage = 30;

 public:
  FragTrap();
  FragTrap(const std::string& name);
  FragTrap(const FragTrap& other);
  FragTrap& operator=(const FragTrap& other);
  virtual ~FragTrap();

  void attack(const std::string& target);
  void beRepaired(unsigned int amount);
  void takeDamage(unsigned int amount);

  void highFivesGuys(void);
};

#endif
