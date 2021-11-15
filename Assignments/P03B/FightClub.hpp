#ifndef FIGHTCLUB
#define FIGHTCLUB

#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <vector>

#include "Characters.hpp"

using namespace std;

/**
 * Attackers
 * @description: A class used to create a que of attackers.
 * @methods:
 *
 * public:
 *      Attackers()
 *      Attackers(ifstream& inFile)
 *      void PrintQue()
 *      int GetTotalAtkrs()
 */
class Attackers {
  private:
    vector<BaseCharacter> que;
    BaseCharacter* atkr;
    int totalAtkrs;
  
  public:
    friend class FightClub;

    Attackers() {
      for (int i = 0; i < 100; i++) {
        if (i % 5 == 0) {
          atkr = new Warrior();
        }
        if (i % 5 == 1) {
          atkr = new Wizard();
        }
        if (i % 5 == 2) {
          atkr = new Archer();
        }
        if (i % 5 == 3) {
          atkr = new Elf();
        }
        if (i % 5 == 4) {
          atkr = new DragonBorn();
        }
      }
    }

    Attackers(ifstream& inFile) {
      string atkrType;

      while(!inFile.eof()) {
        inFile >> atkrType;
        if(atkrType == "warrior") {
          atkr = new Warrior();
        }
        else if(atkrType == "wizard") {
          atkr = new Wizard();
        }
        else if(atkrType == "archer") {
          atkr = new Archer();
        }
        else if(atkrType == "elf") {
          atkr = new Elf();
        }
        else if(atkrType == "dragonborn") {
          atkr = new DragonBorn();
        }
        que.push_back(*atkr);
      }
      
      totalAtkrs = que.size();
    }

    void PrintQue() {
      cout << "\n-------------------ATTACKERS QUE-------------------\n";
      for (auto it : que) {
        cout << it << '\n';
      }
      cout << "Number of Attackers: " << totalAtkrs;
    }

    int GetTotalAtkrs() {
      return totalAtkrs;
    }
};

/**
 * Defenders
 * @description: A class used to create a que of defenders.
 * @methods:
 *
 * public:
 *      Defenders(int numAtkrs)
 *      void PrintQue()
 *      int GetTotalDndrs()
 */
class Defenders {
  private:
    vector<BaseCharacter> que;
    BaseCharacter* dndr;
    int totalDndrs;

  public:
    friend class FightClub;

    Defenders(int numAtkrs) {
      if (numAtkrs <= 100) {
        totalDndrs = 5;
        for (int i = 0; i < totalDndrs; i++) {
          if (i % 5 == 0) {
            dndr = new Warrior();
          }
          else if (i % 5 == 1) {
            dndr = new Wizard();
          }
          else if (i % 5 == 2) {
            dndr = new Archer();
          }
          else if (i % 5 == 3) {
            dndr = new Elf();
          }
          else if (i % 5 == 4) {
            dndr = new DragonBorn();
          }
          que.push_back(*dndr);
        }
      }
      if (numAtkrs > 100) {
        totalDndrs = round(numAtkrs / 100) * 5;
        for (int i = 0; i < totalDndrs; i++) {
          if (i % 5 == 0) {
            dndr = new Warrior();
            dndr->hp *= 25; // Beefs up the defenders for survivability
            dndr->maxHp = dndr->hp;
          }
          else if (i % 5 == 1) {
            dndr = new Wizard();
            dndr->hp *= 25; // Beefs up the defenders for survivability
            dndr->maxHp = dndr->hp;
          }
          else if (i % 5 == 2) {
            dndr = new Archer();
            dndr->hp *= 25; // Beefs up the defenders for survivability
            dndr->maxHp = dndr->hp;
          }
          else if (i % 5 == 3) {
            dndr = new Elf();
            dndr->hp *= 25; // Beefs up the defenders for survivability
            dndr->maxHp = dndr->hp;
          }
          else if (i % 5 == 4) {
            dndr = new DragonBorn();
            dndr->hp *= 25; // Beefs up the defenders for survivability
            dndr->maxHp = dndr->hp;
          }
          que.push_back(*dndr);
        }
      }
    }

