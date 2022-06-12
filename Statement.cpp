#include "Statement.h"
#include <iostream>

void Statement::debugPrint() const {

  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << type.typeName << " " << name << " ";

  for (auto statement : parameters) {
    statement.debugPrint();
  }
  std::cout << std::endl;
}
