#pragma once
#include "Tokenizer.h"
#include "Type.h"
#include <map>
#include <optional>
#include <vector>

class Parser {

public:
  Parser();
  ~Parser() = default;
  void parse(std::vector<Token> &tokens);

private:
  std::optional<Type> expectType();
  std::optional<Token> expectIdentifier(const std::string &name = "");
  std::optional<Token> expectOperator(const std::string &name = "");

  std::vector<Token>::iterator currentToken;
  std::vector<Token>::iterator endToken;
  std::map<std::string, Type> tTypes;
};
