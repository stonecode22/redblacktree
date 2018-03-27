#ifndef BST_H
#define BST_H
#include<iostream>
using namespace std;

struct node
{
  int data;
  node* left;
  node* right;
};

class bst
{
 public:
  bst(); //constructor
  ~bst(); //destructor
  int remove(int data); //remove int from tree
  int insert(int data); //add int to tree & reconstruct
  int display(); //display tree
  int removeAll(); //for deconstructor, delete all nodes
  int findHeight(); //calculate height of bst
  int level(); //use in conjunction with findHeight to display the levels within the tree (visual rep)
 private:
  node* root;
  int height;
  int insert(node* &root, int data);
  int display(node* root);
  int removeAll(node* &root);
  int remove(node* &root, int data);
  int findHeight(node* root);
  int level(node* root, int order);
};

#endif
