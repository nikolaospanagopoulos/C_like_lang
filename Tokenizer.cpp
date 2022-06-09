#include "Tokenizer.h"
#include <stdexcept>

std::vector<Token> Tokenizer::parse(const std::string &inProgram) {

  std::vector<Token> tokens{};

  Token currentToken{};
  currentToken.lineNumber = 1;
  for (char currentChar : inProgram) {

    if (currentToken.tType == STRING_ESCAPE_SEQUENCE) {
      switch (currentChar) {
      case 'n':
        currentToken.tokenText.append(1, currentChar);
        break;
      case 'r':
        currentToken.tokenText.append(1, currentChar);
        break;
      case 't':
        currentToken.tokenText.append(1, currentChar);
        break;
      case '\\':
        currentToken.tokenText.append(1, currentChar);
        break;
      default:
        throw std::runtime_error("unknown escape sequence: \\" +
                                 std::string(1, currentChar) + " on line " +
                                 std::to_string(currentToken.lineNumber));
      }
    }
    switch (currentChar) {

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      if (currentToken.tType == WHITESPACE) {
        currentToken.tType = INTEGER_LITERAL;
        currentToken.tokenText.append(1, currentChar);
      } else {

        currentToken.tokenText.append(1, currentChar);
      }
      break;

    case '{':
    case '}':
    case '(':
    case ')':
    case '=':
    case '-':
    case ';':
    case ',':
      if (currentToken.tType != STRING_LITERAL) {
        endToken(currentToken, tokens);
        currentToken.tType = OPERATOR;
        currentToken.tokenText.append(1, currentChar);
        endToken(currentToken, tokens);
      } else {
        currentToken.tokenText.append(1, currentChar);
      }
      break;
    case ' ':
    case '\t':
      endToken(currentToken, tokens);
      break;
    case '\r':
    case '\n':
      endToken(currentToken, tokens);
      ++currentToken.lineNumber;
      break;
    case '"':
      if (currentToken.tType != STRING_LITERAL) {
        endToken(currentToken, tokens);
        currentToken.tType = STRING_LITERAL;
        currentToken.tokenText.append(1, currentChar);
      } else if (currentToken.tType == STRING_LITERAL) {
        endToken(currentToken, tokens);
      }
      break;
    case '\\':
      if (currentToken.tType == STRING_LITERAL) {
        currentToken.tType = STRING_ESCAPE_SEQUENCE;
      } else {
        endToken(currentToken, tokens);
        currentToken.tType = OPERATOR;
        currentToken.tokenText.append(1, currentChar);
        endToken(currentToken, tokens);
      }

    default:
      break;
    }
  }
  return tokens;
}

void Tokenizer::endToken(Token &token, std::vector<Token> &tokens) {
  if (token.tType != WHITESPACE) {
    tokens.push_back(token);
  }
  token.tType = WHITESPACE;
  token.tokenText.erase();
}
