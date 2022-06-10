#pragma once
#include <array>
#include <string>
#include <vector>

enum TokenType {

  POTENTIAL_COMMENT,
  COMMENT,
  WHITESPACE,
  IDENTIFIER,
  INTEGER_LITERAL,
  DOUBLE_LITERAL,
  POTENTIAL_DOUBLE,
  STRING_LITERAL,
  OPERATOR,
  STRING_ESCAPE_SEQUENCE
};

static const std::array<std::string, 10> arrayOfTypes{

    "POTENTIAL_COMMENT",
    "COMMENT",
    "WHITESPACE",
    "IDENTIFIER",
    "INTEGER_LITERAL",
    "DOUBLE_LITERAL",
    "POTENTIAL_DOUBLE",
    "STRING_LITERAL",
    "OPERATOR",
    "STRING_ESCAPE_SEQUENCE"

};

class Token {

public:
  TokenType tType{WHITESPACE};
  std::string tokenText;
  size_t lineNumber{};

  void debugPrintTokens() const;
};
class Tokenizer {
public:
  std::vector<Token> parse(const std::string &inProgram);

private:
  void endToken(Token &token, std::vector<Token> &tokens);
};