    void PrintQue() {
      cout << "\n-------------------DEFENDERS QUE-------------------\n";
      for (auto it : que) {
        cout << it << '\n';
      }
      cout << "Number of Defenders: " << GetTotalDndrs();
    }

    int GetTotalDndrs() {
      return totalDndrs;
    }
};

/**
 * FightClub
 * @description: A class used to handle the interactions between
 * the attackers and defenders.
 * @methods:
 *
 * public:
 *      FightClub(ifstream& inFile)
 *      void CreateArmies(ifstream& inFile)
 *      void CommenceBattle()
 *      void Fight()
 *      void Combat()
 *      void DisplayFight()
 *      void MatchCharType(string wantedType)
 *      void SwitchDefender(string wantedType)
 *      void HealDefenders()
 *      void RemoveDef(int i)
 *      void RemoveAtkr(int i)
 *      PickNextBest()
 *      void gameOver(char winner)
 */
class FightClub {
  private: 
    Attackers* AQue;
    Defenders* DQue;
    vector<BaseCharacter> DeathQue;
    BaseCharacter* CaptainBase;
    BaseCharacter* Invader;
    BaseCharacter* GrimReaper;
    int capElem;
    int invElem;
    int PNBRuns = 0;
    bool bgameOver = false;

  public:
    /**
     * @brief Constructor 
     * 
     * Creates a new FightClub object by passing in 
     * the input file.
     * 
     * @param ifstream& inFile - Input file with list of attackers
     * 
     * @return N/A
     */
    FightClub(ifstream& inFile) {
      CreateArmies(inFile);
    }

    /**
     * @brief Member Function 
     * 
     * Creates two new que's of attackers and defenders.
     * 
     * @param ifstream& inFile - Input file with list of attackers
     * 
     * @return void
     */
    void CreateArmies(ifstream& inFile){
      AQue = new Attackers(inFile);
      Invader = &AQue->que.at(0);
      invElem = 0;
      DQue = new Defenders(AQue->GetTotalAtkrs());
      CaptainBase = &DQue->que.at(0);
      capElem = 0;
      CommenceBattle();
    }

    /**
     * @brief Member Function 
     * 
     * Begins the fight between the attackers and defenders.
     * 
     * @return void
     */
    void CommenceBattle() {
      cout << "\n-------------------Battle Commenced-------------------\n";
      Fight();
      cout << "\nFight Ended...\n";
    }

    /**
     * @brief Member Function 
     * 
     * Controls the rounds between each fight.
     * 
     * @return void
     */
    void Fight() {
      // Matches the def type with the current atkr type
      MatchCharType(Invader->charType); 
    }

    /**
     * @brief Member Function 
     * 
     * Handles the damage done to each character and
     * what to do when a character dies.
     * 
     * @return void
     */
    void Combat() {
      while(CaptainBase->hp > 0 && Invader->hp > 0) {
        // Attacker deals damage to defender
        CaptainBase->TakeDamage(Invader->weapon->use());
        if (CaptainBase->hp <= 0) {
          if (DQue->que.empty()) {
              bgameOver = true;
              gameOver('A');
              return;
          }else{
            RemoveDef(capElem);
            DisplayFight(); 
            if (!DQue->que.empty()) {
              CaptainBase = &DQue->que.at(0);
              capElem = 0;
            }else{
              bgameOver = true;
              gameOver('A');
              return;
            }
          }
        }else{
          // Defender then deals damage to attacker
          Invader->TakeDamage(CaptainBase->weapon->use());
          if (Invader->hp <= 0) {

            if (AQue->que.empty()) {
              cout << "INVADER Que Empty...\n";
              bgameOver = true;
              gameOver('D');
              return;
            }else{
              RemoveAtkr(invElem);
              DisplayFight();
              if (!AQue->que.empty()) {
                Invader = &AQue->que.at(0);
                invElem = 0;
              }else{
                cout << "INVADER Que Empty...\n";
                bgameOver = true;
                gameOver('D');
                return;
              }
            }
          }else{
            // All defenders heal and only the current attacker heals, 
            // using each characters health regen stat
            Invader->RegenHealth();
            SwitchDefender(CaptainBase->charType);
            HealDefenders();

          }
        }
      }
      Fight();
    }

