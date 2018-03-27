//Binary Search Tree
#include<iostream>
#include<string.h>
#include<vector>
#include<fstream>
#include"bst.h"
using namespace std;

bool getConsoleData(int* numbers, bool* valid, bst* tree);
bool getFileData(int* numbers, bool* valid, bst* tree);

int main()
{
  bst tree;
  char readChoice1[10];
  char readChoice2[10];
  bool valid = true;
  int numbers[100];
  
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

  //Phase 3:
  //Purpose: prompt user to make additional edits (removing nodes, inserting nodes, re-displaying the tree)
  valid = true; //reusing valid for another loop
  cout << "INSERT a node, REMOVE a node, DISPLAY the tree, or QUIT.\n";

  
  
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
  while(valueCount < 100 && terminate == false) //for 100 numbers, insert index values into numbers array
    {
      cin >> numbers[valueCount];
      tree->insert(numbers[valueCount]); //insert value into the tree
      if(numbers[valueCount] == -1)
	{
	  terminate = true;
	  tree->remove(-1);
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
  int valueCount = 0;
  ifstream file;

  //prompt user to insert the name of the file to be used
  cout << "Enter the name of file to use: ";
  cin.getline(fileName, 49);
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
      while(!file.eof()) //while the file has not "hit" the end line
	{
	  file >> numbers[valueCount];
	  tree->insert(numbers[valueCount]);
	}
      tree->remove(numbers[valueCount]); //error without this, where the last value is taken in twice
      file.close();
      *valid = true;
      return valid; //return "true" to valid, continue to phase 2
    }
}
