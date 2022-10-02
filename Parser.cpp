//
// Created by matsuri on 2022/09/30.
//

#include "Parser.h"
#include <iostream>

namespace simpleparser {
  using namespace std;
  void Parser::parse(vector<Token> &tokens) {
    mEndToken = tokens.end();
    mCurrentToken = tokens.begin();

    while (mCurrentToken != mEndToken) {
      optional<Type> possibleType = expectType();
      if (possibleType.has_value()) {
        optional<Token> possibleName = expectIdentifier();
        if (possibleName.has_value()) {
          optional<Token> possibleOperator = expectOperator("(");
          if (possibleOperator.has_value()) {
            cout << "We have a function!" << possibleName->mText << ".";
            exit(0);
          }
        }
      }
    }
  }
  optional<Token> Parser::expectIdentifier(const string &name) {
    if (mCurrentToken == mEndToken) {
      return nullopt;
    }
    if (mCurrentToken->mType != IDENTIFIER) {
      return nullopt;
    }
    if (!name.empty() && mCurrentToken->mText != name) {
      return nullopt;
    }
    Token returnToken = *mCurrentToken;
    mCurrentToken++;
    return returnToken;
  }
  optional<Token> Parser::expectOperator(const string &name) {
    if (mCurrentToken == mEndToken) {
      return nullopt;
    }
    if (mCurrentToken->mType != OPERATOR) {
      return nullopt;
    }
    if (!name.empty() && mCurrentToken->mText != name) {
      return nullopt;
    }
    Token returnToken = *mCurrentToken;
    ++mCurrentToken;
    return returnToken;

  }
  Parser::Parser() {
    mTypes["char"] = Type{"signed char", INT8};
    mTypes["uint8_t"] = Type{"uint8_T", UNIT8};
    mTypes["int"] = Type{"signed int", INT32};
    mTypes["unsigned"] = Type{"unsigned int", UINT32};
    mTypes["double"] = Type{"double", DOUBLE};
    mTypes["void"] = Type{"void", VOID};
  }
  optional<Type> Parser::expectType() {
    optional<Token> possibleType = expectIdentifier();
    if(!possibleType.has_value()){
      return nullopt;
    }
    map<string, Type>::iterator it = mTypes.find(possibleType->mText);
    if (it == mTypes.end()) {
      return nullopt;
    }
    return it->second;
  }
}// namespace simpleparser
