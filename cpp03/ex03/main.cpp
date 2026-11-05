#include "DiamondTrap.hpp"

int main() {
  std::cout << "--- DiamondTrap Birth ---" << std::endl;
  DiamondTrap dt("dt");
  // 1. 名前とClapTrap名の確認
  dt.whoAmI();

  // 2. 攻撃 
  dt.attack("an enemy");

  // 3. 特殊能力 (両方の親から引き継いでいるか)
  dt.guardGate();      // ScavTrap から
  dt.highFivesGuys();  // FragTrap から

  std::cout << "\n--- Status Check ---" << std::endl;
  // ダメージを受けて HP(FragTrap:100) を確認
  dt.takeDamage(30);
  dt.beRepaired(UINT_MAX);
  dt.takeDamage(UINT_MAX);
  dt.takeDamage(UINT_MAX);

  std::cout << "\n--- Destruction ---" << std::endl;
  return 0;
}
