#include<iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <sstream>

#include "FileReader.h"
#include "Token.h"
#include "TokenType.h"
#include "Tree.h"

#ifndef LEXER_H
#define LEXER_H

using namespace std;

class Lexer {

private:

public:
  Lexer(string filePath);

  stack<Tree*>* Trees;

  FileReader* fileReader;
  queue<Token>* TokenQueue;

  Tree* Parse();

  void Tiny();
  void ReadToken(TokenType type);
  void ReadIdentifier();
  void ReadInt();
  void ReadChar();
  void ReadString();
  void Primary();
  void Name();
  void Consts();
  void Const();
  void ConstVal();
  void BuildTree(string name, int count);
  void Expression();
  void Assignment();
  void Term();
  void Factor();
  void ForExp();
  void ForStat();
  void Body();
  void Dcln();
  void Dclns();
  void Params();
  void OtherwiseClause();
  void CaseExpression();
  void Statement();
  void Caseclause();
  int Caseclauses();
  void LitList();
  void Type();
  void Types();
  void StrNode();
  void OutExp();
  void Fcn();
  void SubProgs();


  void PrintQueue();
  void Initialize();

  Token GetToken(char read_char);
  Token ReadintegerToken(char read_char);
  Token ReadOperatorToken(char read_char);
  Token ReadDoubleOperatorToken(char read_char);
  Token ReadPunctuationToken(char read_char);
  Token ReadCharacterToken();
  Token ReadKeywordToken(char read_char);
  Token ReadWhiteSpaceToken(char read_char);
  Token ReadCommentType1Token();
  Token ReadCommentType2Token();
  Token ReadCommentType3Token();
  Token ReadStringToken();
  Token ReadOpenParenthesisToken();
  Token ReadCloseParenthesisToken();
  Token ReadPossibleKeyOrId(char read_char);
  Token ReadKeywordToken(string keyWord);

  bool IsOperator(char read_char);
  bool IsDoubleCompareOperator(char read_char);
  bool IsDoubleCompareOperatorForLessThan(char read_char);
  bool IsPunctuationOp(char read_char);
  bool IsDoublePunctuationDot(char read_char);
  bool IsSwapOrAssignment(char read_char);
  bool IsSwap(char read_char);
  bool IsWhitespace(char read_char);
  bool IsSingleQuoteCharacter(char read_char);
  bool IsKeyWord(string str_key);
  bool IsValidCharValue(char read_char);
  bool IsOpenCurly(char read_char);
  bool IsCloseCurly(char read_char);
  bool IsStar(char read_char);
  bool IsDivide(char read_char);
  bool IsDoubleQuouteChar(char read_char);
  bool IsValidStringValue(char read_char);
  bool IsOpenParenthesis(char read_char);
  bool IsCloseParenthesis(char read_char);
  bool IsPossibleIdentifier(char read_char);
  bool IsHashTag(char read_char);

};

#endif
