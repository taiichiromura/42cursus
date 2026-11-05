#include "ClapTrap.hpp"

int main() {
  std::cout << "デフォルトコンストラクタ、基本機能、最大値のテスト"
            << std::endl;
  ClapTrap claptrap1;
  claptrap1.attack("Enemy");
  claptrap1.takeDamage(5);
  claptrap1.beRepaired(UINT_MAX);
  claptrap1.beRepaired(UINT_MAX);
  claptrap1.takeDamage(10);
  claptrap1.attack("Enemy2");
  claptrap1.beRepaired(10);
  std::cout << "\n" << std::endl;

  std::cout << "--コピーコンストラクタのテスト--" << std::endl;
  ClapTrap copytrap(claptrap1);
  copytrap.attack("Enemy3");
  claptrap1.takeDamage(5);
  claptrap1.takeDamage(5);
  copytrap.takeDamage(5);

  std::cout << "\n" << std::endl;
  std::cout << "-- 代入演算子のテスト --" << std::endl;
  ClapTrap trap_a("trap_a");
  ClapTrap trap_b("trap_b");
  trap_b = trap_a;  // trap_bの名前やステータスがAと同じになるか
  trap_b.takeDamage(1);


  std::cout << "\n" << std::endl;
  std::cout << "-- 死亡後のテスト --" << std::endl;
  ClapTrap zombie;
  zombie.takeDamage(100);
  zombie.attack("Target");
  zombie.beRepaired(10);

  std::cout << "\n" << std::endl;
  std::cout << "-- EP切れのテスト --" << std::endl;
  ClapTrap ep_test;
  for (int i = 0; i < 11; i++) ep_test.attack("Target");
  ep_test.beRepaired(10);

  return 0;
}
