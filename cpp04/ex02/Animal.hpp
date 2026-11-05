#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include <string>

class Animal {
  protected:
	std::string type;
  public:
    Animal();
	Animal(const Animal& other);
	Animal& operator=(const Animal& other);
	virtual ~Animal();

	void virtual makeSound() const = 0;
	std::string virtual getType(void) const;

	virtual void setIdea(int index, const std::string idea);
    virtual std::string getIdea(int index) const;

};

#endif
