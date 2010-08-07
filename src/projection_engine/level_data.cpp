#include "level_data.h"

// helper function to explode a string
void string_explode(string str, string separator, vector<string>* results){
    int found;
    found = str.find_first_of(separator);
    while(found != string::npos){
        if(found > 0){
            results->push_back(str.substr(0,found));
        }
        str = str.substr(found+1);
        found = str.find_first_of(separator);
    }
    if(str.length() > 0){
        results->push_back(str);
    }
}


LevelData* LevelData::inst = NULL; 

LevelData::LevelData() {}

LevelData* LevelData::Instance() {
  if (!inst) {
    inst = new LevelData;
    
    inst->core_level_count = 0;
    inst->current_level = "1";
  }
    
  return inst;
}


void LevelData::parseLevelList(string set) {
  string path = "level_lists/";
  
  TiXmlDocument level_details(path.append(set).c_str());
  level_details.LoadFile();
  
  TiXmlNode* list = level_details.FirstChild("levels");
  TiXmlNode* level_node;
  
  for (level_node = list->FirstChild(); level_node != 0; level_node = level_node->NextSibling() ) {
    LevelDetails details;
    details.id = level_node->ToElement()->Attribute("id");
    details.name = level_node->ToElement()->Attribute("name");
    details.filename = level_node->ToElement()->Attribute("filename");
    details.score = "--";
    details.completed = "0";
    details.skipped = "0";
    
    if (set == "core.xml") {
      core_levels.push_back(details);
      core_level_count++;
    }
  }
}


void LevelData::parseUserData() {
  ifstream config_file("user_data.mja");
  string line;
  string state="none"; // none, level_data, inprocess
  
  while (getline(config_file, line)) {
    if (line == "(lvl)") state = "level_data";
    if (line == "(endlvl)") state = "none";
    
    if (state == "level_data" && line != "(lvl)") {
      // id,score,completed,skipped
      vector<string> parsed_level;
      string_explode(line, ":", &parsed_level);
      
      vector<LevelDetails>::iterator iter;

      for (iter = core_levels.begin(); iter != core_levels.end(); iter++) {
        if (iter->id == parsed_level[0]) {
          iter->score = parsed_level[1];
          iter->completed = parsed_level[2];
          iter->skipped = parsed_level[3];
        }
      }
    }
    
  }
}


LevelDetails LevelData::getDetailsByPosition(int level_index) {
  level_index -= 1;
  
  return core_levels[level_index];
}


LevelDetails LevelData::getDetailsById(string id) {
  vector<LevelDetails>::iterator iter;
  
  for (iter = core_levels.begin(); iter != core_levels.end(); iter++) {
    if (iter->id == id)
      return *iter;
  }
}


LevelDetails LevelData::getCurrentDetails() {
  return getDetailsById(current_level);
}


string LevelData::getCurrentLevel() {
  return current_level;
}


void LevelData::setCurrentLevel(string _id) {
  current_level = _id;
}


string LevelData::getNextLevel() {
  bool found_current = false;
  vector<LevelDetails>::iterator iter;
  
  for (iter = core_levels.begin(); iter != core_levels.end(); iter++) {
    if (found_current) return iter->id;
    if (iter->id == current_level) found_current = true;
  }
  
  return "";
}


bool LevelData::canLoadNextLevel() {
  string next_level = getNextLevel();
  
  if (next_level.empty())
    return false;
  else
    return true;
}


int LevelData::getCoreLevelCount() {
  return core_level_count;
}