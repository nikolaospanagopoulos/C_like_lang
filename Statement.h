#pragma once
#include "Type.h"
#include <string>
#include <vector>

enum class StatementKind {

  VARIABLE_DECLERATION,
  FUNCTION_CALL
};

class Statement {

public:
  std::string name;
  Type type;
  std::vector<Statement> parameters;
  void debugPrint() const;
  StatementKind statementKind{StatementKind::FUNCTION_CALL};
};
