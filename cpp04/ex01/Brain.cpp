#include "Brain.hpp"

Brain::Brain() { std::cout << "Brain created." << std::endl; }

Brain::Brain(const Brain &other) {
  std::cout << "Brain copy constructor called." << std::endl;
  *this = other;
}

Brain &Brain::operator=(const Brain &other) {
  std::cout << "Brain assignment operator called." << std::endl;
  if (this == &other)
    return *this;
  for (int i = 0; i < 100; i++)
    this->ideas[i] = other.ideas[i];
  return *this;
}

Brain::~Brain() { std::cout << "Brain destroyed." << std::endl; }
