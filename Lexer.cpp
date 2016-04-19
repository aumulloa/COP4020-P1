#include "Lexer.h"

Lexer::Lexer(string filePath)  {
  fileReader = new FileReader(filePath);
  fileReader->OpenFile();
  TokenQueue = new queue<Token>();
}

void Lexer::Initialize() {

    char read_char = fileReader->GetNext();

    while(read_char != '~')   {
        Token myToken = GetToken(read_char);
        if(myToken.GetTokenType() != 58)
          TokenQueue->push(myToken);
        read_char = fileReader->GetNext();
    }
}

Token Lexer::GetToken(char read_char) {

  if(isdigit(read_char)) {
    Token digit_token = ReadintegerToken(read_char);
    return digit_token;
  }
  else if(IsOperator(read_char)){
    Token operator_token = ReadOperatorToken(read_char);
    return operator_token;
  }
  else if(IsPunctuationOp(read_char)) {
    Token punctuation_token = ReadPunctuationToken(read_char);
    return punctuation_token;
  }

  else if(IsSingleQuoteCharacter(read_char))  {
    Token char_token = ReadCharacterToken();
    return char_token;
  }
  else if(IsWhitespace(read_char)){
    Token whiteSpace_token = ReadWhiteSpaceToken(read_char);
    return whiteSpace_token;
  }
  else if(IsOpenCurly(read_char)) {
    Token comment_token = ReadCommentType1Token();
    return comment_token;
  }
  else if(IsDoubleQuouteChar(read_char)) {
    Token string_token = ReadStringToken();
    return string_token;
  }
  else if(IsOpenParenthesis(read_char)) {
    Token par_token = ReadOpenParenthesisToken();
    return par_token;
  }
  else if(IsCloseParenthesis(read_char)) {
    Token par_token = ReadCloseParenthesisToken();
    return par_token;
  }
  else if(IsPossibleIdentifier(read_char))  {
    Token temp_token = ReadPossibleKeyOrId(read_char);
    return temp_token;
  }


//Main Method
  //else if(IsKeyWord(read_char)) {
  //  Token keyword_token = ReadKeywordToken(read_char);
  //  return keyword_token;
//  }
  else{
    TokenType temp_type = TokenInvalidToken;
    Token token_toReturn (temp_type, "InvaliddfdgfsgToken");
    return token_toReturn;
  }
}

Token Lexer::ReadPossibleKeyOrId(char read_char) {

  char read_next = fileReader->GetNext();
  string target = "";
  target += read_char;

  while(IsPossibleIdentifier(read_next) || isdigit(read_next))  {
    target += read_next;
    read_next = fileReader->GetNext();
  }
  fileReader->PutBack(read_next);

//  if(IsKeyWord(target)) {
//    return ReadKeywordToken();
//  }
  //else {
    TokenType temp_type = TokenIdentifier;
    Token token_toReturn (temp_type, target);
    return token_toReturn;
//}

}

Token Lexer::ReadOpenParenthesisToken()  {

  TokenType temp_type = TokenOpenParenthesis;
  Token token_toReturn (temp_type, "(");
  return token_toReturn;
}

Token Lexer::ReadCloseParenthesisToken()  {

  TokenType temp_type = TokenCloseParenthesis;
  Token token_toReturn (temp_type, ")");
  return token_toReturn;
}

Token Lexer::ReadStringToken()  {

  char read_next = fileReader->GetNext();

  string str = "";

  while(!IsDoubleQuouteChar(read_next)) {
    str += read_next;
    read_next = fileReader->GetNext();
  }
  TokenType temp_type = TokenString;
  Token token_toReturn (temp_type, str);
  return token_toReturn;;
}

Token Lexer::ReadCommentType2Token()  {

  char read_next = fileReader->GetNext();
  char read_next_next = fileReader->GetNext();

  string comment_string = "";

  while(!(IsStar(read_next) && IsDivide(read_next_next))) {
    comment_string += read_next;
    read_next = read_next_next;
    read_next_next = fileReader->GetNext();
  }

  TokenType temp_type = TokenCommentType2;
  Token token_toReturn (temp_type, comment_string);
  return token_toReturn;
}

Token Lexer::ReadCommentType1Token()  {
  char read_next = fileReader->GetNext();

  string comment_string = "";

  while(!IsCloseCurly(read_next)) {
    comment_string += read_next;
    read_next = fileReader->GetNext();
  }
  TokenType temp_type = TokenCommentType1;
  Token token_toReturn (temp_type, comment_string);
  return token_toReturn;
}

Token Lexer::ReadWhiteSpaceToken(char read_char)  {

  TokenType temp_type = TokenWhiteSpace;
  Token token_toReturn (temp_type, "WhiteSpaceChar");
  return token_toReturn;
}

