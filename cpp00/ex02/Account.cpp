#include "Account.hpp"
#include <iomanip>
#include <iostream>
#include <ctime>

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

Account::Account(int initial_deposit)
{
	Account::_displayTimestamp();
	std::cout << "index:" << _nbAccounts << ";" << "amount:" <<
	initial_deposit << ";" << "created";
	this->_accountIndex = _nbAccounts;
	_nbAccounts++;
	this->_amount = initial_deposit;
	_totalAmount = _totalAmount + initial_deposit;
	std::cout << std::endl;
	(void)initial_deposit;
}

Account::~Account(void)
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";" << "amount:" <<
	this->_amount  << ";" << "closed";
	std::cout << std::endl;
};

int	Account::getNbAccounts( void )
{
	return _nbAccounts;
}
int	Account::getTotalAmount( void )
{
	return _totalAmount;
}
int	Account::getNbDeposits( void )
{
	return _totalNbDeposits;
}
int	Account::getNbWithdrawals( void )
{
	return _totalNbWithdrawals;
}
void Account::displayAccountsInfos( void )
{
	Account::_displayTimestamp();
	std::cout << "accounts:" << _nbAccounts << ";" <<
	"total:" << _totalAmount << ";" << "deposits:" << _totalNbDeposits << ";" <<
	"withdrawals:" << _totalNbWithdrawals << std::endl;
}

void Account::makeDeposit( int deposit )
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";"
	<< "p_amount:" << this->_amount << ";"
	<< "deposit:" << deposit << ";";
	this->_amount = this->_amount + deposit;
	_totalAmount = _totalAmount + deposit;
	this->_nbDeposits++;
	_totalNbDeposits++;
	std::cout << "amount:" << this->_amount << ";"
	<< "nb_deposits:" << this->_nbDeposits;
	std::cout << std::endl;
}

bool Account::makeWithdrawal( int withdrawal )
{
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";"
	<< "p_amount:" << this->_amount << ";";
	if (withdrawal > this->_amount)
	{
		std::cout << "withdrawal:refused" << std::endl;
		return (false);
	}
	this->_amount = this->_amount - withdrawal;
	_totalAmount = _totalAmount - withdrawal;
	this->_nbWithdrawals++;
	_totalNbWithdrawals++;
	std::cout << "withdrawal:" << withdrawal << ";"
	<< "amount:" << this->_amount << ";"
	<< "nb_withdrawals:" << this->_nbWithdrawals;
	std::cout << std::endl;
	return (true);
}

int Account::checkAmount( void ) const
{
	return 1;
}

void Account::displayStatus( void ) const
{
	Account::_displayTimestamp();
	std::cout << "index:" <<this->_accountIndex << ";"
	<< "amount:" << this->_amount << ";"
	<< "deposits:" << this->_nbDeposits << ";"
	<< "withdrawals:" << this->_nbWithdrawals;
	std::cout << std::endl;
}

void	Account::_displayTimestamp()
{
	std::time_t t = std::time(NULL);
  	std::tm* local_time = std::localtime(&t);

	char buffer[20];
	std::strftime(buffer, sizeof(buffer), "[%Y%m%d_%H%M%S] ", local_time);
	std::cout << buffer;
}
