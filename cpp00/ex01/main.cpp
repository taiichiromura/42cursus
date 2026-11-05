#include <iostream>
#include "PhoneBook.hpp"

int	main()
{
	PhoneBook phonebook;
	std::string cmd;

	while(1)
	{
		std::cout << "Enter command:";
		std::getline(std::cin, cmd);
		if (cmd == "ADD")
			phonebook.add();
		else if (cmd == "SEARCH")
			phonebook.search();
		else if (cmd == "EXIT")
			break;
		else
			std::cout << "invalid command" << std::endl;
	}
}
