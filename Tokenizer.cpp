
#include "Tokenizer.h"
#include <iostream>
#include <stdexcept>

std::vector<Token> Tokenizer::parse(const std::string &inProgram) {

  std::vector<Token> tokens{};

  Token currentToken{};
  currentToken.lineNumber = 1;
  for (char currentChar : inProgram) {

    if (currentToken.tType == STRING_ESCAPE_SEQUENCE) {
      switch (currentChar) {
      case 'n':
        currentToken.tokenText.append(1, '\n');
        break;
      case 'r':
        currentToken.tokenText.append(1, '\r');
        break;
      case 't':
        currentToken.tokenText.append(1, '\t');
        break;
      case '\\':
        currentToken.tokenText.append(1, '\\');
        break;
      default:
        throw std::runtime_error("unknown escape sequence: \\" +
                                 std::string(1, currentChar) + " on line " +
                                 std::to_string(currentToken.lineNumber));
        break;
      }
      currentToken.tType = STRING_LITERAL;
      continue;
    } else if (currentToken.tType == POTENTIAL_COMMENT && currentChar != '/') {
      currentToken.tType = OPERATOR;
      endToken(currentToken, tokens);
      continue;
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
      }

      else if (currentToken.tType == POTENTIAL_DOUBLE) {
        currentToken.tType = DOUBLE_LITERAL;
        currentToken.tokenText.append(1, currentChar);
      }

      else {

        currentToken.tokenText.append(1, currentChar);
      }
      break;

    case '.':
      if (currentToken.tType == WHITESPACE) {
        currentToken.tType = POTENTIAL_DOUBLE;
        currentToken.tokenText.append(1, currentChar);
      }

      else if (currentToken.tType == INTEGER_LITERAL) {
        currentToken.tType = DOUBLE_LITERAL;
        currentToken.tokenText.append(1, currentChar);
      } else if (currentToken.tType == STRING_LITERAL) {
        currentToken.tokenText.append(1, currentChar);
      }

      // here maybe error for second dot in double literal . ex 1..5

      else {
        endToken(currentToken, tokens);
        currentToken.tType = OPERATOR;
        currentToken.tokenText.append(1, currentChar);
        endToken(currentToken, tokens);
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
      if (currentToken.tType == STRING_LITERAL ||
          currentToken.tType == COMMENT) {
        currentToken.tokenText.append(1, currentChar);

      } else {

        endToken(currentToken, tokens);
      }
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

      break;
    case '/':
      if (currentToken.tType == STRING_LITERAL) {

        currentToken.tokenText.append(1, currentChar);
      } else if (currentToken.tType == POTENTIAL_COMMENT) {
        currentToken.tType = COMMENT;
        currentToken.tokenText.erase();
      } else {
        endToken(currentToken, tokens);
        currentToken.tType = POTENTIAL_COMMENT;
        currentToken.tokenText.append(1, currentChar);
      }
      break;
    default:
      if (currentToken.tType == WHITESPACE ||
          currentToken.tType == INTEGER_LITERAL ||
          currentToken.tType == DOUBLE_LITERAL) {
        endToken(currentToken, tokens);
        currentToken.tType = IDENTIFIER;
        currentToken.tokenText.append(1, currentChar);

      } else {
        currentToken.tokenText.append(1, currentChar);
      }
      break;
    }
  }
  endToken(currentToken, tokens);
  return tokens;
}

void Tokenizer::endToken(Token &token, std::vector<Token> &tokens) {
  if (token.tType == COMMENT) {
    std::cout << "ignoring comment: " << token.tokenText << std::endl;
  } else if (token.tType != WHITESPACE) {
    tokens.push_back(token);
  }

  if (token.tType == POTENTIAL_DOUBLE) {
    if (token.tokenText.compare(".") == 0) {
      token.tType = OPERATOR;
    } else {
      token.tType = DOUBLE_LITERAL;
    }
  }
  token.tType = WHITESPACE;
  token.tokenText.erase();
}
void Token::debugPrintTokens() const {

  std::cout << "Token(" << arrayOfTypes[tType] << ", \"" << tokenText << "\","
            << "    line      : " << lineNumber << ")" << std::endl;
}
