#include<iostream>
#include<string>
#include "TokenType.cpp"

#ifndef Token_H
#define Token_H

using namespace std;

class Token {

  private:
    TokenType Type;
    string value;

  public:
    Token(TokenType Type, string value);
    TokenType GetTokenType();
    string GetTokenValue();

};

#endif
