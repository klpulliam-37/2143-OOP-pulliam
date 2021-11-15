#ifndef WEAPONS
#define WEAPONS

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Dice.hpp"
#include "Helpers.hpp"

using namespace std;

#pragma once

/**
 * Weapon
 * @description: A class used to create different weapons 
 * utilizing a map.
 * @methods:
 *
 * public:
 *      Weapon()
 *      Weapon(vector< string > choices)
 *      Weapon(string n)
 *      double use()
 *      string getWeaponType()
 *      string getWeaponDamage()
 *      friend ostream& operator<<(ostream& os, const Weapon& w)
 */
class Weapon {
  private:
    string name;    // name of weapon
    string damage;  // damage per roll or "use"
    Dice*  die;
    map<string, vector<string>> Weapons = {
      {"fists", {"1.d.4", "1.d.6"}},
      {"sword", {"1.d.12", "2.d.6", "3.d.4"}},
      {"bow", {"1.d.8", "2.d.4", "1.d.10"}},
      {"spell", {"1.d.20", "2.d.10", "3.d.6", "5.d.4"}},
      {"magicW", {"1.d.4", "1.d.6"}},
      {"fire", {"1.d.6", "1.d.8"}},
    };

public:
    /**
     * @brief Construct a new Base Weapon object.
     * Also invokes the Dice class constructor with the "die" type
     */
    Weapon() {
        name = "Fists&Feet";
        damage = "1.d.4";
        die = new Dice(damage);
    }
    
    /**
     * @brief Overloaded Constructor for a new Base Weapon object.
     * Also invokes the Dice class constructor with the "die" type
     * @param choices-vector of string "die" choices like {"2.d.8","2.d.10","3.d.4"}
     */
    Weapon(vector< string > choices) {
        name = "Fists&Feet";
        damage = randomChoice(choices);
        die = new Dice(damage);
    }

    Weapon(string n) {
      name = n;
      auto it = Weapons.find(n);
      damage = randomChoice(it->second);
      die = new Dice(damage);
    }

    double use() {
        return die->roll();
    }

    string getWeaponType() {
      return name;
    }

    string getWeaponDamage() {
      return damage;
    }

    friend ostream& operator<<(ostream& os, const Weapon& w) {
        return os << "[" << w.name << " , " << w.damage << "]";
    }
};

#endif