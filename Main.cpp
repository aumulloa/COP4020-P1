#include<iostream>
#include "Lexer.cpp"

using namespace std;

int main() {

  Lexer* f = new Lexer("test.txt");

  f->Initialize();
  f->PrintQueue();


  return 0;
}
