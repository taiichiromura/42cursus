#include "Weapon.hpp"

Weapon::Weapon() : _type("default") {}

Weapon::Weapon(std::string type) : _type(type) {}

Weapon::Weapon(const Weapon &src) {
    *this = src;
} 

Weapon &Weapon::operator=(const Weapon &rhs) {
    if (this != &rhs) {
        this->_type = rhs._type;
    }
    return *this;
}

Weapon::~Weapon() {}

const std::string &Weapon::getType() const { return this->_type; }

void Weapon::setType(std::string newType) { this->_type = newType; }
