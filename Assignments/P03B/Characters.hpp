#ifndef CHARACTERS
#define CHARACTERS

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <map>

#include "Dice.hpp"
#include "Helpers.hpp"
#include "Weapons.hpp"

/**
 * BaseCharacter
 * @description: A class used as a base for the different character types.
 * @methods:
 *
 * public:
 *      BaseCharacter()
 *      virtual double attack()
 *      virtual void TakeDamage(int damage)
 *      virtual void RegenHealth()
 *      friend ostream& operator<<(ostream& cout, const BaseCharacter& Char)
 */
class BaseCharacter {

  public:
    string name;
    string charType;
    int hp;
    int maxHp;
    int hpRegen;
    Weapon *weapon;
    Weapon* weaponEnhancement = nullptr;

    BaseCharacter() {
      name = "Nameless";
      weapon = new Weapon("fists");
    }

    virtual double attack() {
      return weapon->use();
    }

    virtual void TakeDamage(int damage) {
      hp -= damage;
    }

    virtual void RegenHealth() {
      // Regenerates the character health without letting it go 
      // beyond what it orginally was when the character was created
      if (!(hp + hpRegen > maxHp)) {
        hp += hpRegen;
      }else{
        int dif = maxHp - hp;
        hp += dif;
      }
    }

    // Prints out the character stats
    friend ostream& operator<<(ostream& cout, const BaseCharacter& Char) {
      cout << "Character Name: " << Char.name << '\n';
      cout << "Character Type: " << Char.charType << '\n';
      cout << "Character HP: " << Char.hp << '\n';
      cout << "Character HP Regen: " << Char.hpRegen << '\n';

      string possibleDamage = Char.weapon->getWeaponDamage();
      string type = Char.weapon->getWeaponType();
      int actualDamage = Char.weapon->use();
      if (Char.weaponEnhancement != nullptr) {
        string enhancementType = Char.weaponEnhancement->getWeaponType();
        int actualEnhancementDamage = Char.weaponEnhancement->use();
        cout << "Weapon Type: " << type << " + " << enhancementType << '\n';
        cout << "Possible Damage: " << Char.weapon->getWeaponDamage() << " + " 
              << Char.weaponEnhancement->getWeaponDamage() << '\n';
        cout << "Actual Damage: " << actualDamage + actualEnhancementDamage<< '\n';
      }else{
        cout << "Weapon Type: " << type << '\n';
        cout << "Possible Damage: " << possibleDamage << '\n';
        cout << "Actual Damage: " << actualDamage << '\n';
      }
      return cout;
    }
};

/**
 * Warrior
 * @description: A warrior class derived from BaseCharacter
 * @methods:
 *
 * public:
 *      Warrior()
 *      Warrior(string n)
 *      double attack() override
 */
class Warrior : public BaseCharacter {  
  public:
    Warrior() {
      name = "Nameless Warrior";
      charType = "Warrior";
      weapon = new Weapon("sword");
      hp = randomHealth(70, 85);
      maxHp = hp;
      hpRegen = randomRegen(hp);
    }

    Warrior(string n) {
      name = n;
      charType = "Warrior";
      weapon = new Weapon("sword");
      hp = randomHealth(70, 85);
      maxHp = hp;
      hpRegen = randomRegen(hp);
    }

    double attack() override {
      return weapon->use();
    }
};

/**
 * Wizard
 * @description: A wizard class derived from BaseCharacter
 * @methods:
 *
 * public:
 *      Wizard()
 *      Wizard(string n)
 *      double attack() override
 */
class Wizard : public BaseCharacter {  
  public:
    Wizard() {
      name = "Nameless Wizard";
      charType = "Wizard";
      weapon = new Weapon("spell");
      hp = randomHealth(50, 75);
      maxHp = hp;
      hpRegen = randomRegen(hp);
    }

    Wizard(string n) {
      name = n;
      charType = "Wizard";
      weapon = new Weapon("spell");
      hp = randomHealth(50, 75);
      maxHp = hp;
      hpRegen = randomRegen(hp);
    }

    double attack() override {
      return weapon->use();
    }
};

/**
 * Archer
 * @description: An archer class derived from BaseCharacter
 * @methods:
 *
 * public:
 *      Archer()
 *      Archer(string n)
 *      double attack() override
 */
class Archer : public BaseCharacter {  
  public:
    Archer() {
      name = "Nameless Archer";
      charType = "Archer";
      weapon = new Weapon("bow");
      hp = randomHealth(50, 65);
      maxHp = hp;
      hpRegen = randomRegen(hp);
    }

    Archer(string n) {
      name = n;
      charType = "Archer";
      weapon = new Weapon("bow");
      hp = randomHealth(50, 65);
      maxHp = hp;
      hpRegen = randomRegen(hp);
    }

    double attack() override {
      return weapon->use();
    }
};

/**
 * Elf
 * @description: An elf class derived from BaseCharacter
 * @methods:
 *
 * public:
 *      Elf()
 *      Elf(string n)
 *      double attack() override
 */
class Elf : public BaseCharacter {  
  public:
    Elf() {
      name = "Nameless Elf";
      charType = "Elf";
      weapon = new Weapon("spell");
      weaponEnhancement = new Weapon("sword");
      hp = randomHealth(50, 75);
      maxHp = hp;
      hpRegen = randomRegen(hp);
    }

    Elf(string n) {
      name = n;
      charType = "Elf";
      weapon = new Weapon("spell");
      weaponEnhancement = new Weapon("sword");
      hp = randomHealth(50, 75);
      maxHp = hp;
      hpRegen = randomRegen(hp);
    }

    double attack() override {
      return weapon->use() + weaponEnhancement->use();
    }
};

/**
 * DragonBorn
 * @description: A dragonborn class derived from BaseCharacter
 * @methods:
 *
 * public:
 *      DragonBorn()
 *      DragonBorn(string n)
 *      double attack() override
 */
class DragonBorn : public BaseCharacter {  
  public:
    DragonBorn() {
      name = "Nameless Dragonborn";
      charType = "Dragonborn";
      weapon = new Weapon("spell");
      weaponEnhancement = new Weapon("fire");
      hp = randomHealth(75, 95);
      maxHp = hp;
      hpRegen = randomRegen(hp);
    }

    DragonBorn(string n) {
      name = n;
      charType = "Dragonborn";
      weapon = new Weapon("spell");
      weaponEnhancement = new Weapon("fire");
      hp = randomHealth(75, 95);
      maxHp = hp;
      hpRegen = randomRegen(hp);
    }

    double attack() override {
      return weapon->use() + weaponEnhancement->use();
    }
};

#endif