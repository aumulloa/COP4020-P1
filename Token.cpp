#include "Token.h"

Token::Token(TokenType Type, string value)  {
  this->Type = Type;
  this->value = value;
}

TokenType Token::GetTokenType() {
  return this->Type;
}
string Token::GetTokenValue() {
  return this->value;
}
