#include "FunctionDefinition.h"
#include <iostream>

void FunctionDefinition::debugPrint() const {

  std::cout << "function debugging" << std::endl;

  std::cout << "function name: " << functionName << std::endl;
  std::cout << "(" << std::endl;

  for (auto parameter : functionParameters) {
    std::cout << "parameter name: " << parameter.parameterName << std::endl;
    std::cout << "parameter type: " << parameter.parameterType.typeName
              << std::endl;
  }

  std::cout << ")" << std::endl;
}
