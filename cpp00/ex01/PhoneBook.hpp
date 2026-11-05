#ifndef PHONEBOOK_HPP

# define PHONEBOOK_HPP

# include "Contact.hpp"


class	PhoneBook
{
	private:
		Contact _contacts[8];
		int		_index;
		bool	_isfull;
	public:
		PhoneBook(void);
		~PhoneBook(void);
		void	add(void);
		void	search(void);
		void	print(void);
		Contact get_contact(int	index);

		std::string	get_str(std::string str);
		std::string	get_input(std::string type);
};

#endif
