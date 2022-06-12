#pragma once
#include "ParameterDefinition.h"
#include <vector>

class FunctionDefinition {
public:
  std::string functionName;
  std::vector<ParameterDefinition> functionParameters;

  void debugPrint() const;
};
