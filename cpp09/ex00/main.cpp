#include "BitcoinExchange.hpp"

int  main(int argc, char **argv) {
  if (argc != 2){
    std::cerr << "Usage: ./btc [input_file]" << std::endl;
    return 1;
  }
  BitcoinExchange btc;

  if (!btc.loadExchangeRate("data.csv"))
  	return 1;

  if (!btc.processInputFile(argv[1]))
  	return 1;
  return 0;
}
