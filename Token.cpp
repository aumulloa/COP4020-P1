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
string Token::GetTokenString()  {

  if(this->GetTokenType() == TokenIdentifier) return "Token_Identifier";
  if(this->GetTokenType() == TokenInteger) return "Token_Integer";
  if(this->GetTokenType() == TokenChar) return "Token_Char";
  if(this->GetTokenType() == TokenString) return "Token_String";
  if(this->GetTokenType() == TokenPlus) return "Token_Plus";
  if(this->GetTokenType() == TokenMinus) return "Token_Minus";
  if(this->GetTokenType() == TokenMultiply) return "Token_Multiply";
  if(this->GetTokenType() == TokenDivide) return "Token_Divide";
  if(this->GetTokenType() == TokenSwap) return "Token_Swap";
  if(this->GetTokenType() == TokenAssign) return "Token_Assign";
  if(this->GetTokenType() == TokenLessThanEquals) return "Token_Less_Than_Equals";
  if(this->GetTokenType() == TokenLessThan) return "Token_Less_Than";
  if(this->GetTokenType() == TokenGreaterThanEquals) return "Token_Greater_Than_Equals";
  if(this->GetTokenType() == TokenMod) return "Token_Mod";
  if(this->GetTokenType() == TokenAnd) return "Token_And";
  if(this->GetTokenType() == TokenOr) return "Token_Or";
  if(this->GetTokenType() == TokenNot) return "Token_Not";
  if(this->GetTokenType() == TokenColon) return "Token_Colon";
  if(this->GetTokenType() == TokenSemiColon) return "Token_Semi_Colon";
  if(this->GetTokenType() == TokenSingleDot) return "Token_Single_Dot";
  if(this->GetTokenType() == TokenComma) return "Token_Comma";
  if(this->GetTokenType() == TokenCommentType1) return "Token_Comment_Type1";
  if(this->GetTokenType() == TokenCommentType2) return "Token_Comment_Type2";
  if(this->GetTokenType() == TokenOpenParenthesis) return "Token_Open_Parenthesis";
  if(this->GetTokenType() == TokenCloseParenthesis) return "Token_Token_Close_Parenthesis";
  if(this->GetTokenType() == TokenDoubleDot) return "Token_Double_Dot";
  if(this->GetTokenType() == Token_Program) return "Token_Program";
  if(this->GetTokenType() == Token_Var) return "Token_Var";
  if(this->GetTokenType() == Token_Const) return "Token_Const";
  if(this->GetTokenType() == Token_Type) return "Token_Type";
  if(this->GetTokenType() == Token_Function) return "Token_Function";
  if(this->GetTokenType() == Token_Return) return "Token_Return";
  if(this->GetTokenType() == Token_Begin) return "Token_Begin";
  if(this->GetTokenType() == Token_End) return "Token_End";
  if(this->GetTokenType() == Token_Output) return "Token_Output";
  if(this->GetTokenType() == Token_If) return "Token_If";
  if(this->GetTokenType() == Token_Then) return "Token_Then";
  if(this->GetTokenType() == Token_Else) return "Token_Else";
  if(this->GetTokenType() == Token_While) return "Token_While";
  if(this->GetTokenType() == Token_Do) return "Token_Do";
  if(this->GetTokenType() == Token_Case) return "Token_Case";
  if(this->GetTokenType() == Token_Of) return "Token_Of";
  if(this->GetTokenType() == Token_Otherwise) return "Token_Otherwise";
  if(this->GetTokenType() == Token_Repeat) return "Token_Repeat";
  if(this->GetTokenType() == Token_For) return "Token_For";
  if(this->GetTokenType() == Token_Until) return "Token_Until";
  if(this->GetTokenType() == Token_Loop) return "Token_Loop";
  if(this->GetTokenType() == Token_Pool) return "Token_Pool";
  if(this->GetTokenType() == Token_Exit) return "Token_Exit";
  if(this->GetTokenType() == Token_Read) return "Token_Read";
  if(this->GetTokenType() == Token_Succ) return "Token_Succ";
  if(this->GetTokenType() == Token_Pred) return "Token_Pred";
  if(this->GetTokenType() == Token_Chr) return "Token_Chr";
  if(this->GetTokenType() == Token_Ord) return "Token_Ord";
  if(this->GetTokenType() == Token_EOF) return "Token_EOF";
  if(this->GetTokenType() == TokenWhiteSpace) return "Token_White_Space";
  if(this->GetTokenType() == TokenInvalidToken) return "Token_Invalid";
  if(this->GetTokenType() == TokenCommentType3) return "Token_Comment_Type3";
  if(this->GetTokenType() == TokenEquals) return "token_Equals";
  if(this->GetTokenType() == TokenNotEquals) return "Token_Not_Equals";

  return "Token_Invalid";
}
