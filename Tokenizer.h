#pragma once
#include <string>
#include <vector>

enum TokenType {

  WHITESPACE,
  IDENTIFIER,
  INTEGER_LITERAL,
  DOUBLE_LITERAL,
  STRING_LITERAL,
  OPERATOR,
  STRING_ESCAPE_SEQUENCE
};

class Token {

public:
  TokenType tType{WHITESPACE};
  std::string tokenText;
  size_t startOffset{};
  size_t endOffset{};
  size_t lineNumber{};
};
class Tokenizer {
public:
  std::vector<Token> parse(const std::string &inProgram);

private:
  void endToken(Token &token, std::vector<Token> &tokens);
};
