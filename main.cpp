//Red Black Tree Tree, By Stone Yang, 3/26
//Creates a sorted binary tree that allows the user to add, remove, and display
#include<iostream>
#include<string.h>
#include<fstream>
#include"rbt.h"
using namespace std;

bool getConsoleData(int* numbers, bool* valid, bst* tree);
bool getFileData(int* numbers, bool* valid, bst* tree);
 
int main()
{
  bst tree; //creating tree (constructor sets root = NULL)
  char readChoice1[10]; //choice for Phase 1
  char readChoice2[10]; //choice for Phase 2
  bool valid = true; //to allow the user to retry after failure
  bool repeat = true; //to allow phase 2 to repeat
  int numbers[200]; //where data values are stored
  
  cout << "Binary Search Tree\n";
  //Phase 1:
  //Purpose: Store in data in two methods (file/console) and insert data values into the tree
  do
    {
      //prompt user for an inital choice between two insertion methods
      cout << "'FILE' to insert data from file, 'CONSOLE' to insert data from console.\n";
      cin.getline(readChoice1, 10);

      //make readChoice1 uppercase to ignore case-sensitivity
      for(int i = 0; i < strlen(readChoice1); i++)
	{
	  readChoice1[i] = toupper(readChoice1[i]);
	}

      //if user inputs file (file insertion)
      if(strcmp(readChoice1, "FILE") == 0)
	{
	  getFileData(numbers, &valid, &tree);
	}

      //if users inputs console (console insertion)
      else if(strcmp(readChoice1, "CONSOLE") == 0)
	{
	  getConsoleData(numbers, &valid, &tree);
	}

      //if user doesn't input any of the above
      else
	{
	  cout << "Invalid command, try again.\n";
	  valid = false;
	}
    }while(valid == false); //any situation where valid = false, loop back and prompt user to retry

  //Phase 2:
  //Purpose: display the tree created in Phase 1
  cout << "Tree successfully generated!\n Your binary search tree:\n";
  tree.display();
  tree.level();

  //Phase 3:
  //Purpose: prompt user to make additional edits (removing nodes, inserting nodes, re-displaying the tree)
  while(repeat == true)
    {
      int number = 0;
      cout << "INSERT a node, REMOVE a node, DISPLAY the tree, or QUIT.\n";
      cin.getline(readChoice2, 10);
      
      //ignore case-sensitivity of readCase2
      for(int i = 0; i < strlen(readChoice2); i++)
	{
	  readChoice2[i] = toupper(readChoice2[i]);
	}
      
      if(strcmp(readChoice2, "INSERT") == 0)
	{
	  cout << "Add a number into the tree: ";
	  cin >> number;
	  cin.ignore();
	  tree.insert(number); //inserts into the tree
	}
      
      else if(strcmp(readChoice2, "REMOVE") == 0)
	{
	  cout << "Remove a number from the tree: ";
	  cin >> number;
	  cin.ignore();
	  tree.remove(number); //removes from the tree, arranges the tree to adapt (change structure) to the change
	}
      else if(strcmp(readChoice2, "DISPLAY") == 0)
	{
	  cout << endl;
	  tree.display(); //displays numbers inorder
	  tree.level(); //displays visual tree levels
	}
      else if(strcmp(readChoice2, "QUIT") == 0)
	{
	  repeat = false; //stop loop, end program
	}
      else
	{
	  cout << "Invalid command, try again.\n"; //when you misspell one of those 4 words
	}
    }
  return 0;
}

//functions below

//Phase 1: function to get values in the console
bool getConsoleData(int* numbers, bool* valid, bst* tree)
{
  //prompt user to enter values
  cout << "Enter values separated by spaces (end by using '-1'): ";
  int valueCount = 0;
  bool terminate = false; //end the input session with '-1'
  while(valueCount < 200 && terminate == false) //for 100 numbers, insert index values into numbers array
    {
      cin >> numbers[valueCount];
      tree->insert(numbers[valueCount]); //insert value from numbers array into the tree
      if(numbers[valueCount] == -1)
	{
	  terminate = true;
	  tree->remove(-1); //tree->insert(-1) happened, so have to remove it (probably not the best way to do things)
	}
      valueCount++;
    }
  *valid = true;
  return valid; //returns "true" to valid, onto phase 2
}

//Phase 1: function to get values from a file
bool getFileData(int* numbers, bool* valid, bst* tree)
{
  char fileName[50];
  int value;
  ifstream file;

  //prompt user to insert the name of the file to be used
  cout << "Enter the name of file to use (be sure values are separated by ','): ";
  cin.getline(fileName, 50);
  file.open(fileName);
  
  //if file is not open (does not exist)
  if(!file.is_open())
    {
      cout << "Cannot find file.\n";
      *valid = false;
      return valid; //return "false" to valid, and loop in the main until "true"
    }
  else
    {
      if(file)
	{
	  file >> value;
	  file.ignore();
	}
      while(!file.eof() && file) //while the file has not "hit" the end line
	{
	  tree->insert(value); //read ints from the file and insert into the tree
	  file >> value; 
	  file.ignore();
	}
      file.close();
      *valid = true;
      return valid; //return "true" to valid, continue to phase 2
    }
}
