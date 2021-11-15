#ifndef HELPERS
#define HELPERS

#include <iostream>
#include <math.h>
#include <vector>
#include <random>
#include <string>

using namespace std;

#pragma once

/**
 * @brief Splits a string into parts based on a delimiter
 *
 *      For example the string: "2.d.12" would be turned into 
 *      a vector => ["2","d","12"] and returned
 * 
 * @param s 
 * @param delimiter 
 * @return vector<string> 
 */
vector<string> tokenize(string s,string delimiter){
    size_t pos = 0;
    vector<string> tokens;
    while ((pos = s.find(delimiter)) != string::npos) {
        tokens.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);
    return tokens;
}

/**
 * @brief Chooses a random item from a vector of strings
 * 
 *      Example: 
 *          given => ["1.d.4","1.d.6","1.d.8"]
 *          Choose one of the 3 choices at random and return it.
 * 
 * @param choices 
 * @return string 
 */
string randomChoice(vector<string> choices){
  return choices[rand() % choices.size()];
}

/**
 * @brief Generates a random int for health values on characters
 * 
 * @param min - minimum of range 
 * @param max - maximum of range 
 * @return int 
 */
int randomHealth(int min, int max) {
  return rand() % (max - min) + min;
}

/**
 * @brief Generates a random double for regeneration values on characters
 * 
 * @param min - minimum of range 
 * @param max - maximum of range 
 * @return double 
 */
double randomRegen(int totalHealth) {
  int min = ceil(totalHealth * 0.01);
  int max = floor(totalHealth * 0.05);
  int regenRate = rand() % (max - min) + min;
  if (regenRate < 1) {
    regenRate = 1;
  }
  return regenRate;
}

#endif