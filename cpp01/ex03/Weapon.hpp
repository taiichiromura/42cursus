#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon {
private:
    std::string _type;

public:
    Weapon();
    Weapon(std::string type);
    Weapon(const Weapon &src);
    Weapon &operator=(const Weapon &rhs);
    ~Weapon();

    const std::string &getType() const;
    void setType(std::string newType);
};

#endif
