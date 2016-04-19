#include "Lexer.h"

Lexer::Lexer(string filePath)  {
  fileReader = new FileReader(filePath);
  fileReader->OpenFile();
  TokenQueue = new queue<Token>();
}

void Lexer::Initialize() {

    char read_char = fileReader->GetNext();

    while(read_char != '~')   {
      try {
        Token myToken = GetToken(read_char);
        TokenQueue->push(myToken);
      }
      catch (int e) {
        cout << "Exception encountered" << endl;
      }
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
  //else if(IsKeyWord(read_char)) {
    //Token keyword_token = ReadKeywordToken(read_char);
    //return keyword_token;
  //}
  else if(IsSingleQuoteCharacter(read_char))  {
    Token keyword_token = ReadCharacter(read_char);
    return keyword_token;
  }
  else if(IsWhitespace(read_char)){
    Token whiteSpace_token = ReadWhiteSpace(read_char);
    return whiteSpace_token;
  }/*
  else if(IsOpenCurly(read_char)) {
    Token comment_token = ReadComment(read_char);
    return comment_token;
  }*/

//Main Method

  else{
    TokenType temp_type = TokenInvalidToken;
    Token token_toReturn (temp_type, "InvaliddfdgfsgToken");
    return token_toReturn;
  }
}
/*
Token Lexer::ReadComment(char read_char)  {
  char read_next = fileReader->GetNext();
  cout << "PO";

  while(!IsCloseCurly(read_next)) {
    read_next = fileReader->GetNext();
  }
  throw 20;
}*/

Token Lexer::ReadWhiteSpace(char read_char)  {
  TokenType temp_type = TokenWhiteSpace;
  Token token_toReturn (temp_type, "WhiteSpace");
  return token_toReturn;
}

Token Lexer::ReadCharacter(char read_char)  {
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
    TokenType temp_type = TokenDivide;
    Token token_toReturn (temp_type, "/");
    return token_toReturn;
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
  if(read_char == ' ') return true;
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
