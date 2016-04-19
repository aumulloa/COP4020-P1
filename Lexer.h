#include<iostream>
#include <queue>
#include <vector>
#include <string>

#include "FileReader.cpp"
#include "Token.cpp"

#ifndef Lexer_H
#define Lexer_H

using namespace std;

class Lexer {

private:
  FileReader* fileReader;
  queue<Token>* TokenQueue;

public:
  Lexer(string filePath);
  void PrintQueue();
  void Initialize();

  Token GetToken(char read_char);

  Token ReadintegerToken(char read_char);
  Token ReadOperatorToken(char read_char);

  bool IsOperator(char read_char);


};

#endif
