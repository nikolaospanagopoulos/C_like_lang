#include "Parser.h"
#include <iostream>
void Parser::parse(std::vector<Token> &tokens) {
  currentToken = tokens.begin();
  endToken = tokens.end();

  while (currentToken != tokens.end()) {
    std::optional<Token> possibleType = expectIdentifier();
    if (possibleType.has_value()) {
      std::optional<Token> possibleName = expectIdentifier();
      if (possibleName.has_value()) {
        std::optional<Token> possibleOperator = expectOperator("(");
        if (possibleOperator.has_value()) {
          // we have a function
          std::cout << "we have a function: " << possibleName->tokenText
                    << std::endl;
        }
      }
    }
  }
}

std::optional<Token> Parser::expectIdentifier(const std::string &name) {

  if (currentToken == endToken) {
    return std::nullopt;
  }

  if (currentToken->tType != IDENTIFIER) {
    return std::nullopt;
  }

  if (!name.empty() && currentToken->tokenText != name) {

    return std::nullopt;
  }

  Token returnToken = *currentToken;
  ++currentToken;
  return returnToken;
}

std::optional<Token> Parser::expectOperator(const std::string &name) {

  if (currentToken == endToken) {
    return std::nullopt;
  }

  if (currentToken->tType != OPERATOR) {
    return std::nullopt;
  }

  if (!name.empty() && currentToken->tokenText != name) {

    return std::nullopt;
  }

  Token returnToken = *currentToken;
  ++currentToken;
  return returnToken;
}
