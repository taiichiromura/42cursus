#include <fstream>
#include <iostream>
#include <string>

std::string replaceAll(std::string content, const std::string& s1,
                       const std::string& s2) {
  if (s1.empty()) return content;

  std::string result;
  size_t pos = 0;
  size_t foundPos;

  while ((foundPos = content.find(s1, pos)) != std::string::npos) {
    result.append(content, pos, foundPos - pos);
    result += s2;
    pos = foundPos + s1.length();
  }
  result.append(content, pos, std::string::npos);
  return result;
}

int main(int ac, char** av) {
  if (ac != 4) {
    std::cerr << "Usage: ./sed_is_for_losers <filename> <s1> <s2>" << std::endl;
    return 1;
  }

  std::string filename = av[1];
  std::string s1 = av[2];
  std::string s2 = av[3];

  std::ifstream ifs(filename.c_str());
  if (!ifs.is_open()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return 1;
  }

  std::string content;
  char letter;
  while (ifs.get(letter)) {
    content += letter;
  }
  ifs.close();

  std::string newContent = replaceAll(content, s1, s2);

  std::ofstream ofs((filename + ".replace").c_str());
  if (!ofs.is_open()) {
    std::cerr << "Error: Could not create output file" << std::endl;
    return 1;
  }

  ofs << newContent;
  ofs.close();

  return 0;
}
