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
  bst();
  ~bst();
  int remove(int data);
  int insert(int data);
  int display();
  int removeAll();
  int findHeight();
  int level();
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
