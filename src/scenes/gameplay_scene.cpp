#include "gameplay_scene.h"

#include <iostream>

void GameplayScene::setup() {
  defineBorder(true, true, true, true);
  
  has_cannon = false;
  
  TiXmlDocument level_data("levels/intro.xml");
  level_data.LoadFile();

  string size, x, y, angle, type, physics, width, height, radius;
  Box *box;
  Platform *platform;
  Circle *circle;
  
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
      physics = object_node->ToElement()->Attribute("physics");
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      width = object_node->ToElement()->Attribute("width");
      height = object_node->ToElement()->Attribute("height");
      angle = object_node->ToElement()->Attribute("angle");

      // create the actual box
      box = new Box(physics);
      box->setX(strtof(x.c_str(), NULL));
      box->setY(strtof(y.c_str(), NULL));
      box->setWidth(strtof(width.c_str(), NULL));
      box->setHeight(strtof(height.c_str(), NULL));
      box->setAngle(strtof(angle.c_str(), NULL));
      box->definePhysics(space);
      addObject(box);
    } else if (object_node->ToElement()->Attribute("type") == string("PLATFORM")) {
      // extract data from XML
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      width = object_node->ToElement()->Attribute("width");
      angle = object_node->ToElement()->Attribute("angle");

      // create the platform
      platform = new Platform();
      platform->setX(strtof(x.c_str(), NULL));
      platform->setY(strtof(y.c_str(), NULL));
      platform->setWidth(strtof(width.c_str(), NULL));
      platform->setAngle(strtof(angle.c_str(), NULL));
      platform->definePhysics(space);
      addObject(platform);
    } else if (object_node->ToElement()->Attribute("type") == string("CIRCLE")) {
      // extract data from XML
      physics = object_node->ToElement()->Attribute("physics");
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      radius = object_node->ToElement()->Attribute("radius");

      // create the 
      circle = new Circle(physics);
      circle->setX(strtof(x.c_str(), NULL));
      circle->setY(strtof(y.c_str(), NULL));
      circle->setRadius(strtof(radius.c_str(), NULL));
      circle->definePhysics(space);
      addObject(circle);
    }
  }
  
  // start the game loop
  scheduleLoop(60);
}