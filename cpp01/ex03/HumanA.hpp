#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "Weapon.hpp"
#include <iostream>
#include <string>

class HumanA {
private:
  std::string _name;
  Weapon &_weapon;
  HumanA();

public:
  HumanA(const std::string &name, Weapon &weapon);
  HumanA(const HumanA &src);
  HumanA &operator=(const HumanA &rhs);
  ~HumanA();

  void attack(void) const;
};

#endif

