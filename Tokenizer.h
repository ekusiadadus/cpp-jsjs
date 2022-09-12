//
// Created by ekusiadadus on 2022/09/10.
//

#ifndef UNTITLED_TOKENIZER_H
#define UNTITLED_TOKENIZER_H

#pragma once

#include <string>
#include <vector>
namespace simpleparser{
  using namespace std;

  enum TokenType{
    WHITESPACE, // no token has ever this type
    IDENTIFIER,
    INTEGER_LITERAL,
    STRING_LITERAL,
    OPERATOR,
    STRING_ESCAPE_SEQUENCE,
  };

  class Token{
  public:
    enum TokenType mType{WHITESPACE};
    string mText;
    size_t mStartOffset{0};
    size_t mEndOffset{0};
    size_t mLineNumber{0};
  };
  class Tokenizer {
  public:
    vector<Token> parse(const string &inProgram);
  private:
    void endToken(Token &token, vector<Token> &tokens);
  };
}


#endif//UNTITLED_TOKENIZER_H