    /**
     * @brief Member Function 
     * 
     * Displays the progress and results of the fight to 
     * the console.
     * 
     * @return void
     */
    void DisplayFight() {
      cout << "Defenders Left: " << DQue->que.size()
            << '\n' << "Attackers Left: "  << AQue->que.size() << '\n';
      system("clear");
    }

    /**
     * @brief Member Function 
     * 
     * Ensures that the defender type matches the attacker type.
     *
     * @param string wantedType - Character type to match with attacker
     * 
     * @return void
     */
    void MatchCharType(string wantedType) {
      int i = 0;
      while (CaptainBase->charType != wantedType && i != DQue->que.size()) {
        CaptainBase = &DQue->que.at(i);
        i++;
      }
      if (i == DQue->que.size()) {
        PNBRuns++;
        PickNextBest();
      }else{
        Combat();
      } 
    }

    /**
     * @brief Member Function 
     * 
     * Switches out the current defender in order to let it heal.
     *
     * @param string wantedType - Character type to match with attacker
     * 
     * @return void
     */
    void SwitchDefender(string wantedType) {
      BaseCharacter* sameChar = CaptainBase;
      int i = 0;
      while (CaptainBase->charType != wantedType 
      && i != DQue->que.size() && CaptainBase != sameChar) {
        CaptainBase = &DQue->que.at(i);
        i++;
      }
      if (i == DQue->que.size()) {
        PNBRuns++;
        PickNextBest();
      }
    }

     /**
     * @brief Member Function 
     * 
     * Heals all of the defenders in the defender que.
     *
     * @return void
     */
    void HealDefenders() {
      BaseCharacter* healer;
      for (int i = 0; i < DQue->que.size(); i++) {
        healer = &DQue->que.at(i);
        healer->RegenHealth();
        // cout << "Defender: " << i + 1 << " healed!\n"; // Debug Line 
      }
    }

    /**
     * @brief Member Function 
     * 
     * Removes a defender from the defender que.
     *
     * @return void
     */
    void RemoveDef(int i) {
      DQue->que.erase(DQue->que.begin() + i);
      if (!DQue->que.empty()) {
        CaptainBase = &DQue->que.at(0);
        capElem = 0;
        DQue->totalDndrs--;
      }
    }
    
    /**
     * @brief Member Function 
     * 
     * Removes an attacker from the attacker que.
     *
     * @return void
     */
    void RemoveAtkr(int i) {
      AQue->que.erase(AQue->que.begin() + i);
      if (!AQue->que.empty()) {
        Invader = &AQue->que.at(0);
        invElem = 0;
        AQue->totalAtkrs--;
      }
    }

    /**
     * @brief Member Function 
     * 
     * Picks the next best character type if a que is out of those 
     * character types.
     *
     * @return void
     */
    void PickNextBest() {
      // search for dragonborn with the most health
      if (PNBRuns == 1) {
        // cout << "Searching for Dragonborn...\n"; // Debug Line 
        MatchCharType("Dragonborn");
      }
      // if no dragonborn, search for elf with the most health
      if (PNBRuns == 2) {
        MatchCharType("Elf");
      }
      // if no elf, search for the warrior with the most health
      if (PNBRuns == 3) {
        MatchCharType("Warrior");
      }
      // if no warrior, search for the archer with the most health
      if (PNBRuns == 4) {
        MatchCharType("Archer");
      }
      // if no archer, search for the wizard with the most health
      if (PNBRuns == 5) {
        MatchCharType("Wizard");
      }
    }

    /**
     * @brief Member Function 
     * 
     * Ends the game and prints out which team won.
     *
     * @return void
     */
    void gameOver(char winner) {
      if(winner == 'A') {
        cout << "Attackers Win!\n";
      }
      else if (winner == 'D') {
        cout << "Defenders Win!\n";
      }
    }  
};

#endif