#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../tinyxml/tinyxml.h"

#include "../game_const.h"

#ifndef LEVEL_DATA_H
#define LEVEL_DATA_H

using namespace std;

struct LevelDetails {
  string name;
  string filename;
  string id;
  string completed;
  string score;
  string unlocked;
  string stars;
  string system_locked;
};

class LevelData {
  private:
    LevelData();
    LevelData(const LevelData&);
    LevelData& operator=(const LevelData&);
    
    static LevelData* inst;
    int core_level_count;
    int locked_level_count;
    string current_level;
    
    vector<LevelDetails> core_levels;
    
  public:
    static LevelData* Instance();
    
    /**
     * Parse the level list in the (string) file
     */
    void parseLevelList(string);
    
    /**
     * Parse the user data
     */
    void parseUserData();
    
    /**
     * Write the user data
     */
    void writeUserData();
    
    /**
     * Get the level details
     */
    LevelDetails getDetailsByPosition(int);
    LevelDetails getDetailsById(string);
    LevelDetails getCurrentDetails();
    
    /**
     * Get and set the current level id
     */
    string getCurrentLevel();
    int getCurrentLevelPlacement();
    void setCurrentLevel(string);
    string getNextLevel();
    bool canLoadNextLevel();
    
    /**
     * Update data for the current level
     */
    void updateCurrentScore(string);
    
    /**
     * Update stars for the current level
     */
    void updateCurrentStars(int);
    
    /**
     * Get the count of all core levels
     */
    int getCoreLevelCount();
    int getCoreLevelCount(bool);
    
    /**
     * Count the final score for the game
     **/
    string getFinalScore();
};

#endif