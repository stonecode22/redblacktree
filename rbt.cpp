#include"rbt.h"

rbt::rbt()
{
  root = NULL; //constructor setting our rbt.tree (in main) to NULL
}

rbt::~rbt()
{
  removeAll(); //deconstructor deletes all nodes one by on
}

node* rbt::parentOf(node* relative)
{
  return relative->parent;
}

node* rbt::gParentOf(node* relative)
{
  node* p = parentOf(relative);
  if(p == NULL)
    {
      return NULL;
    }
    return parentOf(p);
}

node* rbt::siblingOf(node* relative)
{
  node* p = parentOf(relative);
  if(p == NULL)
    {
      return NULL;
    }
  if(relative == p->left)
    {
      return p->right;
    }
  else
    {
      return p->left;
    }
}

node* rbt::uncleOf(node* relative)
{
  node* p = parentOf(relative);
  node* g = gParentOf(relative);
  if(g == NULL)
    {
      return NULL;
    }
  return siblingOf(p);
}

int rbt::rotateL(node* root)
{
  node* newRoot = root->right;
  assert(newRoot != NULL);
  root->right = newRoot->left;
  newRoot->left = root;
  newRoot->parent = root->parent;
  root->parent = newRoot;
  return 1;
}

int rbt::rotateR(node* root)
{
  node* newRoot = root->left;
  assert(newRoot != NULL);
  root->right = newRoot->right;
  newRoot->right = root;
  newRoot->parent = root->parent;
  root->parent = newRoot;
  return 1;
}

int rbt::insert(int data)
{
  return insert(root, data); //accesses insert(node*, int, node*)
}

//create a node that passes a data value and a way to link with two other nodes
int rbt::insert(node* &root, int data)
{
  if(root == NULL) //if no node
    {
      node* newNode = new node; //create a new node
      newNode->data = data; //data user will insert will be set into node
      newNode->left = NULL;
      newNode->right = NULL;
      newNode->parent = NULL;
      if(newNode != NULL)
	{
	  newNode->parent = root;
	}
      newNode->color = 1;
      root = newNode;
      repair(root);
      return 1;
    }
  else if((root->data) > data) //root already exists, so CASE 2: the data in root is larger than the data we input; insert this into the left child of root 
    {
      return insert(root->left, data);
    }
  else //root already exists, CASE 3: root is smaller than the data inputted; insert this into right child of root
    {
      return insert(root->right, data);
    }
}

int rbt::repair(node* &root)
{
  //1. Node is the root, has no parent
  if(parentOf(root) == NULL)
    {
      root->color = 0;
      return 1;
    }
  //2. Node's parent is black
  else if(parentOf(root)->color == 0)
    {
      return 1;
    }
  //3. Node's parent & uncle is red
  else if(parentOf(root)->color == 1)
    {
      parentOf(root)->color = 0;
      uncleOf(root)->color = 0;
      gParentOf(root)->color = 1;
      repair(root->parent->parent);
      return 1;
    }
  //4. Node's parent is red, and uncle is black
  else
    {
      node* p = parentOf(root);
      node* g = gParentOf(root);
      if(root == g->left->right)
	{
	  rotateL(root);
	  root = root->left;
	}
      else if(root == g->right->left)
	{
	  rotateR(root);
	  root = root->right;
	}
      //4.5. 
      if(root == p->left)
	{
	  rotateR(g);
	  return 1;
	}
      else
	{
	  rotateL(g);
	  p->color = 0;
	  g->color = 1;
	  return 1;
	}
    }
}

int rbt::display()
{
  return display(root); //accesses display(node*)
}

int rbt::display(node* root)
{
  if(root == NULL) //if no root, don't do anything
    {
      return 0;
    }
  else //otherwise...
    {
      display(root->left); //recursively repeat, going to left node until at VERY leftmost node
      cout << root->data << " | ";//display data (if NULL, displays nothing)
      if(root->color == 0)
	{
	  cout << "Black | ";
	}
      else
	{
	  cout << "Red | ";
	}

      if(root->parent != NULL)
	{
	  cout << root->parent << endl;
	}
      else
	{
	  cout << "NULL" << endl;
	}
      display(root->right); //go to the right of node
      return 1;
    }
}

