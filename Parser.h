//
// Created by ekusiadadus on 2022/09/30.
//

#ifndef UNTITLED_PARSER_H
#define UNTITLED_PARSER_H
#pragma once

#include "Tokenizer.h"
#include <optional>
#include <string>
#include <map>

namespace simpleparser {
  using namespace std;

  enum BUILD_IN_TYPE {
    INT8,
    UNIT8,
    INT32,
    UINT32,
    DOUBLE,
    STRUCT,
    VOID,
  };

  class Type {
  public:
    Type(const string &name = "", BUILD_IN_TYPE type = VOID) : mName(name), mType(type) {}

    string mName;
    enum BUILD_IN_TYPE mType;
    vector<Type> mStructMembers;
  };
  class Parser {
  public:
    Parser();
    void parse(vector<Token> &tokens);

  private:
    optional<Type> expectType();
    optional<Token> expectIdentifier(const string &name = string());
    optional<Token> expectOperator(const string &name = string());
    bool expectFunctionDefinition();
    vector<Token>::iterator mCurrentToken;
    vector<Token>::iterator mEndToken;
    map<string, Type> mTypes;
  };

}// namespace simpleparser


#endif//UNTITLED_PARSER_H
