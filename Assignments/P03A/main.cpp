/*****************************************************************************
*                    
*  Author:           Kolten Pulliam
*  Email:            klpulliam44@gmail.com
*  Label:            P03A
*  Title:            Program 3A - RockPaperScissorsLizardSpock
*  Course:           2143-Object-Oriented-Programming
*  Semester:         Fall 2021
* 
*  Description:
*        This program creates a two players that play a variant of 
*        RockPaperScissors. This accomplished by assigning random
*        "hands" to each player, which are really just unicode values
*        stored as strings. The players are then checked against each other
*        by seeing whose hand is greater than the other which is all done 
*        by overloading the greater than operator. 
*        (The first 5 classes, the two maps, and the unicode assignments )
*        (where all done by Professor Terry Griffin)
*        (https://github.com/rugbyprof)
* 
*  Usage:
*        N/A
* 
*  Files:            (list of all source files used in this program)
        main.cpp
        emoji.h
*****************************************************************************/
#include <iostream>
#include <fstream>
#include "emoji.h"    //https://github.com/99x/emojicpp
#include <functional>  // needed for `bind`
#include <map>
#include <random>
#include <string>

using namespace std;

#define ROCK u8"\U0000270A"
#define PAPER u8"\U0000270B"
#define SCISSORS u8"\U0001F44C"
#define LIZARD u8"\U0001F918"
#define SPOCK u8"\U0001F596"

#define ROCK2 u8"\U0001F5FB"
#define PAPER2 u8"\U0001F4C3"
#define SCISSORS2 u8"\U0001F52A"
#define LIZARD2 u8"\U0001F438"
#define SPOCK2 u8"\U0001F596"

/**
 * This class is used to test the random number generators by 
 * creating an array with the same sides as some die. Then 
 * counting the values generated between 1 and die size. 
 * There should be an equal number in every slot, which
 * for a 20 sided die is about .05 or 5 percent in each.
 * 
 */
class Tester {
    int* arr;
    int  size;

public:
    Tester() : size{20} {
        arr = new int[size + 1];
        initArr();
    }

    Tester(int size) : size{size} {
        arr = new int[size + 1];
        initArr();
    }

    void initArr() {
        for (int i = 0; i < size + 1; i++) {
            arr[i] = 0;
        }
    }

    // add random value to distribution table
    void load(int i) {
        arr[i]++;
    }

    // generate  the distribution table
    void distro(double res[], double total) {
        for (int i = 0; i < size + 1; i++) {
            res[i] = (double)arr[i] / total;
        }
    }
};

/**
 * DieRoll
 * @description: A class to implement roll playing dice rolls.
 * @methods:
 * private:
 *      int Random(Max) : returns a value between 0 and max.
 *      int Random(Min , Max) : returns a value between min and max
 *      void init(int , int)  : initialize class
 * public:
 *      DieRoll()
 *      DieRoll(int)
 *      DieRoll(int,int)
 *      void setDie(int)    : set sides
 *      int Roll(int,int)   :  NEEDS FIXING!!!!!!
 */
class DieRoll {
    int sides;

    int Random(int max) {
        return 1 + (rand() % max);
    }

    // min = 40 max = 100
    int Random(int min, int max) {
        return 1 + min + (rand() % (max - min));
    }
    void init(int _seed, int _sides) {
        sides = _sides;
        srand(_seed);
    }
public:
    DieRoll() {
        //cout << "default base" << endl;
        init(time(0), 6);
    }
    DieRoll(int _seed) {
        //cout << "overloaded const" << endl;
        init(_seed, 6);
    }
    DieRoll(int _seed, int _sides) {
        //cout << "overloaded const" << endl;
        init(_seed, _sides);
    }

    void setDie(int _sides) {
        sides = _sides;
    }

    // NEEDS FIXING!!!
    int Roll(int sides, int times) {
        int sum = 0;
        while (times--) {
            sum += Random(sides);
        }
        return sum;
    }
};


/**
 * RandRoll
 * @description: A random die roller using a "better" random
 *      number generator. Docs: https://www.cplusplus.com/reference/random/
 * 
 * @methods:
 *     int Roll(int)    : give the "sides" will return an int between 
 *                        1 and sides inclusive.
 * 
 */
