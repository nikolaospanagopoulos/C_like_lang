#pragma once
#include "FunctionDefinition.h"
#include "Statement.h"
#include "Tokenizer.h"
#include "Type.h"
#include <map>
#include <optional>
#include <vector>

class Parser {

public:
  Parser();
  ~Parser() = default;
  void debugPrint() const;
  void parse(std::vector<Token> &tokens);

private:
  bool expectFunctionDefinition();
  std::optional<Type> expectType();
  std::optional<Token> expectIdentifier(const std::string &name = "");
  std::optional<Token> expectOperator(const std::string &name = "");

  std::optional<Statement> parseOneStatement();
  bool parseFunctionBody();
  std::vector<Token>::iterator currentToken;
  std::vector<Token>::iterator endToken;
  std::map<std::string, Type> tTypes;
  std::map<std::string, FunctionDefinition> functions;
};
