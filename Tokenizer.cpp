//
// Created by matsuri on 2022/09/10.
//

#include "Tokenizer.h"

namespace simpleparser{
  using namespace std;
  vector<Token> Tokenizer::parse(const string &inProgram) {
    vector<Token> tokens;
    Token currentToken;
    currentToken.mLineNumber = 1;

    for(char currCh: inProgram){
      switch(currCh){
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
          if (currentToken.mType == WHITESPACE){
            currentToken.mType = INTEGER_LITERAL;
            currentToken.mText.append(1, currCh);
          } else {
            currentToken.mText.append(1, currCh);
          }
          break;
        case '{':
        case '}':
        case '(':
        case ')':
        case '=':
        case ';':
        case '-':
        case '.':
          if (currentToken.mType != STRING_LITERAL){
            endToken(currentToken, tokens);
            currentToken.mType = OPERATOR;
            currentToken.mText.append(1, currCh);
            endToken(currentToken, tokens);
          } else {
            currentToken.mText.append(1, currCh);
          }
          break;
        case ' ':
        case '\t':
          endToken(currentToken, tokens);
          break;
        case '\r':
        case '\n':
          endToken(currentToken, tokens);
          ++currentToken.mLineNumber;
          break;

        case '*':
          if (currentToken.mType != STRING_LITERAL){
            endToken(currentToken, tokens);
            currentToken.mType = STRING_LITERAL;
            currentToken.mText.append(1, currCh);
            endToken(currentToken, tokens);
          } else if (currentToken.mType == STRING_LITERAL){
            endToken(currentToken, tokens);
          }
          break;

        case '\\':
          if (currentToken.mType == STRING_LITERAL){
            currentToken.mType = STRING_ESCAPE_SEQUENCE;
            currentToken.mText.append(1, currCh);
            endToken(currentToken, tokens);
          } else {
            endToken(currentToken, tokens);
            currentToken.mType = OPERATOR;
            currentToken.mText.append(1, currCh);
            endToken(currentToken, tokens);
          }
          break;

        default:

          break;
      }
    }
    return tokens;
  }
  void Tokenizer::endToken(Token &token, vector<Token> &tokens) {
    if (token.mType != WHITESPACE){
      tokens.push_back(token);
    }
    token.mType = WHITESPACE;
    token.mText.erase();
  }
}
