#include "gameplay_scene.h"

#include <iostream>

void GameplayScene::setup() {
  defineBorder(true, true, true, true);
  
  // load a level
  loadLevel("intro.xml");
  // replaceLevel("stack.xml");
  
  // start the game loop
  scheduleLoop(60);
}


void GameplayScene::loadLevel(string level_file) {
  has_cannon = false;
  has_goal = false;
  string path = "levels/";
  
  TiXmlDocument level_data(path.append(level_file).c_str());
  level_data.LoadFile();

  string size, x, y, angle, type, physics, width, height, radius;
  Box *box;
  Platform *platform;
  Circle *circle;
  Triangle *triangle;
  
  TiXmlNode* level = level_data.FirstChild("level");
  TiXmlNode* object_node;
  
  for (object_node = level->FirstChild(); object_node != 0; object_node = object_node->NextSibling() ) {
    if (object_node->ToElement()->Attribute("type") == string("CANNON") && !has_cannon) {
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      
      Cannon *cannon = new Cannon(strtof(x.c_str(), NULL), strtof(y.c_str(), NULL));
      addObject(cannon);
      has_cannon = true;
    } if (object_node->ToElement()->Attribute("type") == string("GOAL")) {
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      
      Goal *goal = new Goal(strtof(x.c_str(), NULL), strtof(y.c_str(), NULL));
      addObject(goal);
      has_goal = true;
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
    } else if (object_node->ToElement()->Attribute("type") == string("TRIANGLE")) {
      // extract data from XML
      physics = object_node->ToElement()->Attribute("physics");
      x = object_node->ToElement()->Attribute("x");
      y = object_node->ToElement()->Attribute("y");
      width = object_node->ToElement()->Attribute("width");
      height = object_node->ToElement()->Attribute("height");
      angle = object_node->ToElement()->Attribute("angle");
      
      // create the actual triangle
      triangle = new Triangle(physics);
      triangle->setX(strtof(x.c_str(), NULL));
      triangle->setY(strtof(y.c_str(), NULL));
      triangle->setWidth(strtof(width.c_str(), NULL));
      triangle->setHeight(strtof(height.c_str(), NULL));
      triangle->setAngle(strtof(angle.c_str(), NULL));
      triangle->definePhysics(space);
      addObject(triangle);
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
}


void GameplayScene::replaceLevel(string level_file) {
  // free all of the sprites
  vector<Sprite*>::iterator iter;
  for (iter = objects.begin(); iter != objects.end(); iter++) {
    delete (*iter);
    (*iter) = NULL;
  }

  objects.clear();
  
  loadLevel(level_file);
}