#include<iostream>
#include <queue>
#include <vector>
#include <string>

#include "FileReader.cpp"
#include "Token.cpp"

#ifndef Processor_H
#define Processor_H

using namespace std;

class Processor {

private:
  FileReader* fileReader;
  vector<Token>* TokenList;
  vector<char>* OperatorsList;

public:
  Processor(string filePath);
  void PrintVector();

  void ProcessLines();
  void ProcessLine(string line);

  string ProcessSpaces(string line);
  string ProcessInteger(string line);
  string ProcessOperator(string line);

  bool IsOperator(char input);


};

#endif