class RandRoll {
    default_random_engine           generator;
    uniform_int_distribution< int > dieMap[21];

public:
    /**
     * Constructor
     * 
     * @description: Create an stl array that has the common dice values
     *              loaded as uniform distribution types.
     * 
     *  Wasteful, as not every array location has a uniform distribution 
     *  associated with it. Could you make it less wasteful?
     */
    RandRoll() {
        dieMap[4] = uniform_int_distribution< int >(1, 4);
        dieMap[6] = uniform_int_distribution< int >(1, 6);
        dieMap[8] = uniform_int_distribution< int >(1, 8);
        dieMap[10] = uniform_int_distribution< int >(1, 10);
        dieMap[12] = uniform_int_distribution< int >(1, 12);
        dieMap[20] = uniform_int_distribution< int >(1, 20);
    }

    /**
     * Generate a random number depending on the "sides" of the dice.
     */
    int Roll(int sides) {
        int diceRoll = dieMap[sides](generator);
        return diceRoll;
    };
};

/**
 * Hands
 * 
 * @description: A static class that only has references to
 *      emojis for printing out Rock Paper Scissors Lizard Spock
 * 
 * @methods:
 *      string RandHand()   : returns a random hand (emoji) 
 *      string Rock()       : returns the emoji for "rock" 
 *      string Paper()      : returns the emoji for "paper" 
 *      string Scissors()   : returns the emoji for "scissors" 
 *      string Lizard()     : returns the emoji for "lizard" 
 *      string Spock()      : returns the emoji for "spock" 
 */
struct Hands {
    const string rock = ROCK2;
    const string paper = PAPER2;
    const string scissors = SCISSORS2;
    const string lizard = LIZARD2;
    const string spock = SPOCK2;

    static map< string, string > Emojis;  // stl map
    //         name  , emoji

    static map< string, string > Names;  // stl map
    //         emoji  , name

    static string RandHand() {
        auto it = Emojis.begin();  // iterator to front of map
        
        // advance some random amnt of steps
        std::advance(it, rand() % Emojis.size());  

        string random_hand = it->second;  // grab emoji from map

        return random_hand;  // return rand emoji
    }

    static string Rock() {
        return Emojis["rock"];
    }
    static string Paper() {
        return Emojis["paper"];
    }
    static string Scissors() {
        return Emojis["scissors"];
    }
    static string Lizard() {
        return Emojis["lizard"];
    }
    static string Spock() {
        return Emojis["spock"];
    }
};

// initialize static data member for
// hands struct (class)
map< string, string > Hands::Emojis = {
    {"rock", ROCK2},
    {"paper", PAPER2},
    {"scissors", SCISSORS2},
    {"lizard", LIZARD2},
    {"spock", SPOCK2}};
// initialize static data member for
// hands struct (class)
map< string, string > Hands::Names = {
    {ROCK2, "rock"},
    {PAPER2, "paper"},
    {SCISSORS2, "scissors"},
    {LIZARD2, "lizard"},
    {SPOCK2, "spock"}};

/**
 * Rock Paper Scissors Lizard Spock
 * 
 * @description: A class to run the rock papers scissors game
 * 
 * Scissors cuts Paper
 * Paper covers Rock
 * Rock crushes Lizard
 * Lizard poisons Spock
 * Spock smashes Scissors
 * Scissors decapitates Lizard
 * Lizard eats Paper
 * Paper disproves Spock
 * Spock vaporizes Rock
 * Rock crushes Scissors
 */
class RPSLS : public DieRoll, public Hands {
public:
  RPSLS(): DieRoll(time(0)){
      string h = RandHand();
      cout<<Names[h]<<": " <<h<<endl;
  };
  RPSLS(int seed) : DieRoll(seed) {
      cout << "Rock: " << Rock() << endl;
  }
};

/**
 * Player
 * 
 * @description: A class to create players with a lot of
 * 
 * @methods: 
 *   Player()                            : Creates an unarmed player
 *   void AssignWeapons()                : Gives the player weapons to use 
 *   string GetWeapon1()                 : Gets the first weapon 
 *   string GetWeapon2()                 : Gets the second weapon
 *   bool operator>(const Player& other) : Checks which player wins
 *   friend ostream& operator<<(ostream& cout, const Player& plyr) : Prints player weapons
 * 
 *
 *
 */
class Player {
  string weapon1;
  string weapon2;

  public:
    Player() {
      weapon1 = "Unarmed";
      weapon2 = "Unarmed";
    }

    void AssignWeapons() {
      weapon1 = Hands::RandHand();
      weapon2 = Hands::RandHand();
      while(weapon2 == weapon1) {
        weapon2 = Hands::RandHand();
      }
    }

    string GetWeapon1() {
      return weapon1;
    }

