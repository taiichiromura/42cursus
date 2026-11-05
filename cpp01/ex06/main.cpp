#include "Harl.hpp"

int main(int ac, char **av) {
  if (ac != 2) {
    std::cerr << "Usage: ./harlFilter <LEVEL>" << std::endl;
    return 1;
  }

  Harl harl;
  harl.complain(av[1]);

  return 0;
}
