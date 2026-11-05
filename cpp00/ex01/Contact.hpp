#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <iostream>
# include <string>

class Contact
{
	private:
		std::string _first_name;
		std::string _last_name;
		std::string _nick_name;
		std::string _phone_number;
		std::string _secret;
	public:
		Contact();
		~Contact();
		void set_first_name(std::string);
		void set_last_name(std::string);
		void set_nick_name(std::string);
		void set_phone_number(std::string);
		void set_secret(std::string);

		std::string get_first_name() const;
		std::string get_last_name() const;
		std::string get_nick_name() const;
		std::string get_phone_number() const;
		std::string get_secret() const;
};

#endif
