#include"bst.h"
#include<iostream>

bst::bst()
{
  root = NULL;
}

bst::~bst()
{
  removeAll();
}

int bst::insert(int data)
{
  return insert(root, data);
}

int bst::insert(node* &root, int data)
{
  if(root == NULL)
    {
      node* newNode = new node;
      newNode->data = data;
      newNode->left = NULL;
      newNode->right = NULL;
      root = newNode;
      return 1;
    }
  else if((root->data) > data)
    {
      return insert(root->left, data);
    }
  else
    {
      return insert(root->right, data);
    }
}

int bst::display()
{
  return display(root);
}

int bst::display(node* root)
{
  if(root == NULL)
    {
      return 0;
    }
  else
    {
      display(root->left); //recursively repeats going to left node until at VERY leftmost node
      cout << root->data << " "; //display data (if NULL, displays nothing)
      display(root->right); //go to the right of node
      return 1;
    }
}

int bst::removeAll()
{
  return removeAll(root);
}

int bst::removeAll(node* &root)
{
  if(root != NULL)
    {
      removeAll(root->left);
      removeAll(root->right);
      delete root;
      root = NULL;
      return 1;
    }
}

    
int bst::remove(int data)
{
  return remove(root, data);
}

int bst::remove(node* &root, int data)
{
  if(root == NULL) //if bst is empty
    {
      return 0;
    }
  else if(root != NULL) //if bst is not empty
    {
      if(root->data == data) //when matching
	{
	  if(root->left == NULL && root->right == NULL) //if there are no children
	    {
	      delete root;
	      root = NULL;
	      return 1;
	    }
	  else if(root->left != NULL && root->right == NULL) //if there is only a left child
	    {
	      node *temp = root->left;
	      delete root;
	      root = temp;
	      return 1;
	    }
	  else if(root->left == NULL && root->right != NULL) //if there is only a right child
	    {
	      node *temp = root->right;
	      delete root;
	      root = temp;
	      return 1;
	    }
	  else if(root->left != NULL && root->right != NULL && (root->right->left) == NULL) //if there are two children, and the right child has no left child (right child becomes the new root)
	    {
	      node *temp = root->right;
	      root->data = temp->data;
	      temp = temp->right;
	      delete temp;
	      return 1;
	    }	  
	  else //if there are two children
	    {
	      node *temp = root->right; //current
	      node *last; //parent of the current
	      while(temp->left != NULL)
		{
		  last = temp;
		  temp = temp->left;
		}
	      root->data = temp->data;
	      delete temp;
	      last->left = NULL;
	      return 1;
	    }
	      
	}
      else if(root->data > data)
	{
	  remove(root->left, data);
	}
      else
	{
	  remove(root->right, data);
	}
    }
}