Token Lexer::ReadCharacterToken()  {
  char read_next = fileReader->GetNext();
  if(IsValidCharValue(read_next)) {
    char read_next_next = fileReader->GetNext();
      if(IsSingleQuoteCharacter(read_next_next))  {
        TokenType temp_type = TokenChar;
        stringstream ss;
        string target;
        ss << read_next;
        ss >> target;
        Token token_toReturn (temp_type, target);
        return token_toReturn;
      }
  }
  TokenType temp_type = TokenInvalidToken;
  Token token_toReturn (temp_type, "InvalidToken");
  return token_toReturn;
}

Token Lexer::ReadPunctuationToken(char read_char)  {
  if(read_char == ';')  {
    TokenType temp_type = TokenSemiColon;
    Token token_toReturn (temp_type, ";");
    return token_toReturn;
  }
  if(read_char == ',')  {
    TokenType temp_type = TokenComma;
    Token token_toReturn (temp_type, ",");
    return token_toReturn;
  }
  if(read_char == '.')  {
    char read_next = fileReader->GetNext();
    if(IsDoublePunctuationDot(read_next))  {
      TokenType temp_type = TokenDoubleDot;
      Token token_toReturn (temp_type, "..");
      return token_toReturn;
    }
    else  {
      fileReader->PutBack(read_next);
      TokenType temp_type = TokenSingleDot;
      Token token_toReturn (temp_type, ".");
      return token_toReturn;
    }
  }
  if(read_char == ':')  {

    char read_next = fileReader->GetNext();
    if(IsSwapOrAssignment(read_next)) {
      char read_next_next = fileReader->GetNext();
      if(IsSwap(read_next_next))  {
        TokenType temp_type = TokenSwap;
        Token token_toReturn (temp_type, ":=:");
        return token_toReturn;
      }
      else {
        fileReader->PutBack(read_next_next);
        TokenType temp_type = TokenAssign;
        Token token_toReturn (temp_type, ":=");
        return token_toReturn;
      }
    }
    else {
      fileReader->PutBack(read_next);
      TokenType temp_type = TokenColon;
      Token token_toReturn (temp_type, ":");
      return token_toReturn;
    }
  }
  TokenType temp_type = TokenInvalidToken;
  Token token_toReturn (temp_type, "InvalidToken");
  return token_toReturn;
}

Token Lexer::ReadOperatorToken(char read_char) {
  if(read_char == '+')  {
    TokenType temp_type = TokenPlus;
    Token token_toReturn (temp_type, "+");
    return token_toReturn;
  }
  if(read_char == '-')  {
    TokenType temp_type = TokenMinus;
    Token token_toReturn (temp_type, "-");
    return token_toReturn;
  }
  if(read_char == '*')  {
    TokenType temp_type = TokenMultiply;
    Token token_toReturn (temp_type, "*");
    return token_toReturn;
  }
  if(read_char == '/')  {
    char read_next = fileReader->GetNext();
    if(IsStar(read_next)) {
      Token token_toReturn = ReadCommentType2Token();
      return token_toReturn;
    }
    else{
      fileReader->PutBack(read_next);
      TokenType temp_type = TokenDivide;
      Token token_toReturn (temp_type, "/");
      return token_toReturn;
    }
  }
  if(read_char == '=')  {
    TokenType temp_type = TokenEquals;
    Token token_toReturn (temp_type, "=");
    return token_toReturn;
  }
  if(read_char == '<')  {
    char read_next = fileReader->GetNext();
    if(IsDoubleCompareOperatorForLessThan(read_next))  {
      if(read_next == '>') {
        TokenType temp_type = TokenNotEquals;
        Token token_toReturn (temp_type, "<>");
        return token_toReturn;
      }
      else{
        TokenType temp_type = TokenLessThanEquals;
        Token token_toReturn (temp_type, "<=");
        return token_toReturn;
      }
    }
    else{
      fileReader->PutBack(read_next);
      TokenType temp_type = TokenLessThan;
      Token token_toReturn (temp_type, "<");
      return token_toReturn;
    }
  }
  if(read_char == '>')  {
    char read_next = fileReader->GetNext();

    if(IsDoubleCompareOperator(read_next))  {
      TokenType temp_type = TokenGreaterThanEquals;
      Token token_toReturn (temp_type, ">=");
      return token_toReturn;
    }
    else{
      fileReader->PutBack(read_next);
      TokenType temp_type = TokenGreaterThan;
      Token token_toReturn (temp_type, ">");
      return token_toReturn;
    }
  }
  TokenType temp_type = TokenInvalidToken;
  Token token_toReturn (temp_type, "InvalidToken");
  return token_toReturn;
}

