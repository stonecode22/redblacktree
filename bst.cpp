#include"bst.h"

bst::bst()
{
  root = NULL; //constructor setting our bst.tree (in main) to NULL
}

bst::~bst()
{
  removeAll(); //deconstructor deletes all nodes one by on
}

int bst::insert(int data)
{
  return insert(root, data); //accesses insert(node*, int)
}

//create a node that passes a data value and a way to link with two other nodes
int bst::insert(node* &root, int data)
{
  if(root == NULL) //if no node
    {
      node* newNode = new node; //create a new node
      newNode->data = data; //data user will insert will be set into node
      newNode->left = NULL; //by default, set to NULL
      newNode->right = NULL; //by default, set to NULL
      root = newNode; //make this the root
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

int bst::display()
{
  return display(root); //accesses display(node*)
}

int bst::display(node* root)
{
  if(root == NULL) //if no root, don't do anything
    {
      return 0;
    }
  else //otherwise...
    {
      display(root->left); //recursively repeat, going to left node until at VERY leftmost node
      cout << root->data << " "; //display data (if NULL, displays nothing)
      display(root->right); //go to the right of node
      return 1;
    }
}

int bst::removeAll()
{
  return removeAll(root); //accesses removeAll(node*)
}

int bst::removeAll(node* &root)
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

    
int bst::remove(int data)
{
  return remove(root, data); //accesses remove(node*, int)
}

int bst::remove(node* &root, int data)
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

int bst::findHeight()
{
  return findHeight(root); //accesses findHeight(node*)
}

int bst::findHeight(node* root)
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
      
int bst::level()
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

int bst::level(node* root, int order)
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
