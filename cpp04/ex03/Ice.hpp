#ifndef ICE_HPP
# define ICE_HPP
# include <iostream>
# include "AMateria.hpp"
# include "ICharacter.hpp"

class Ice : public AMateria
{
public:
	Ice(void);
	Ice(std::string const & type);
	Ice(Ice const & input);
	Ice const & operator=(Ice const & input);
	virtual ~Ice(void);
	std::string const & getType(void) const;
	AMateria*	clone(void) const;
	void		use(ICharacter & target);
};

#endif
