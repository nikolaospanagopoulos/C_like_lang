#include "Parser.h"
#include "ExceptionError.h"
#include <iostream>

bool Parser::expectFunctionDefinition() {

  std::vector<Token>::iterator parseStart = currentToken;
  std::optional<Type> possibleType = expectType();
  if (possibleType.has_value()) {
    std::optional<Token> possibleName = expectIdentifier();
    if (possibleName.has_value()) {
      std::optional<Token> possibleOperator = expectOperator("(");
      if (possibleOperator.has_value()) {
        // we have a function
        FunctionDefinition func;
        std::cout << "we have a function: " << possibleName->tokenText
                  << std::endl;

        func.functionName = possibleName->tokenText;
        while (!expectOperator(")").has_value()) {
          std::optional<Type> possibleParamType = expectType();
          if (!possibleParamType.has_value()) {
            throw Exception(
                "expected a type at start of argument/parameter list",
                currentToken->lineNumber);
          }
          std::optional<Token> possibleVariableName = expectIdentifier();
          ParameterDefinition param;
          param.parameterType = possibleParamType->typeName;

          if (possibleVariableName.has_value()) {
            param.parameterName = possibleVariableName->tokenText;
          }

          func.functionParameters.push_back(param);
          if (expectOperator(")").has_value()) {
            break;
          }
          // no comma , we break
          if (!expectOperator(",").has_value()) {
            throw Exception("function parameters shoulb be seperated by comma ",
                            currentToken->lineNumber);
          }
        }
        parseFunctionBody();
        functions[func.functionName] = func;
        return true;
      } else {

        currentToken = parseStart;
      }
    } else {
      currentToken = parseStart;
    }
  }
  return false;
}

void Parser::parse(std::vector<Token> &tokens) {
  currentToken = tokens.begin();
  endToken = tokens.end();

  while (currentToken != endToken) {
    if (expectFunctionDefinition()) {

    } else {
      // throw Exception("unknown identifier " + currentToken->tokenText,
      //                currentToken->lineNumber);
      std::cerr << "unknown identifier " + currentToken->tokenText << std::endl;
      ++currentToken;
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

bool Parser::parseFunctionBody() {

  if (!expectOperator("{").has_value()) {
    return false;
  }
  if (!expectOperator("}").has_value()) {
    throw Exception("unbalanced function ", currentToken->lineNumber);
  }

  return true;
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
  if (!possibleType.has_value()) {
    return std::nullopt;
  }
  std::map<std::string, Type>::iterator foundType =
      tTypes.find(possibleType->tokenText);
  if (foundType == tTypes.end()) {
    --currentToken;
    return std::nullopt;
  }
  return foundType->second;
}
void Parser::debugPrint() const {

  for (auto funcInfo : functions) {
    funcInfo.second.debugPrint();
  }
}

std::optional<Statement> Parser::parseOneStatement() {
  std::vector<Token>::iterator startToken = currentToken;
  std::optional<Type> possibleType = expectType();
  if (!possibleType.has_value()) {
    currentToken = startToken;
    return std::nullopt;
  }

  std::optional<Token> possibleVariableName = expectIdentifier();
  if (!possibleVariableName.has_value()) {
    currentToken = startToken;
    return std::nullopt;
  }
  Statement statement;

  statement.statementKind = StatementKind::VARIABLE_DECLERATION;
  statement.name = possibleVariableName->tokenText;
  statement.type = *possibleType;

  return statement;
}
