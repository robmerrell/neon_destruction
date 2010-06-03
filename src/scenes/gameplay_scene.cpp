#include "gameplay_scene.h"

#include <iostream>

void GameplayScene::setup() {
  defineBorder(true, true, true, true);
  
  has_cannon = false;
  
  TiXmlDocument level_data("levels/intro.xml");
  level_data.LoadFile();

  string size, x, y, angle, type, physics;
  Box *box;
  Platform *platform;
  
  TiXmlNode* level = level_data.FirstChild("level");
  TiXmlNode* object_node;
  
  for (object_node = level->FirstChild(); object_node != 0; object_node = object_node->NextSibling() ) {
    if (object_node->ToElement()->Attribute("type") == string("CANNON") && !has_cannon) {
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      
      Cannon *cannon = new Cannon(strtof(x.c_str(), NULL), strtof(y.c_str(), NULL));
      addObject(cannon);
      has_cannon = true;
    } if (object_node->ToElement()->Attribute("type") == string("BOX")) {
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
    } else if (object_node->ToElement()->Attribute("type") == string("PLATFORM")) {
      // extract data from XML
      size = object_node->ToElement()->Attribute("size");
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      angle = object_node->ToElement()->Attribute("angle");
      type = "PLATFORM_" + size;
      
      // create the platform
      platform = new Platform(type);
      platform->setX(strtof(x.c_str(), NULL));
      platform->setY(strtof(y.c_str(), NULL));
      platform->setAngle(strtof(angle.c_str(), NULL));
      platform->definePhysics(space);
      addObject(platform);
    }
  }
  
  // start the game loop
  scheduleLoop(60);
}