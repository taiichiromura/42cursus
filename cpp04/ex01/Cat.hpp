#ifndef CAT_HPP
#define CAT_HPP

#include <iostream>
#include <string>
#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public virtual Animal{
  private:
    Brain* brain;

  public:
    Cat();
	Cat(const Cat& other);
	Cat& operator=(const Cat& other);
	virtual ~Cat();

	void makeSound() const;
	std::string getType(void) const;
	void setIdea(int index, const std::string idea);
	std::string getIdea(int index) const;
};

#endif
