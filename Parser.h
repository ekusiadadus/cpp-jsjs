//
// Created by ekusiadadus on 2022/09/30.
//

#ifndef UNTITLED_PARSER_H
#define UNTITLED_PARSER_H
#pragma once

#include "Tokenizer.h"
#include <optional>

namespace simpleparser {
  using namespace std;
  class Parser {
  public:
    void parse(vector<Token> &tokens);

  private:
    optional<Token> expectIdentifier(const string &name = string());
    optional<Token> expectOperator(const string &name = string());
    vector<Token>::iterator mCurrentToken;
    vector<Token>::iterator mEndToken;
  };

}// namespace simpleparser


#endif//UNTITLED_PARSER_H
