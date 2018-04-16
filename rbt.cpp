#include"rbt.h"

rbt::rbt()
{
  root = NULL;
}

rbt::~rbt()
{
  removeAll(); //deconstructor deletes all nodes one by on
}

int rbt::rotateL(node* &root, node* &p)
{
  node* child = p->right;
  
  p->right = child->left; //child's left child becomes p's right child
  if(p->right != NULL)
    {
      p->right->parent = p; //right child becomes p's parent
    }
  if(child != NULL) //to not lose grandparent
    {
      child->parent = p->parent; //child becomes parents grandparent
    }
  if(p->parent == NULL)
    {
      root = child;
    }
  else if(p == p->parent->left)
    {
      p->parent->left = child;
    }
  else
    {
      p->parent->right = child;
    }
  child->left = p;
  p->parent = child;
  return 1;
}

int rbt::rotateR(node* &root, node* &p)
{
  node* child = p->left;
  p->left = child->right;
  if(p->left != NULL)
    {
      p->left->parent = p;
    }
  if(child != NULL)
    {
      child->parent = p->parent;
    }
  if(p->parent == NULL)
    {
      root = child;
    }
  else if(p == p->parent->right)
    {
      p->parent->right = child;
    }
  else
    {
      p->parent->left = child;
    }
  child->right = p;
  p->parent = child;
  return 1;
}

int rbt::insert(int data)
{
  node* newNode = new node;
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->parent = NULL;
  newNode->color = 1;
  insert(root, newNode); //accesses insert(node*, int, node*)
  repair(root, newNode);
}

//create a node that passes a data value and a way to link with two other nodes
int rbt::insert(node* &root, node* &temp)
{
  if(root == NULL)
    {
      root = temp;
      return 1;
    }
  else if(root->data > temp->data)
    {
      temp->parent = root;
      return insert(root->left, temp);
    }
  else
    {
      temp->parent = root;
      return insert(root->right, temp);
    }      
}

int rbt::repair(node* &root, node* &temp)
{
  node* p = NULL;
  node* gp = NULL;
  while((temp != root) && (temp->color == 1) && (temp->parent->color == 1))
    {
      p = temp->parent; //parent
      gp = temp->parent->parent; //grandparent
      if(gp->left == p) //parent is left child
	{
	  node* unc = gp->right; //gp->right is uncle
	  if(unc != NULL && unc->color == 1) //if uncle exists & it's red
	    {
	      p->color = 0; //parent is orig. red
	      gp->color = 1; //gp is orig. black if parent was red
	      unc->color = 0; //uncle must be red within the reqs. of the while loop
	      temp = gp; //need to set temp = gp
	    }
	  else if(unc->color = 0)
	    {
	      if(temp == p->right)
		{
		  rotateL(root, p);
		  temp = p;
		  p = temp->parent;
		}
	      rotateR(root, gp);
	      
	      int tempColor; //swap colors
	      tempColor = p->color;
	      p->color = gp->color;
	      gp->color = tempColor;
	      temp = p;
	    }
	}
      else //parent is right child
	{
	  node* unc = gp->left; //gp->right is uncle
	  if(unc != NULL && unc->color == 1) //if uncle exists & it's red
	    {
	      p->color = 0; //parent is orig. red
	      gp->color = 1; //gp is orig. black if parent was red
	      unc->color = 0; //uncle must be red within the reqs. of the while loop
	      temp = gp; //need to set temp = gp
	    }
	  else if(unc->color = 0)
	    {
	      if(temp == p->left)
		{
		  rotateR(root, p);
		  temp = p;
		  p = temp->parent;
		}
	      rotateL(root, gp);
	      
	      int tempColor; //swap colors
	      tempColor = p->color;
	      p->color = gp->color;
	      gp->color = tempColor;
	      temp = p;
	    }
	}
    }
  root->color = 0;
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
	  cout << "Parent: " << root->parent->data << endl;
	}
      else
	{
	  cout << "NULL\n";
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