int rbt::removeAll()
{
  return removeAll(root); //accesses removeAll(node*)
}

int rbt::removeAll(node* &root)
{
  if(root != NULL) //if tree exists
    {
      removeAll(root->left); //recursion to delete the VERY leftmost node until all are deleted
      removeAll(root->right); //recursion to delete the VERY rightmost node until all are deleted
      delete root; //with the two removeAll() above, only the root remains; we delete it here
      root = NULL;
      return 1;
    }
}

int rbt::remove(int data)
{
  return remove(root, data); //accesses remove(node*, int)
}

int rbt::remove(node* &root, int data)
{
  if(root == NULL) //if bst is empty
    {
      return 0;
    }
  else if(root != NULL) //if bst is not empty
    {
      if(root->data == data) //when user finds a match in data values
	{
	  if(root->left == NULL && root->right == NULL) //if there are no children
	    {
	      delete root; //delete root
	      root = NULL;
	      return 1;
	    }
	  else if(root->left != NULL && root->right == NULL) //if there is only a left child
	    {
	      node *temp = root->left;
	      delete root;
	      root = temp; //replace the parent with the left child
	      return 1;
	    }
	  else if(root->left == NULL && root->right != NULL) //if there is only a right child
	    {
	      node *temp = root->right;
	      delete root;
	      root = temp; //replace the parent with the right child
	      return 1;
	    }
	  else if(root->left != NULL && root->right != NULL && (root->right->left) == NULL) //if there are two children, and the right child has no left child (right child becomes the new root)
	    {
	      node *temp = root->right;
	      root->data = temp->data; //root's data becomes the data in temp
	      root->right = temp->right; //root->right then points to the data after deleting the temp
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
	      delete root;
	      root->data = temp->data;
	      delete temp;
	      last->left = NULL;
	      return 1;
	    }
	      
	}
      else if(root->data > data) //if data found in the root is greater than the one user inputted, recursively go to the left child until match
	{
	  remove(root->left, data);
	}
      else //if data found in the root is less than the one user inuputted, recursively go to the right child until match
	{
	  remove(root->right, data);
	}
    }
}

int rbt::findHeight()
{
  return findHeight(root); //accesses findHeight(node*)
}

int rbt::findHeight(node* root)
{
  if(root == NULL) //if root = NULL, do nothing
    {
      return 0;
    }
  if(root !=NULL)
    {
      int leftHeight = 0; //using this to find the height of the left side of the root
      leftHeight = findHeight(root->left); //keeps moving to a lower level leftward
      
      int rightHeight = 0; //using this to find the height of the right side of the root
      rightHeight = findHeight(root->right); //keeps moving to a lower level rightward

      
      if(leftHeight > rightHeight) //compare which height is higher between left and right, and return the highest; if the same, it chooses rightHeight+1, even though they are the same value (so it don't matter)
	{
	  return leftHeight + 1;
	}
      else
	{
	  return rightHeight + 1;
	}
    }
}
      
int rbt::level()
{
  int height = findHeight(); //using findHeight(), sets height = the height of the tree
  cout << "\nLevel#:";
  for(int i = 0; i < height; i++) //for values i = 0 to whatever the height is, print the levels and the values that reside in them
    {
      cout << endl << "     " << (i+1) << ": ";
      level(root, i); //access level(node*, int)
    }
  cout << endl;
  return 1;
}

int rbt::level(node* root, int order)
{
  if(root == NULL) //if root = NULL, do nothing
    {
      return 0;
    }
  if(root != NULL) //if root exists...
    {
      if(order == 0) //the root, printing "1: <root value>" in main
	{
	  cout << root->data << " "; //print root
	}
      else //if descendants of root, printing 2,3,4...: <values> in main
	{
	  level(root->left, order-1);
	  level(root->right, order-1);
	}
    }
}