Token Lexer::ReadintegerToken(char read_char) {

  string integer_string = "";
  integer_string += read_char;

  char next_read = fileReader->GetNext();

  while(isdigit(next_read)) {
    integer_string += next_read;
    next_read = fileReader->GetNext();
  }
  fileReader->PutBack(next_read);

  TokenType temp_type = TokenInteger;
  Token token_toReturn (temp_type, integer_string);

  return token_toReturn;
}

void Lexer::PrintQueue()  {

  while(!TokenQueue->empty()) {
    Token temp = TokenQueue->front();
    TokenQueue->pop();

    cout << "TokenType: " << temp.GetTokenType() << " TokenValue: " << temp.GetTokenValue() << endl;
  }
}

bool Lexer::IsOperator(char read_char)  {
  if (read_char == '+'|| read_char == '-' || read_char == '*'||
      read_char == '/' || read_char == '=' || read_char == '<' ||
      read_char == '>') return true;

  return false;
}

bool Lexer::IsDoubleCompareOperator(char read_char)  {
  if (read_char == '=')return true;
  return false;
}

bool Lexer::IsDoubleCompareOperatorForLessThan(char read_char)  {
  if (read_char == '=' || read_char == '>')return true;
  return false;
}

bool Lexer::IsPunctuationOp(char read_char) {

  if (read_char == ':' || read_char == '.' || read_char == ';' ||
      read_char == ',') return true;
  return false;
}

bool Lexer::IsDoublePunctuationDot(char read_char) {
  if(read_char == '.') return true;
  return false;
}

bool Lexer::IsSwapOrAssignment(char read_char)  {
  if(read_char == '=') return true;
  return false;
}

bool Lexer::IsSwap(char read_char)  {
  if(read_char == ':') return true;
  return false;
}

bool Lexer::IsWhitespace(char read_char)  {
  if(read_char == '\t' || read_char == ' ' || read_char == '\n' || read_char == '\f' || read_char == '\v') return true;
  return false;
}

bool Lexer::IsSingleQuoteCharacter(char read_char)  {
  if(read_char == '\'') return true;
  return false;
}

bool Lexer::IsValidCharValue(char read_char)  {
  if(read_char != '\'') return true;
  return false;
}
//need to implement IsKeyWord
bool Lexer::IsOpenCurly(char read_char) {
  if(read_char == '{') return true;
  return false;
}

bool Lexer::IsCloseCurly(char read_char) {
  if(read_char == '}') return true;
  return false;
}

bool Lexer::IsKeyWord(char read_char) {
  return false;
}

bool Lexer::IsStar(char read_char)  {
  if(read_char == '*') return true;
  return false;
}

bool Lexer::IsDivide(char read_char)  {
  if(read_char == '/') return true;
  return false;
}

bool Lexer::IsDoubleQuouteChar(char read_char) {
  if(read_char == '"') return true;
  return false;
}

bool Lexer::IsValidStringValue(char read_char)  {
  if(read_char != '"') return true;
  return false;
}

bool Lexer::IsOpenParenthesis(char read_char)  {
  if(read_char == '(') return true;
  return false;
}

bool Lexer::IsCloseParenthesis(char read_char){
  if(read_char == ')') return true;
  return false;
}

bool Lexer::IsPossibleIdentifier(char read_char)  {

  if(read_char == '_' || read_char == 'a' || read_char == 'A' || read_char == 'b' || read_char == 'B' ||
    read_char == 'a' || read_char == 'A' || read_char == 'b' || read_char == 'B' ||
    read_char == 'c' || read_char == 'C' || read_char == 'd' || read_char == 'D' ||
    read_char == 'e' || read_char == 'E' || read_char == 'f' || read_char == 'F' ||
    read_char == 'g' || read_char == 'G' || read_char == 'h' || read_char == 'H' ||
    read_char == 'i' || read_char == 'I' || read_char == 'j' || read_char == 'J' ||
    read_char == 'k' || read_char == 'K' || read_char == 'l' || read_char == 'L' ||
    read_char == 'm' || read_char == 'M' || read_char == 'n' || read_char == 'N' ||
    read_char == 'o' || read_char == 'O' || read_char == 'p' || read_char == 'P' ||
    read_char == 'q' || read_char == 'Q' || read_char == 'r' || read_char == 'R' ||
    read_char == 's' || read_char == 'S' || read_char == 't' || read_char == 'T' ||
    read_char == 'u' || read_char == 'U' || read_char == 'v' || read_char == 'V' ||
    read_char == 'w' || read_char == 'W' || read_char == 'x' || read_char == 'X' ||
    read_char == 'y' || read_char == 'Y' || read_char == 'z' || read_char == 'Z') return true;
    return false;
}
