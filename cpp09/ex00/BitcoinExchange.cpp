#include "BitcoinExchange.hpp"

const std::string BitcoinExchange::DELIMITER = " | ";

BitcoinExchange::BitcoinExchange(){}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _exchangeRate(other._exchangeRate) {}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other){
  if (this != &other)
      _exchangeRate = other._exchangeRate;
  return *this;
}
BitcoinExchange::~BitcoinExchange(){}

ValueType BitcoinExchange::checkValue(const std::string &priceStr, float &price) const
{
    std::stringstream ss(priceStr);

    if (!(ss >> price) || ss.peek() != EOF)
        return VALUE_BAD_FORMAT;
    if (price < 0)
        return VALUE_NEGATIVE;
    if (price > 1000.0f)
        return VALUE_TOO_LARGE;
    return VALUE_OK;
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    for (size_t i = 0; i < date.length(); i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(static_cast<unsigned char>(date[i])))
            return false;
    }

    int year  = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day   = std::atoi(date.substr(8, 2).c_str());

    if (year < 2009 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;

	  //4で割り切れる年は、基本的にうるう年
    //ただし100で割り切れる年は、うるう年ではない
    //ただし400で割り切れる年は、やっぱりうるう年
    if (month == 2)
    {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if ((isLeap && day > 29) || (!isLeap && day > 28))
            return false;
    }
    return true;
}



bool BitcoinExchange::parseLine(const std::string &line, std::string &date, float &value) const
{
    size_t pipePos = line.find(BitcoinExchange::DELIMITER);

    if (pipePos == std::string::npos || pipePos + BitcoinExchange::DELIMITER.length() >= line.length()) {
        std::cerr << "Error: bad input => " << line << std::endl;
        return false;
    }

    date = line.substr(0, pipePos);
    std::string valueStr = line.substr(pipePos + BitcoinExchange::DELIMITER.length());

    if (!isValidDate(date)) {
        std::cerr << "Error: bad input  => " << line << std::endl;
        return false;
    }

    ValueType type = checkValue(valueStr, value);
    switch (type)
    {
        case VALUE_OK:
            return true;
        case VALUE_NEGATIVE:
            std::cerr << "Error: not a positive number." << std::endl;
            return false;
        case VALUE_TOO_LARGE:
            std::cerr << "Error: too large a number." << std::endl;
            return false;
        case VALUE_BAD_FORMAT:
     		std::cerr << "Error: bad input => " << line << std::endl;
            return false;
        default:
			break;
    }
	return type == VALUE_OK;
}

bool BitcoinExchange::processInputFile(std::string filename) {
  std::ifstream ifs(filename.c_str());
  if (!ifs.is_open()) {
	std::cerr << "Error: could not open file." << std::endl;
    return false;
  }
  std::string line;
  std::getline(ifs, line);

  while(std::getline(ifs, line)) {
    std::string date;
	float value;
	if (BitcoinExchange::parseLine(line, date, value)) {
	  std::map<std::string, float>::iterator it = this->_exchangeRate.lower_bound(date);
	  if (it == this->_exchangeRate.end())
        it--;
	  else if (it->first != date)
	  {
		if (it != this->_exchangeRate.begin())
		  --it;
		else
		{
		  std::cerr << "Error: no data available before " << date << std::endl;
		  continue;
		}
	  }
	  std::cout << date << " => " << value << " = " << (value * it->second) << std::endl;
    }
  }
  return true;
}

bool BitcoinExchange::loadLine(std::string line) {
  size_t pos = line.find(",");
  if (pos == std::string::npos)
	return false;

  std::string date = line.substr(0, pos);
  std::string priceStr = line.substr(pos + 1);

  if (!isValidDate(date))
    return false;
  float price;
  ValueType result = checkValue(priceStr, price);
  if (result != VALUE_OK)
    return false;
  this->_exchangeRate[date] = price;

  return true;
}


bool BitcoinExchange::loadExchangeRate(std::string filename) {
  if (filename == "") {
	std::cerr << "Error: no file input" << std::endl;
	return false;
  }

  std::ifstream ifs(filename.c_str());
  if (!ifs.is_open()) {
    std::cerr << "Error: could not open file." << std::endl;
    return false;
  }
  std::string line;
  std::getline(ifs, line);
  while(std::getline(ifs, line)) {
    loadLine(line);
  }
  ifs.close();
  return true;
}
