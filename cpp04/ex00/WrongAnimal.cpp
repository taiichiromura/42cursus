#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() {
  this->type = "WrongAnimal";
  std::cout << "WrongAnimal is born !" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &other) { *this = other; }

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &other) {
  if (this != &other) {
    this->type = other.type;
  }
  return *this;
}

WrongAnimal::~WrongAnimal() {
  std::cout << "Wrong Animal is dead." << std::endl;
}

void WrongAnimal::makeSound() const { std::cout << "Wrong!" << std::endl; }

const std::string &WrongAnimal::getType(void) const { return this->type; }
