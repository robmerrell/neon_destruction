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
    inst->locked_level_count = 0;
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
    details.unlocked = "0";
    details.stars = "0";
    
    if (set == "core.xml") {
      core_levels.push_back(details);
      
      if (details.filename != "end_scene.xml")
        core_level_count++;
    }
    
    if (set == "pack1.xml") {
      details.system_locked = "1";
      
      core_levels.push_back(details);
      locked_level_count++;
    }
  }
}


void LevelData::parseUserData() {
  char app_dir[255];
  int ret = PDL_GetDataFilePath("my_data.mja", app_dir, 256);
  string file_path(app_dir);

  ifstream config_file(file_path.c_str());
  string line;
  string state="none"; // none, level_data, inprocess
  
  while (getline(config_file, line)) {
    if (line == "(inp)") state = "inprocess";
    if (line == "(endinp)") state = "none";
    if (line == "(lvl)") state = "level_data";
    if (line == "(endlvl)") state = "none";
    
    if (state == "inprocess" && line != "(inp)") {
      // list,id
      vector<string> parsed_level;
      string_explode(line, ":", &parsed_level);
      
      current_level = parsed_level[1];
    }
    
    if (state == "level_data" && line != "(lvl)") {
      // id,score,completed,unlocked,stars
      vector<string> parsed_level;
      string_explode(line, ":", &parsed_level);
      
      vector<LevelDetails>::iterator iter;

      for (iter = core_levels.begin(); iter != core_levels.end(); iter++) {
        if (iter->id == parsed_level[0]) {
          iter->score = parsed_level[1];
          iter->completed = parsed_level[2];
          iter->unlocked = parsed_level[3];
          if (parsed_level.size() >= 5)
            iter->stars = parsed_level[4];
        }
      }
    }
    
  }
  
  config_file.close();
}


void LevelData::writeUserData() {
  char app_dir[255];
  int ret = PDL_GetDataFilePath("my_data.mja", app_dir, 256);
  string file_path(app_dir);
  
  ofstream config_file(file_path.c_str());
  
  if (config_file.is_open()) {
    if (!current_level.empty() && getDetailsById(current_level).filename != "end_scene.xml") {
      config_file << "(inp)" << endl;
      config_file << "core:" << current_level << endl;
      config_file << "(endinp)" << endl;
    }
    
    config_file << "(lvl)" << endl;
    vector<LevelDetails>::iterator iter;

    for (iter = core_levels.begin(); iter != core_levels.end(); iter++) {
      string score = iter->score;
      if (score == "--") score = "0";
      
      if (iter->filename != "end_scene.xml") {
        // cout << "s: " << score << endl;
        cout << iter->id << ":" << score << ":" << iter->completed << ":" << iter->unlocked << ":" << iter->stars << endl;
        config_file << iter->id << ":" << score << ":" << iter->completed << ":" << iter->unlocked << ":" << iter->stars << endl;
      }
    }
    config_file << "(endlvl)";
  }
  
  config_file.close();
  
  // rename tmp_save.mja to user_data.mja
  // int res = rename("./tmp_save.mja", "./my_data.mja");
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


void LevelData::updateCurrentScore(string new_score) {
  vector<LevelDetails>::iterator iter;
  
  for (iter = core_levels.begin(); iter != core_levels.end(); iter++) {
    if (iter->id == current_level) {
      if ((atoi(new_score.c_str()) < atoi(iter->score.c_str())) || iter->score == "--" || iter->score == "0") {
        iter->score = new_score;
        iter->completed = "1";
      }
    }
  } 
}

void LevelData::updateCurrentStars(int star_count) {
  vector<LevelDetails>::iterator iter;
  
  for (iter = core_levels.begin(); iter != core_levels.end(); iter++) {
    if (iter->id == current_level) {
      stringstream star_stream;
      star_stream << star_count;
      
      if (star_count > atoi(iter->stars.c_str()))
        iter->stars = star_stream.str();
    }
  } 
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


int LevelData::getCurrentLevelPlacement() {
  bool found_current = false;
  vector<LevelDetails>::iterator iter;
  int count=0;
  
  for (iter = core_levels.begin(); iter != core_levels.end(); iter++) {
    if (found_current) return count;
    if (iter->id == current_level) found_current = true;
    
    count++;
  }
  
  return 0;
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


int LevelData::getCoreLevelCount(bool show_core=true) {
  if (show_core)
    return core_level_count;
  else
    return locked_level_count;
}


string LevelData::getFinalScore() {
  vector<LevelDetails>::iterator iter;
  int score_count = 0;
  string message = "Total Shots Fired: ";
  
  for (iter = core_levels.begin(); iter != core_levels.end(); iter++) {
    score_count += atoi(iter->score.c_str()); 
  }
  
  stringstream score_stream;
  score_stream << score_count;
  
  message.append(score_stream.str());
  
  return message;
}
