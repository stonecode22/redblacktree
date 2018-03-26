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
  bool valid = true;
  int numbers[100];
  
  cout << "Binary Search Tree\n";
  //primary phase, extract data values from either a file or console input
  do
    {
      cout << "'FILE' to insert data from file, 'CONSOLE' to insert data from console.\n";
      cin.getline(readChoice1, 10);
      for(int i = 0; i < strlen(readChoice1); i++)
	{
	  readChoice1[i] = toupper(readChoice1[i]);
	}
      
      if(strcmp(readChoice1, "FILE") == 0)
	{
	  getFileData(numbers, &valid, &tree);
	}
  
      if(strcmp(readChoice1, "CONSOLE") == 0)
	{
	  getConsoleData(numbers, &valid, &tree);
	}
      else
	{
	  cout << "Invalid command, try again.\n";
	  valid = false;
	}
    }while(valid == false); //if readChoice1 doesn't match anything, prompt user to try again
  
  tree.display();
  cout << endl;
  return 0;
}

bool getConsoleData(int* numbers, bool* valid, bst* tree)
{
  cout << "Enter values separated by spaces (end by using '-1'): ";
  int valueCount = 0;
  bool terminate = false;
  while(valueCount < 100 && terminate == false)
    {
      cin >> numbers[valueCount];
      tree->insert(numbers[valueCount]);
      if(numbers[valueCount] == -1)
	{
	  terminate = true;
	  tree->remove(-1);
	}
      valueCount++;
    }
  *valid = true;
  return valid;
}

bool getFileData(int* numbers, bool* valid, bst* tree)
{
  char fileName[50];
  int valueCount = 0;
  ifstream file;
  cout << "Enter the name of file to use: ";
  cin.getline(fileName, 49);
  file.open(fileName);
  
  if(!file.is_open())
    {
      cout << "Cannot find file.\n";
      *valid = false;
      return valid;
    }
  else
    {
      while(!file.eof())
	{
	  file >> numbers[valueCount];
	  valueCount++;
	}
      file.close();
      *valid = true;
      return valid;
    }
}
