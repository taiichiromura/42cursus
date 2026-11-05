#include <csignal>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "ConfigParser.hpp"
#include "ConfigServer.hpp"
#include "Server.hpp"
#include "Utils.hpp"

static std::vector<ConfigServer> loadServers(const std::string& configPath) {
  std::string file;
  if (!readFileToString(configPath, file))
    throw std::runtime_error("Could not open config file");

  ConfigParser conf_parse;
  ConfigServer conf_serv;
  conf_parse.splitConfToServers(file, &conf_serv);

  std::vector<ConfigServer> parsed_servers = conf_parse.getServers();
  if (parsed_servers.empty())
    throw std::runtime_error("No server config parsed!");

  return parsed_servers;
}

int main(int argc, char const* argv[]) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: ./webserv [config_file]" << std::endl;
      return 1;
    }
    struct sigaction sa;
    std::memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handleShutdownSignal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    signal(SIGPIPE, SIG_IGN);
    std::srand(std::time(NULL));

    std::vector<ConfigServer> parsed_servers = loadServers(argv[1]);

    Server serv;
    serv.createSocketAndEpoll(parsed_servers);
    serv.run(parsed_servers);

  } catch (const std::exception& e) {
    std::cerr << "Critical Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
