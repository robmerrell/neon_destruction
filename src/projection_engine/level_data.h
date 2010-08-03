#include <string>
#include <iostream>
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
};

class LevelData {
  private:
    LevelData();
    LevelData(const LevelData&);
    LevelData& operator=(const LevelData&);
    
    static LevelData* inst;
    int core_level_count;
    string current_level;
    
    vector<LevelDetails> core_levels;
    
  public:
    static LevelData* Instance();
    
    /**
     * Parse the level list in the (string) file
     */
    void parseLevelList(string);
    
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
    void setCurrentLevel(string);
    string getNextLevel();
    bool canLoadNextLevel();
};

#endif