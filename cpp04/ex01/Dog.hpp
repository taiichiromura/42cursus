#ifndef DOG_HPP
#define DOG_HPP

#include <iostream>
#include <string>
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public virtual Animal{
  private:
    Brain* brain;

  public:
    Dog();
	Dog(const Dog& other);
	Dog& operator=(const Dog& other);
	virtual ~Dog();

	void makeSound() const;
	std::string getType(void) const;

	void setIdea(int index, const std::string idea);
	std::string getIdea(int index) const;
};

#endif
