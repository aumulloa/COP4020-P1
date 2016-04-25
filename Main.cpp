#include<iostream>
#include <exception>    // exception

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


	if(argc < 2 || argc > 3)	{
		cout << "Cant run";
		return -1;
	}

	Lexer* lexical_analizer;
	string arg1(argv[1]);
	bool print_ast = false;
	char* filePath;
	try	{
		if(arg1.compare("-ast") == 0)	{
			print_ast = true;
			filePath = argv[2];
			lexical_analizer = new Lexer(filePath);

		}
		else	{
			print_ast = false;
			filePath = argv[1];
			lexical_analizer = new Lexer(filePath);
		}
		lexical_analizer->Initialize();
		Tree* AST = lexical_analizer->Parse();
		if(print_ast)	{
			Print(AST);
		}
	}
	catch (exception & ex)
  {
    cout << ex.what() << endl;
  }
  return 0;
}
