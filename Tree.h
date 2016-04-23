#ifndef TREE_H
#define TREE_H

#include <vector>
#include <string>

using namespace std;
class Tree
{
public:
  string value;
  vector<Tree*> children;

  Tree(string name);
};

#endif
