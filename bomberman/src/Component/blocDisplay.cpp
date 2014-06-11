#include "blocDisplay.hh"

namespace Component{
  groundDisplay::groundDisplay(Entity::GameObject* _p, Engine::Graphic* _g)
    : Component::abstract(_p), cube(new object3d::cubeVertex(__GROUNDTEXTURE)), engine(_g) {
    double		x,y;
    parent->getPosition(x, y);
    cube->setPosition(x, y, object3d::cubeVertex::Ground);
    engine->addObject(cube);
  }
  groundDisplay::~groundDisplay() {}

  indestructibleDisplay::indestructibleDisplay(Entity::GameObject* _p, Engine::Graphic* _g)
    : Component::abstract(_p), cube(new object3d::cubeVertex(__INDESTEXTURE)), engine(_g) {
    double		x,y;
    parent->getPosition(x, y);
    cube->setPosition(x, y, object3d::cubeVertex::Ground);
    engine->addObject(cube);
  }
  indestructibleDisplay::~indestructibleDisplay() {}
};
