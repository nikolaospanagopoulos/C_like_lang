#pragma once

#include <iostream>
#include <string>

class Exception {

private:
  std::string message;
  int lineNumber;

public:
  Exception(std::string errorMessage = "", int line = 1)
      : message(errorMessage), lineNumber(line) {}
  void outputMesage() {
    std::cerr << message << " on line: " << lineNumber << std::endl;
  }
};
