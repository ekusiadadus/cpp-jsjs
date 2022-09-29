//
// Created by ekusiadadus on 2022/09/10.
//

#ifndef UNTITLED_TOKENIZER_H
#define UNTITLED_TOKENIZER_H

#pragma once

#include <string>
#include <vector>
#include<iostream>
namespace simpleparser {
  using namespace std;

  enum TokenType {
    WHITESPACE,// no token has ever this type
    IDENTIFIER,
    INTEGER_LITERAL,
    DOUBLE_LITERAL,
    STRING_LITERAL,
    OPERATOR,
    STRING_ESCAPE_SEQUENCE,
    POTENTIAL_DOUBLE,
    POTENTIAL_COMMENT,
    COMMENT,
  };

  static const char* sTokenTypeStrings[] = {
    "WHITESPACE",// no token has ever this type
    "IDENTIFIER",
    "INTEGER_LITERAL",
    "DOUBLE_LITERAL",
    "STRING_LITERAL",
    "OPERATOR",
    "STRING_ESCAPE_SEQUENCE",
    "POTENTIAL_DOUBLE",
    "POTENTIAL_COMMENT",
    "COMMENT",
  };

  class Token {
  public:
    enum TokenType mType { WHITESPACE };
    string mText;
    size_t mLineNumber{0};

    void debugPrint() const;
  };
  class Tokenizer {
  public:
    vector<Token> parse(const string &inProgram);

  private:
    void endToken(Token &token, vector<Token> &tokens);
  };
}// namespace simpleparser


#endif//UNTITLED_TOKENIZER_H
