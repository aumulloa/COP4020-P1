#include<iostream>
#include "Lexer.h"
#include "Tree.h"

using namespace std;

void Print(Tree* tree, int level)	{

	for (int i = 0; i < level; i++)	{
		cout << ". ";
	}

	cout << tree->value << "(" << tree->children.size() << ")" << endl;

	for (int i = 0; i < (int) tree->children.size(); i++)	{
		Print(tree->children.at(i), level + 1);
	}
}

void Print(Tree* tree)	{

	if (tree != NULL) {
		Print(tree, 0);
	}
	else	{
		cout << "No tree found" << endl;
	}
}


int main(int argc, char* argv[])	{

  Lexer* f = new Lexer("tiny/tiny_01");

  f->Initialize();

  Tree* ast = f->Parse();

  Print(ast);


  return 0;
}
