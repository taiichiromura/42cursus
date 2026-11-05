#include "Animal.hpp"

Animal::Animal() : type("default") {
  std::cout << "Animal " << this->type << " is born !" << std::endl;
}

Animal::Animal(const Animal &other) { *this = other; }

Animal &Animal::operator=(const Animal &other) {
  if (this != &other) {
    this->type = other.type;
  }
  return *this;
}

Animal::~Animal() { std::cout << "Animal is dead." << std::endl; }

void Animal::makeSound() const {
  std::cout << "Animal " << this->type << " made a sound" << std::endl;
}

const std::string &Animal::getType(void) const { return this->type; }
