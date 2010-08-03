#include "level_data.h"

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
    
    if (set == "core.xml") {
      core_levels.push_back(details);
      core_level_count++;
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