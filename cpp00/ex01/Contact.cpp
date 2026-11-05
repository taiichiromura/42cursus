#include "Contact.hpp"

Contact::Contact()
{
}

Contact::~Contact()
{
}

void Contact::set_first_name(std::string first_name)
{
	_first_name = first_name;
}

void Contact::set_last_name(std::string last_name)
{
	_last_name = last_name;
}

void Contact::set_nick_name(std::string nick_name)
{
	_nick_name = nick_name;
}

void Contact::set_phone_number(std::string phone_number)
{
	_phone_number = phone_number;
}

void Contact::set_secret(std::string secret)
{
	_secret = secret;
}

std::string Contact::get_first_name() const
{
	return _first_name;
}

std::string Contact::get_last_name() const
{
	return _last_name;
}

std::string Contact::get_nick_name() const
{
	return _nick_name;
}

std::string Contact::get_phone_number() const
{
	return _phone_number;
}

std::string Contact::get_secret() const
{
	return _secret;
}
