#include "Cat.hpp"

Cat::Cat() : Animal() {
  this->type = "Cat";
  std::cout << this->type << " is born !" << std::endl;
}

Cat::Cat(const Cat &other) : Animal() { *this = other; }

Cat &Cat::operator=(const Cat &other) {
  if (this != &other) {
    this->type = other.type;
  }
  return *this;
}

Cat::~Cat() { std::cout << "Cat is dead." << std::endl; }

void Cat::makeSound() const { std::cout << "meow" << std::endl; }
