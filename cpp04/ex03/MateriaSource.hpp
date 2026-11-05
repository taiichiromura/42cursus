#ifndef MATERIA_HPP
#define MATERIA_HPP

#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{
  private:
    AMateria* _mSlot[4];
  public:
	MateriaSource();
	MateriaSource(std::string const & type);
	MateriaSource(const MateriaSource& materia);
	MateriaSource& operator=(const MateriaSource& materia);
	virtual ~MateriaSource();
	void learnMateria(AMateria*);
	AMateria* createMateria(std::string const & type);
};

#endif
