#include<iostream>
#include"bst.h"
using namespace std;

int main()
{
  bst tree;
  int data;

  tree.insert(50);
  tree.insert(35);
  tree.insert(15);
  tree.insert(60);
  tree.insert(65);
  tree.insert(55);
  tree.display();
  return 0;
}
