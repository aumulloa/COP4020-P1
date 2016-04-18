#include<iostream>
#include "Processor.cpp"


using namespace std;

int main() {

  Processor* f = new Processor("test.txt");

  f->ProcessLines();
  f->PrintVector();

  return 0;
}
