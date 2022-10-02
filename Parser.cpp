//
// Created by matsuri on 2022/09/30.
//

#include "Parser.h"
#include <iostream>

namespace simpleparser{
  using namespace std;
  void Parser::parse(vector<Token> &tokens) {
    mEndToken = tokens.end();
    vector<Token>::iterator it = tokens.begin();
    while(mCurrentToken != mEndToken){
      optional<Token> possibleType = expectIdentifier();
      if(possibleType.has_value()){
        optional<Token> possibleName = expectIdentifier();
        if(possibleName.has_value()){
          optional<Token> possibleOperator = expectOperator("(");
          if (possibleOperator.has_value()){
            cout << "We have a function!" << possibleName->mText << ".";
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
    if (!name.empty() && mCurrentToken->mText != name){
      return nullopt;
    }
    vector<Token>::iterator it = mCurrentToken;
    mCurrentToken++;
    return *it;
  }
  optional<Token> Parser::expectOperator(const string &name) {
    if (mCurrentToken == mEndToken) {
      return nullopt;
    }
    if (mCurrentToken->mType != OPERATOR) {
      return nullopt;
    }
    if (!name.empty() && mCurrentToken->mText != name){
      return nullopt;
    }
    vector<Token>::iterator it = mCurrentToken;
    mCurrentToken++;
    return *it;
  }
}

