#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>

class Brain {
  public:
	static const int ideaSize = 100;
	std::string ideas[ideaSize];

	Brain();
	Brain(const Brain& other);
	Brain& operator=(const Brain &other);
	virtual ~Brain();
};

#endif
