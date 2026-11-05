#include "ScavTrap.hpp"

int main() {
  ScavTrap scav;
  scav.attack("Enemy");
  scav.takeDamage(20);
  scav.guardGate();
  scav.beRepaired(10);
  scav.takeDamage(200);
  scav.attack("Enemy");
  ClapTrap clap;
  clap.attack("Enemy");
  clap.takeDamage(20);
  clap.beRepaired(10);
  return 0;
}
