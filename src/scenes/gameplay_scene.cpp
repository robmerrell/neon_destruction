#include "gameplay_scene.h"

#include <iostream>

void GameplayScene::setup() {
  defineBorder(true, true, true, true);
  
  TiXmlDocument level_data("levels/intro.xml");
  level_data.LoadFile();

  string size, x, y, angle, type, physics;
  Box *box;
  
  TiXmlNode* level = level_data.FirstChild("level");
  TiXmlNode* object_node;
  
  for (object_node = level->FirstChild(); object_node != 0; object_node = object_node->NextSibling() ) {
    if (object_node->ToElement()->Attribute("type") == string("BOX")) {
      // extract data from XML
      size = object_node->ToElement()->Attribute("size");
      physics = object_node->ToElement()->Attribute("physics");
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      angle = object_node->ToElement()->Attribute("angle");
      type = "BOX_" + size;

      // create the actual box
      box = new Box(type, physics);
      box->setX(strtof(x.c_str(), NULL));
      box->setY(strtof(y.c_str(), NULL));
      box->setAngle(strtof(angle.c_str(), NULL));
      box->definePhysics(space);
      addObject(box);
    }
  }
  
  // start the game loop
  scheduleLoop(60);
}