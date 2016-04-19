#include "Lexer.h"

Lexer::Lexer(string filePath)  {
  fileReader = new FileReader(filePath);
  fileReader->OpenFile();
  TokenQueue = new queue<Token>();
}

void Lexer::Initialize() {

    char read_char = fileReader->GetNext();

    while(read_char != '*')   {
      Token myToken = GetToken(read_char);
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
    cout << "HOLA";
    return operator_token;
  }
  else  {
    TokenType temp_type = TokenWhiteSpace;
    Token token_toReturn (temp_type, "WhiteSpace");
    return token_toReturn;
  }

}
bool Lexer::IsOperator(char read_char)  {
  if(read_char == '+'|| read_char == '-') return true;
  return false;
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
