#include "Processor.h"

Processor::Processor(string filePath)  {
  fileReader = new FileReader(filePath);
  fileReader->OpenFile();
  TokenList = new vector<Token>();
  char OpChars[] = {'+', '-', '*', '/', '=', '<', '>'};
  OperatorsList = new vector<char>(OpChars, OpChars + sizeof(OpChars) / sizeof(char));
}

void Processor::PrintVector() {

  for(int i = 0; i < TokenList->size(); i++ ) {
    cout << TokenList->at(i).GetTokenType() << " " << TokenList->at(i).GetTokenValue() <<  endl;
  }
}
void Processor::ProcessLines() {

  if(!fileReader->IsOpen()) {
    cout << "File hasnt been yet opened" << endl;
    return;
  }

  string inLine;
  while(getline(fileReader->ifs, inLine)) {
    ProcessLine(inLine);
  }
}

string Processor::ProcessInteger(string line) {
  int i = 0;
  string integerValue = "";

  while(isdigit(line[i])) {
    integerValue += line[i];
    i++;
  }
  TokenType Type = TokenInteger;

  Token myToken(Type, integerValue);
  TokenList->push_back(myToken);

  return line.substr(i);
}

string Processor::ProcessSpaces(string line) {

  int i = 0;
  string whiteSpaces = "";

  while(line[i] == ' ') {
    TokenType Type = TokenWhiteSpace;

    Token myToken(Type , whiteSpaces);
    TokenList->push_back(myToken);
    whiteSpaces += line[i];
    i++;
  }
  return line.substr(i);
}

string Processor::ProcessOperator(string line)  {

  int i = 0;

  while(IsOperator(line[i])) {
    if(line[i] == '+')  {
      TokenType Type = TokenPlus;
      Token temp(Type, "+");
      TokenList->push_back(temp);
    }
    else if(line[i] == '-')  {
      TokenType Type = TokenMinus;
      Token temp(Type, "-");
       TokenList->push_back(temp);
    }
    else if(line[i] == '*')  {
      TokenType Type = TokenMultiply;
      Token temp(Type, "*");
      TokenList->push_back(temp);
    }
    else if(line[i] == '/')  {
      TokenType Type = TokenDivide;
      Token temp(Type, "/");
      TokenList->push_back(temp);
    }
    else if(line[i] == '=')  {
      TokenType Type = TokenEquals;
      Token temp(Type, "=");
      TokenList->push_back(temp);
    }
    else if(line[i] == '<')  {
      TokenType Type = TokenLessThan;
      Token temp(Type, "<");
      TokenList->push_back(temp);
    }
    else if(line[i] == '>')  {
      TokenType Type = TokenGreaterThan;
      Token temp(Type, ">");
      TokenList->push_back(temp);
    }
    i++;
  }
  return line.substr(i);
}

void Processor::ProcessLine(string line) {

  if(isdigit(line[0])) {
    string temp = ProcessInteger(line);
    ProcessLine(temp);
  }
  else if (line[0] == ' ')  {
    string temp = ProcessSpaces(line);
    ProcessLine(temp);
  }
  else if(IsOperator(line[0])) {

    string temp = ProcessOperator(line);
    ProcessLine(temp);
  }

}
bool Processor::IsOperator(char input)
  {
    for(int i = 0 ; i < OperatorsList->size(); i++)  {
      if(OperatorsList->at(i) == input) {
        return true;
      }
    }
    return false;
  }
