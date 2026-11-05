#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie {
private:
  std::string _name;

public:
  Zombie();
  Zombie(const Zombie &src);
  Zombie &operator=(const Zombie &rhs);
  ~Zombie();

  void announce() const;
  void setName(const std::string &name);
};
Zombie *zombieHorde(int N, const std::string &name);

#endif
