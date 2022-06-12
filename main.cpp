#include "ExceptionError.h"
#include "Parser.h"
#include "Tokenizer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

  try {

    while (in_file >> sstr.rdbuf()) {
      std::cout << sstr.str();
    }
    std::cout << "file contents end " << std::endl;
    std::cout << "------------------------------" << std::endl;

    Tokenizer tokenizer;
    std::vector<Token> tokens = tokenizer.parse(sstr.str());

    std::cout << "TOKEN INFO" << std::endl;
    std::cout << '\n' << std::endl;
    for (auto token : tokens) {
      token.debugPrintTokens();
    }

    std::cout << "END TOKEN INFO" << std::endl;

    std::cout << '\n';
    std::cout << '\n';
    std::cout << '\n';
    std::cout << "---------PARSE----------" << std::endl;

    Parser parser;
    parser.parse(tokens);

    parser.debugPrint();
    return 0;

  } catch (Exception &e) {

    e.outputMesage();
    return 1;
  }
}
