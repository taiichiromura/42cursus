#include "Cat.hpp"

Cat::Cat() : Animal() {
  this->type = "Cat";
  this->brain = new Brain();
  std::cout << "Cat is born!" << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other) {
  this->brain = new Brain();
  *this = other;
}

Cat &Cat::operator=(const Cat &other) {
  if (this == &other)
    return *this;
  this->type = other.type;
  if (this->brain) {
    delete this->brain;
    this->brain = new Brain(*other.brain);
  }
  return *this;
}

Cat::~Cat() {
  delete this->brain;
  std::cout << type << " is dead." << std::endl;
}

void Cat::makeSound() const { std::cout << "nyaa!" << std::endl; }

std::string Cat::getType(void) const {
  return this->type;
}

std::string Cat::getIdea(int index) const {
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

void Cat::setIdea(int index, const std::string idea) {
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
