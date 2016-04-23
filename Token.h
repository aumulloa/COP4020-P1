#include <iostream>
#include <string>
#include "TokenType.h"

#ifndef TOKEN_H
#define TOKEN_H

using namespace std;

class Token {

  private:


  public:
    Token(TokenType Type, string value);
    TokenType GetTokenType();
    string GetTokenValue();
    string GetTokenString();
    TokenType Type;
    string value;

};

#endif
