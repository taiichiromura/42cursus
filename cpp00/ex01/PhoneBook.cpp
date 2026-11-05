#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>

PhoneBook::PhoneBook()
{
	_index = 0;
	_isfull = false;
}
PhoneBook::~PhoneBook(){}

void	PhoneBook::add()
{
	this->_contacts[_index].set_first_name(get_input("first name"));
	this->_contacts[_index].set_last_name(get_input("last name"));
	this->_contacts[_index].set_nick_name(get_input("nickname"));
	this->_contacts[_index].set_phone_number(get_input("phone number"));
	this->_contacts[_index].set_secret(get_input("darkest secret"));
	this->_index++;
	std::cout << "\n";
	if (_index == 8)
	{
		this->_isfull = true;
		this->_index = 0;
	}
}

void	PhoneBook::search()
{
	int	i = 0;

	std::cout << "\n";
	if (this->_index == 0 && this->_isfull == false)
	{
		std::cout << "No contacts to print!\n" << "\n";
		return;
	}
	std::cout << std::setw(10) << "INDEX"  << '|' << std::setw(10) << "FIRST_NAME" << '|'
	<< std::setw(10) << "LAST_NAME" << '|' << std::setw(10) << "NICKNAME" << "\n"
	<< std::setw(43) << std::setfill('-') << "" << std::setfill(' ') << std::endl;

	int limit;

	if (this->_isfull == true)
    	limit = 8;
	else
    	limit = this->_index;
	while(i < limit)
	{
		std::cout << std::setw(10) << i + 1 << '|' <<
		std::setw(10) << get_str(this->_contacts[i].get_first_name()) << '|' <<
		std::setw(10) << get_str(this->_contacts[i].get_last_name()) << '|' <<
		std::setw(10) << get_str(this->_contacts[i].get_nick_name()) << "\n";
		i++;
	}
	std::cout << std::setw(43) << std::setfill('-') << "" << std::setfill(' ') << "\n";
	std::cout << "\n";
	this->print();
}

void	PhoneBook::print()
{
	std::string	input;
	std::cout << "Enter the index of the contacts to print:\n";
	while(1)
	{
		std::getline(std::cin, input);
		if (input.length() == 1 && ((this->_isfull == true && input[0] >= '1' && input[0] <= '8')
				|| (this->_isfull == false && input[0] >= '1' && input[0] < this->_index + '1')))
		{
			std::cout << "\n"
			<< std::setw(15) << std::left << "first name"
			<< std::setw(0) << this->_contacts[input[0] - '1'].get_first_name()
			<< "\n" << std::setw(15) << std::left << "last name"
			<< std::setw(0) << this->_contacts[input[0] - '1'].get_last_name()
			<< "\n" << std::setw(15) << std::left << "nickname"
			<< std::setw(0) << this->_contacts[input[0] - '1'].get_nick_name()
			<< "\n" << std::setw(15) << std::left << "phone number"
			<< std::setw(0) << this->_contacts[input[0] - '1'].get_phone_number()
			<< "\n" << std::setw(15) << std::left << "darkest secret"
			<< std::setw(0) << this->_contacts[input[0] - '1'].get_secret()
			<< "\n" << "\n";
			return;
		}
		std::cout << "invalid input:\n> ";
	}
}

std::string	PhoneBook::get_str(std::string str)
{
	if (str.length() <= 10)
		return (str);
	else
		return (str.substr(0,9).append("."));
}

std::string	PhoneBook::get_input(std::string type)
{
	std::string	input;

	std::cout << "\n"
	<< "Please enter the " << type << ":\n> ";
	while(input.empty())
	{
		std::getline(std::cin, input);
		if (!input.empty())
			break;
		std::cout << "empty input! try again:\n> ";
	}
	return (input);
}
