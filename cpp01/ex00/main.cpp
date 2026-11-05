#include "Zombie.hpp"

int main() {
  Zombie *zombie1 = NULL;

  try {
    zombie1 = newZombie("zombie1");
    zombie1->announce();
    delete zombie1;
    zombie1 = NULL;
  } catch (const std::bad_alloc &e) {
    std::cerr << "Error: Memory allocation failed: " << e.what() << std::endl;
    return 1;
  }

  randomChump("zombie2");
}