    string GetWeapon2() {
      return weapon2;
    }

    /**
    * Overloaded Operator >
    * 
    * @description: Overloads the greater than operator to compare two players weapons,
    *               essentially creating the rules for the game.
    *
    */ 
    bool operator>(const Player& other) {
      // Checks if the first weapons tied, if so then check the second weapons
      if (this->weapon1 == other.weapon1){
        if (this->weapon2 == SCISSORS2 && other.weapon2 == PAPER2){
        return true; 
        }else if (this->weapon2 == PAPER2 && other.weapon2 == ROCK2){
        return true; 
        }else if (this->weapon2 == ROCK2 && other.weapon2 == LIZARD2){
        return true; 
        }else if (this->weapon2 == LIZARD2 && other.weapon2 == SPOCK2){
        return true; 
        }else if (this->weapon2 == SPOCK2 && other.weapon2 == SCISSORS2){
        return true; 
        }else if (this->weapon2 == SCISSORS2 && other.weapon2 == LIZARD2){
        return true; 
        }else if (this->weapon2 == LIZARD2 && other.weapon2 == PAPER2){
        return true; 
        }else if (this->weapon2 == PAPER2 && other.weapon2 == SPOCK2){
        return true; 
        }else if (this->weapon2 == SPOCK2 && other.weapon2 == ROCK2){
        return true; 
        }else if (this->weapon2 == ROCK2 && other.weapon2 == SCISSORS2){
        return true; 
        }
      }else{
        if (this->weapon1 == SCISSORS2 && other.weapon1 == PAPER2){
        return true; 
        }else if (this->weapon1 == PAPER2 && other.weapon1 == ROCK2){
        return true; 
        }else if (this->weapon1 == ROCK2 && other.weapon1 == LIZARD2){
        return true; 
        }else if (this->weapon1 == LIZARD2 && other.weapon1 == SPOCK2){
        return true; 
        }else if (this->weapon1 == SPOCK2 && other.weapon1 == SCISSORS2){
        return true; 
        }else if (this->weapon1 == SCISSORS2 && other.weapon1 == LIZARD2){
        return true; 
        }else if (this->weapon1 == LIZARD2 && other.weapon1 == PAPER2){
        return true; 
        }else if (this->weapon1 == PAPER2 && other.weapon1 == SPOCK2){
        return true; 
        }else if (this->weapon1 == SPOCK2 && other.weapon1 == ROCK2){
        return true; 
        }else if (this->weapon1 == ROCK2 && other.weapon1 == SCISSORS2){
        return true; 
        }
      }   
      return false;
    }

    /**
    * Overloaded Operator <<
    * 
    * @description: Overloads the greater than operator to compare two players weapons
    *
    */  
    friend ostream& operator<<(ostream& cout, const Player& plyr){
      if (plyr.weapon1 == "Unarmed" && plyr.weapon2 == "Unarmed") {
        cout << "Player is unarmed...\n";
      }else{
        cout << plyr.weapon1 << " + " << plyr.weapon2 << '\n';
      }
      return cout;
    }    
};

int main() {
  ofstream outFile("output.txt");
  DieRoll dr(time(0), 20); 
  Player p1; // gets two random weapons when constructed
  Player p2; // same

  for (int i = 0; i < 25; i++){
    p1.AssignWeapons();
    p2.AssignWeapons();

    if(p1 > p2){
      outFile << "Player 1 beat Player 2" << endl;
      if (p1.GetWeapon1() != p2.GetWeapon1()) {
        outFile << "Player 1's " << p1.GetWeapon1() 
          << " beat Player 2's " << p2.GetWeapon1() << "!" << endl;
      }else{
        outFile << "Player 1's " << p1.GetWeapon2() 
          << " beat Player 2's " << p2.GetWeapon2() << "!" << endl;
      }
    }else if(p2 > p1){
      outFile << "Player 2 beat Player 1" << endl;
      if (p1.GetWeapon1() != p2.GetWeapon1()) {
        outFile << "Player 2's " << p2.GetWeapon1() 
          << " beat Player 1's " << p1.GetWeapon1() << "!" << endl;
      }else{
        outFile << "Player 2's " << p2.GetWeapon2() 
          << " beat Player 1's " << p1.GetWeapon2() << "!" << endl;
      }
    }else{
      outFile << "It's a tie!" << endl;
      outFile << "Player1 Weapons: " << p1;
      outFile << "Player2 Weapons: " << p2;
    }
    outFile << '\n';
  }

  outFile.close();
  
  return 0;
}