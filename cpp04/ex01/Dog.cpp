#include "Dog.hpp"

Dog::Dog() : Animal() {
  this->type = "Dog";
  this->brain = new Brain();
  std::cout << "Dog is born!" << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other) {
  this->brain = new Brain();
  *this = other;
}

Dog &Dog::operator=(const Dog &other) {
  if (this == &other)
    return *this;
  this->type = other.type;
  if (this->brain) {
    delete this->brain;
    this->brain = new Brain(*other.brain);
  }
  return *this;
}

Dog::~Dog() {
  delete this->brain;
  std::cout << "Dog is dead." << std::endl;
}

void Dog::makeSound() const { std::cout << "wan!" << std::endl; }

std::string Dog::getType(void) const { return this->type; }

std::string Dog::getIdea(int index) const {
  if (!this->brain) {
    return "No brain available";
  }
  if (index < 0 || index >= this->brain->ideaSize) {
    return "Index out of range!";
  }
  if (this->brain->ideas[index].empty()) {
    return "No idea at this index";
  }
  return this->brain->ideas[index];
}

void Dog::setIdea(int index, const std::string idea) {
  if (index < 0 || index >= this->brain->ideaSize) {
      std::cout << "Index out of range!" << std::endl;
      return;
  }
  if (!this->brain->ideas[index].empty()) {
      std::cout << "An idea already exists at index " << index << "!" << std::endl;
      return;
  }
  this->brain->ideas[index] = idea;
}
