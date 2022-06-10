#include "Parser.h"
#include <iostream>
void Parser::parse(std::vector<Token> &tokens) {
  currentToken = tokens.begin();
  endToken = tokens.end();

  while (currentToken != endToken) {
    std::optional<Type> possibleType = expectType();
    if (possibleType.has_value()) {
      std::optional<Token> possibleName = expectIdentifier();
      if (possibleName.has_value()) {
        std::optional<Token> possibleOperator = expectOperator("(");
        if (possibleOperator.has_value()) {
          // we have a function
          std::cout << "we have a function: " << possibleName->tokenText
                    << std::endl;
          exit(0);
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

Parser::Parser() {

  tTypes["int"] = Type("signed int", INT32);
  tTypes["unsigned"] = Type("unsigned int", UINT32);
  tTypes["char"] = Type("signed char", INT8);
  tTypes["uint8_t"] = Type("uint8_t", INT8);
  tTypes["void"] = Type("void", VOID);
}

std::optional<Type> Parser::expectType() {

  std::optional<Token> possibleType = expectIdentifier();
  std::map<std::string, Type>::iterator foundType =
      tTypes.find(possibleType->tokenText);
  if (foundType == tTypes.end()) {
    return std::nullopt;
  }
  return foundType->second;
}
