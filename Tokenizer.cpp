//
// Created by matsuri on 2022/09/10.
//

#include "Tokenizer.h"
#include <stdexcept>

namespace simpleparser {
  using namespace std;
  vector<Token> Tokenizer::parse(const string &inProgram) {
    vector<Token> tokens;
    Token currentToken;
    currentToken.mLineNumber = 1;

    for (char currCh: inProgram) {
      if (currentToken.mType == STRING_ESCAPE_SEQUENCE) {
        switch (currCh) {
          case 'n':
            currentToken.mText.append(1, '\n');
          case 'r':
            currentToken.mText.append(1, '\r');
          case 't':
            currentToken.mText.append(1, '\t');
          case '\\':
            currentToken.mText.append(1, '\\');
            break;
          default:
            throw runtime_error("Invalid escape sequence" + string(1, currCh) + " in string on line: " + to_string(currentToken.mLineNumber));
        }
        currentToken.mType = STRING_LITERAL;
        continue;
      }else if(currentToken.mType == POTENTIAL_COMMENT && currCh != '/'){
        currentToken.mType = OPERATOR;
        endToken(currentToken, tokens);
        continue;
      }
      switch (currCh) {
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
          if (currentToken.mType == WHITESPACE) {
            currentToken.mType = INTEGER_LITERAL;
            currentToken.mText.append(1, currCh);
          } else {
            currentToken.mText.append(1, currCh);
          }
          break;

        case '.':
          if (currentToken.mType == WHITESPACE) {
            currentToken.mType = POTENTIAL_DOUBLE;
            currentToken.mText.append(1, currCh);
          } else if (currentToken.mType == INTEGER_LITERAL) {
            currentToken.mType = DOUBLE_LITERAL;
            currentToken.mText.append(1, currCh);
          } else if (currentToken.mType == STRING_LITERAL) {
            currentToken.mText.append(1, currCh);
          } else {
            endToken(currentToken, tokens);
            currentToken.mType = OPERATOR;
            currentToken.mText.append(1, currCh);
            endToken(currentToken, tokens);
          }
          break;


        case '{':
        case '}':
        case '(':
        case ')':
        case '=':
        case ';':
        case '-':
          if (currentToken.mType != STRING_LITERAL) {
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
          if (currentToken.mType != STRING_LITERAL) {
            endToken(currentToken, tokens);
            currentToken.mType = STRING_LITERAL;
            currentToken.mText.append(1, currCh);
            endToken(currentToken, tokens);
          } else if (currentToken.mType == STRING_LITERAL) {
            endToken(currentToken, tokens);
          }
          break;

        case '\\':
          if (currentToken.mType == STRING_LITERAL) {
            currentToken.mType = STRING_ESCAPE_SEQUENCE;
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
    if (token.mType != WHITESPACE) {
      tokens.push_back(token);
    }
    token.mType = WHITESPACE;
    token.mText.erase();
  }

  void Token::debugPrint() const {
    cout << "Token( " << sTokenTypeStrings[mType] << " \" " << mText << " \" " <<" Line: " << mLineNumber << ")" << endl;
  }

}// namespace simpleparser
