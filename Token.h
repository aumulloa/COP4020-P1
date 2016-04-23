#include<iostream>
#include<string>
#include "TokenType.cpp"

#ifndef Token_H
#define Token_H

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
