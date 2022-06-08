#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {

  std::ifstream in_file;
  std::stringstream sstr;

  in_file.open("test1.myl");

  std::cout << "file contents read: " << std::endl;
  std::cout << "------------------------------" << std::endl;
  if (!in_file) {
    std::cerr << "preblem opening file" << std::endl;
    return 1;
  }

  while (in_file >> sstr.rdbuf()) {
    std::cout << sstr.str();
  }
  std::cout << "file contents end " << std::endl;
  std::cout << "------------------------------" << std::endl;
  return 0;
}
