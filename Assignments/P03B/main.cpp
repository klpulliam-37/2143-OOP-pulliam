/*****************************************************************************
*                    
*  Author:           Kolten Pulliam
*  Email:            klpulliam44@gmail.com
*  Label:            P03B
*  Title:            Program 3B - Fight Club
*  Course:           2143-Object-Oriented-Programming
*  Semester:         Fall 2021
* 
*  Description:
*        This program creates two vectors holding with one holding a group of
*        attackers and the other holding a group of defenders. The two groups
*        will battle each other and a winner will be decided once one of 
*        the groups completely dies out.
* 
*  Usage:
*        N/A
* 
*  Files:            (list of all source files used in this program)
        main.cpp
        Weapons.hpp
        Characters.hpp
        Dice.hpp
        FightClub.hpp
        Helpers.hpp
*****************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "Weapons.hpp"
#include "Characters.hpp"
#include "FightClub.hpp"

using namespace std;

void OpenFiles(ifstream& inFile);

int main() {
  srand(time(0));
  ifstream inFile;
  OpenFiles(inFile);

  FightClub Game(inFile);  

  cout << "End of Program\n";
  
  return 0;
}

/**
* @brief Function
* 
* Opens the input file.
* 
* @param ifstream& inFile - Input file object that will be opened.
* 
* @return N/A
*/
void OpenFiles(ifstream& inFile) {
  string inFileName;

  // Checks if the input file opened
  cout << "Please give the name of the input file...\n";
  cin >> inFileName;
  inFile.open(inFileName);
  while (!inFile.is_open()) {
    cout << "The input file did not open, please try again...\n";
    cin >> inFileName;
  }
  cout << "The input file is now open.\n";
}