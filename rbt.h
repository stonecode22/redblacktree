#ifndef RBT_H
#define RBT_H
#include<iostream>
using namespace std;

struct node
{
  int data; //contained number
  int color; //0 = Black, 1 = Red
  node* left;
  node* right;
  node* parent;
};

class rbt
{
 public:
  rbt(); //constructor
  ~rbt(); //destructor
  int remove(int data); //remove int from tree
  int insert(int data); //add int to tree & reconstruct
  int display(); //display tree
  int removeAll(); //for deconstructor, delete all nodes
  int findHeight(); //calculate height of bst
  int level(); //use in conjunction with findHeight to display the levels within the tree (visual rep)
  node* parentOf(node* relative);
  node* gParentOf(node* relative);
  node* siblingOf(node* relative);
  node* uncleOf(node* relative);
 private:
  int height;
  node* root;
  //  node* parentOf(node* relative);
  //  node* gParentOf(node* relative);
  //  node* siblingOf(node* relative);
  //  node* uncleOf(node* relative);
  int rotateL(node* root);
  int rotateR(node* root);
  int insert(node* &root, int data);
  int repair(node* &root);
  int display(node* root);
  int removeAll(node* &root);
  int remove(node* &root, int data);
  int findHeight(node* root);
  int level(node* root, int order);
};

#endif
