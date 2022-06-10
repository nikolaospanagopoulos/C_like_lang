#pragma once
#include "Tokenizer.h"
#include <optional>
#include <vector>

class Parser {

public:
  void parse(std::vector<Token> &tokens);

private:
  std::optional<Token> expectIdentifier(const std::string &name = "");
  std::optional<Token> expectOperator(const std::string &name = "");

  std::vector<Token>::iterator currentToken;
  std::vector<Token>::iterator endToken;
};
