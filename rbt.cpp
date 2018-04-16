#include"rbt.h"

rbt::rbt()
{
  root = NULL; //constructor
}

rbt::~rbt()
{
  removeAll(); //deconstructor deletes all nodes one by on
}

//Left rotator function
int rbt::rotateL(node* &root, node* &p)
{
  node* child = p->right;
  
  p->right = child->left; //child's left child becomes p's right child
  if(p->right != NULL) //if parent's right child exists
    {
      p->right->parent = p; //parent's right child becomes p's parent
    }
  if(child != NULL) //if child exists
    {
      child->parent = p->parent; //child becomes old p's grandparent
    }
  if(p->parent == NULL) //if p has no parent
    {
      root = child; //rotate so that child is the new root
    }
  else if(p == p->parent->left) //if p = is the left child of its grandfather
    {
      p->parent->left = child; //let p become new child
    }
  else //if p = the right child of its grandfather
    {
      p->parent->right = child; //let p become new child
    }
  child->left = p; //p becomes new left child of the old child
  p->parent = child; //new p's parent is old child
  return 1;
}

//Right rotator function
int rbt::rotateR(node* &root, node* &p) //similar to rotateL
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
  //create a new node here
  node* newNode = new node;
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->parent = NULL;
  newNode->color = 1; //default color to RED [1]
  insert(root, newNode); //accesses insert(node*, node*)
  repair(root, newNode); //fix the newly created tree
}

//create a node that passes a data value and a way to link with two other nodes
int rbt::insert(node* &root, node* &temp)
{
  if(root == NULL) //if node doesn't exist
    {
      root = temp; //from insert(int data), make the root = newNode (temp here)
      return 1;
    }
  //similar to a binary search tree
  else if(root->data > temp->data) //if the data in current node is smaller than what we're inserting
    {
      temp->parent = root; //set the parent
      return insert(root->left, temp); //recursively check again until NULL
    }
  else
    {
      temp->parent = root; //set parent
      return insert(root->right, temp); //recursion
    }      
}

int rbt::repair(node* &root, node* &temp)
{
  node* p = NULL;
  node* gp = NULL;
  //in the conditions that...
  //1. There is not only one node in the tree
  //2. The color of temp (newNode) is red
  //3. The color of temp's parent is also red
  //   We deem it necessary to go through this loop and fix the tree
  while((temp != root) && (temp->color == 1) && (temp->parent->color == 1))
    {
      p = temp->parent; //parent
      gp = temp->parent->parent; //grandparent
      if(p == gp->left) //parent is left child of its grandparent
	{
	  node* unc = gp->right; //gp->right is uncle
	  if(unc != NULL && unc->color == 1) //if uncle exists & it's red
	    {
	      p->color = 0; //parent is orig. red
	      gp->color = 1; //gp is orig. black if parent was red
	      unc->color = 0; //uncle must be red within the reqs. of the while loop
	      temp = gp; //need to set temp = gp
	    }
	  else //if uncle is NULL & black
	    {
	      if(temp == p->right) //if temp = p's right child
		{
		  rotateL(root, p); //call rotateL function
		  temp = p;
		  p = temp->parent;
		}
	      rotateR(root, gp); //call rotateR function

	      //swap colors
	      int tempColor;
	      tempColor = p->color;
	      p->color = gp->color;
	      gp->color = tempColor;
	      temp = p;
	    }
	}
      else //parent is right child of its grandparent
	{
	  node* unc = gp->left; //gp->left is uncle
	  if(unc != NULL && unc->color == 1) //if uncle exists & it's red
	    {
	      p->color = 0; //parent is orig. red
	      gp->color = 1; //gp is orig. black if parent was red
	      unc->color = 0; //uncle must be red within the reqs. of the while loop
	      temp = gp; //need to set temp = gp
	    }
	  else //if unc is NULL (leaf), which is black
	    {
	      if(temp == p->left) //if temp = p's left child
		{
		  rotateR(root, p); //call rotateR
		  temp = p;
		  p = temp->parent;
		}
	      rotateL(root, gp); //call RotateL

	      //swap colors
	      int tempColor;
	      tempColor = p->color;
	      p->color = gp->color;
	      gp->color = tempColor;
	      temp = p;
	    }
	}
    }
  root->color = 0; //ALWAYS set the root to be black
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
      if(root->color == 0) //if node is black
	{
	  cout << "BLK | ";
	}
      else //if it's red
	{
	  cout << "RED | ";
	}

      if(root->parent != NULL) //if parent exists
	{
	  cout << "Parent: " << root->parent->data << " | "; //print the parent's data
	}
      else //if parent doesn't exist
	{
	  cout << "Parent: NULL | "; //print NULL
	}
      if(root->left != NULL) //if node's left child exists
	{
	  cout << "LChild: " << root->left->data << " | "; //print its left child's data
	}
      else //if not, NULL
	{
	  cout << "LChild: NULL | ";
	}
      if(root->right != NULL) //if node's right child exists
	{
	  cout << "RChild: " << root->right->data << endl; //print its right child's data
	}
      else //if not, NULL
	{
	  cout << "RChild: NULL\n";
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

//removal function here in pt2
