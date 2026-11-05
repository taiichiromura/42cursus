#include "Zombie.hpp"
#include <iostream>

int main() {
  int N = 5;

  Zombie *horde = zombieHorde(N, "HordeMember");
  if (!horde)
    return 1;

  for (int i = 0; i < N; i++) {
    std::cout << i << ": ";
    horde[i].announce();
  }

  delete[] horde;

  return 0;
}
