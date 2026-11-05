#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cctype>
#include <map>

enum ValueType {
    VALUE_OK,
    VALUE_BAD_FORMAT,
    VALUE_NEGATIVE,
    VALUE_TOO_LARGE
};

class BitcoinExchange {
private:
  std::map<std::string, float> _exchangeRate;
  static const std::string DELIMITER;
  
public:
  BitcoinExchange();
  BitcoinExchange(const BitcoinExchange &other);
  BitcoinExchange &operator=(const BitcoinExchange &other);
  ~BitcoinExchange();

  bool loadExchangeRate(std::string filename);
  bool loadLine(std::string line);
  bool processInputFile(std::string filename);
  bool parseLine(const std::string &line, std::string &date, float &value) const;
  bool isValidDate(const std::string &date) const;
  ValueType checkValue(const std::string &priceStr, float &price) const;


};
