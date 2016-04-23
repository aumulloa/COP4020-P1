#include<iostream>
#include "Lexer.cpp"

using namespace std;



void Print(Tree* tree, int level)
{
	for (int i = 0; i < level; ++i)
	{
		cout<< ". ";
	}

	cout << tree->value << "(" << tree->children.size() << ")" << endl;

	for (int i = 0; i < (int) tree->children.size(); i++)
	{
		Print(tree->children.at(i), level + 1);
	}
}

void Print(Tree* tree)
{
	if (tree == NULL) cout << "Where is my tree? YOU DELETE IT!";

	Print(tree, 0);
}


int main() {

  Lexer* f = new Lexer("tiny/tiny_10");

  f->Initialize();

  Tree* ast = f->Parse();

  Print(ast);


  return 0;
}
