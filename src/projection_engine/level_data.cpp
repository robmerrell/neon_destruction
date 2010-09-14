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
  LevelDetails details1;
  details1.id="1";
  details1.name="Intro";
  details1.filename="intro.xml";
  details1.score="--";
  details1.completed="0";
  details1.skipped="0";
  core_levels.push_back(details1);
  core_level_count++;
  
  
  LevelDetails details2;
  details2.id="2";
  details2.name="Green vs Ble";
  details2.filename="green_vs_blue.xml";
  details2.score="--";
  details2.completed="0";
  details2.skipped="0";
  core_levels.push_back(details2);
  core_level_count++;
  
  
  LevelDetails details3;
  details3.id="3";
  details3.name="Gauntlet Treasure";
  details3.filename="gauntlet_treasure.xml";
  details3.score="--";
  details3.completed="0";
  details3.skipped="0";
  core_levels.push_back(details3);
  core_level_count++;
  
  
  LevelDetails details4;
  details4.id="4";
  details4.name="Clock Tower";
  details4.filename="clock_tower.xml";
  details4.score="--";
  details4.completed="0";
  details4.skipped="0";
  core_levels.push_back(details4);
  core_level_count++;
  
  
  LevelDetails details5;
  details5.id="5";
  details5.name="Steps";
  details5.filename="steps.xml";
  details5.score="--";
  details5.completed="0";
  details5.skipped="0";
  core_levels.push_back(details5);
  core_level_count++;
  
  
  LevelDetails details6;
  details6.id="6";
  details6.name="Swing";
  details6.filename="swing.xml";
  details6.score="--";
  details6.completed="0";
  details6.skipped="0";
  core_levels.push_back(details6);
  core_level_count++;
  
  
  LevelDetails details7;
  details7.id="7";
  details7.name="Stack";
  details7.filename="stack.xml";
  details7.score="--";
  details7.completed="0";
  details7.skipped="0";
  core_levels.push_back(details7);
  core_level_count++;
  
  
  LevelDetails details8;
  details8.id="8";
  details8.name="Bottoms Up";
  details8.filename="bottoms_up.xml";
  details8.score="--";
  details8.completed="0";
  details8.skipped="0";
  core_levels.push_back(details8);
  core_level_count++;
  
  
  LevelDetails details9;
  details9.id="9";
  details9.name="PROMOTION";
  details9.filename="end_scene.xml";
  details9.score="--";
  details9.completed="0";
  details9.skipped="0";
  core_levels.push_back(details9);
}


void LevelData::parseUserData() {
  ifstream config_file("user_data.mja");
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


void LevelData::writeUserData() {
  ofstream config_file("tmp_save.mja");
  
  
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
      
      if (iter->filename != "end_scene.xml")
        config_file << iter->id << ":" << score << ":" << iter->completed << ":" << iter->skipped << endl;
    }
    config_file << "(endlvl)";
  }
  
  // rename tmp_save.mja to user_data.mja
  rename("tmp_save.mja", "user_data.mja");
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