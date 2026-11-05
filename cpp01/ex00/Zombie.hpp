#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>
#include <string>

class Zombie {
private:
  std::string _name;

public:
  Zombie();
  Zombie(const Zombie &name);
  Zombie &operator=(const Zombie &rhs);
  ~Zombie();

  Zombie(const std::string &name);
  void announce(void) const;
};

Zombie *newZombie(const std::string &name);
void randomChump(const std::string &name);

#endif
