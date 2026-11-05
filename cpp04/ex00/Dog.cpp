#include "Dog.hpp"

Dog::Dog() : Animal() {
  this->type = "Dog";
  std::cout << this->type << " is born !" << std::endl;
}

Dog::Dog(const Dog &other) : Animal() { *this = other; }

Dog &Dog::operator=(const Dog &other) {
  if (this != &other) {
    this->type = other.type;
  }
  return *this;
}

Dog::~Dog() { std::cout << "Dog is dead." << std::endl; }

void Dog::makeSound() const { std::cout << "Wan!" << std::endl; }
