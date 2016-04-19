#include<iostream>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <exception>

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
  Token ReadDoubleOperatorToken(char read_char);
  Token ReadPunctuationToken(char read_char);
  Token ReadCharacter(char read_char);
  Token ReadKeywordToken(char read_char);
  Token ReadWhiteSpace(char read_char);
  Token ReadComment(char read_char);

  bool IsOperator(char read_char);
  bool IsDoubleCompareOperator(char read_char);
  bool IsDoubleCompareOperatorForLessThan(char read_char);
  bool IsPunctuationOp(char read_char);
  bool IsDoublePunctuationDot(char read_char);
  bool IsSwapOrAssignment(char read_char);
  bool IsSwap(char read_char);
  bool IsWhitespace(char read_char);
  bool IsSingleQuoteCharacter(char read_char);
  bool IsKeyWord(char read_char);
  bool IsValidCharValue(char read_char);
  bool IsOpenCurly(char read_char);
  bool IsCloseCurly(char read_char);


};

#endif
