#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"
#include <iostream>

class HumanB {
private:
  std::string _name;
  Weapon *_weapon;

public:
  HumanB();
  HumanB(const std::string name);
  HumanB(const HumanB &src);
  HumanB &operator=(const HumanB &rhs);
  ~HumanB();
  void setWeapon(Weapon &weapon);
  void attack() const;
};

#endif
