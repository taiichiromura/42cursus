#include "WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal() {
  this->type = "WrongCat";
  std::cout << "WrongCat is born !" << std::endl;
}

WrongCat::WrongCat(const WrongCat &other) : WrongAnimal() { *this = other; }

WrongCat &WrongCat::operator=(const WrongCat &other) {
  if (this != &other) {
    this->type = other.type;
  }
  return *this;
}

WrongCat::~WrongCat() { std::cout << "Wrong Cat is dead." << std::endl; }

void WrongCat::makeSound() const { std::cout << "Wrong Cat!" << std::endl; }
