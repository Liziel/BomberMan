#include "blocDisplay.hh"

namespace Component{
  groundDisplay::groundDisplay(Entity::GameObject* _p, Engine::Graphic* _g)
    : Component::abstract(_p), cube(new object3d::cubeVertex(__GROUNDTEXTURE)), engine(_g) {
    double		x,y;
    parent->getPosition(x, y);
    cube->setPosition(x*3, y*3, object3d::cubeVertex::Ground);
    cube->scale(glm::vec3(3,3,3));
    engine->addObject(cube);
  }
  groundDisplay::~groundDisplay() { delete cube; }

  indestructibleDisplay::indestructibleDisplay(Entity::GameObject* _p, Engine::Graphic* _g)
    : Component::abstract(_p), cube(new object3d::cubeVertex(__INDESTEXTURE)), engine(_g) {
    double		x,y;
    parent->getPosition(x, y);
    cube->setPosition(x*3, y*3, object3d::cubeVertex::Up);
    cube->scale(glm::vec3(3,3,3));
    engine->addObject(cube);
  }
  indestructibleDisplay::~indestructibleDisplay() { delete cube; }

  bookshelfDisplay::bookshelfDisplay(Entity::GameObject* _p, Engine::Graphic* _g)
    : Component::abstract(_p), cube(new object3d::cubeVertex(__BOOKSHELFTEXTURE)), engine(_g) {
    double		x,y;
    parent->getPosition(x, y);
    cube->setPosition(x*3, y*3, object3d::cubeVertex::Up);
    cube->scale(glm::vec3(2.5,2.5,2.5));
    engine->addObject(cube);
    attachCallback(Event::Info::disableCollision,
		   new Event::FixedCallback([this](Event::Data&) {
		     engine->subObject(cube);
		     }));
  }
  bookshelfDisplay::~bookshelfDisplay() { delete cube; }
};
