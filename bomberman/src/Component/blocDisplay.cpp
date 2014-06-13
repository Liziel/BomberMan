#include "blocDisplay.hh"

namespace Component{
  groundDisplay::groundDisplay(Entity::GameObject* _p, Engine::Graphic* _g)
    : Component::abstract(_p), cube(new object3d::cubeVertex(__GROUNDTEXTURE)), engine(_g) {
    double		x,y;
    const glm::vec4&	hitbox = parent->getHitBox();
    parent->getPosition(x, y);
    cube->setPosition(x*3, y*3, object3d::cubeVertex::Ground);
    cube->scale(glm::vec3(3,3,3));
    engine->addObject(cube);
  }
  groundDisplay::~groundDisplay() { delete cube; }

  indestructibleDisplay::indestructibleDisplay(Entity::GameObject* _p, Engine::Graphic* _g)
    : Component::abstract(_p), cube(new object3d::cubeVertex(__INDESTEXTURE)), engine(_g) {
    double		x,y;
    const glm::vec4&	hitbox = parent->getHitBox();
    parent->getPosition(x, y);
    cube->setPosition(x*3, y*3, object3d::cubeVertex::Up);
    cube->scale(glm::vec3(3,3,3));
    engine->addObject(cube);
  }
  indestructibleDisplay::~indestructibleDisplay() { delete cube; }

  bookshelfDisplay::bookshelfDisplay(Entity::GameObject* _p, Engine::Graphic* _g)
    : Component::abstract(_p), cube(new object3d::cubeVertex(__BOOKSHELFTEXTURE)), engine(_g) {
    double		x,y;
    const glm::vec4&	hitbox = parent->getHitBox();
    parent->getPosition(x, y);
    cube->scale(glm::vec3(2.5,2.5,2.5));
    cube->setPosition(x*3, y*3, object3d::cubeVertex::Up);
    engine->addObject(cube);
    attachCallback(Event::Info::disableCollision,
		   new Event::FixedCallback([this](Event::Data&) {
		       std::cout << engine << std::endl;
		       engine->subObject(cube);
		     }));
  }
  bookshelfDisplay::~bookshelfDisplay() { delete cube; }

  playerDisplay::playerDisplay(Entity::GameObject* _p, Engine::Graphic* _g)
    : Component::abstract(_p), cube(new object3d::cubeVertex(__INDESTEXTURE)), engine(_g) {
    double		_x,_y;
    const glm::vec4&	hitbox = parent->getHitBox();
    parent->getPosition(_x, _y);
    _x += hitbox[0];
    _y += hitbox[2];
    cube->setPosition(_x*3, _y*3, object3d::cubeVertex::Up);
    cube->scale(glm::vec3(2,2,2));
    x = _x;
    y = _y;
    engine->addObject(cube);
    attachCallback(Event::Info::Clock,
		   new Event::FixedCallback([this](Event::Data&) {
		       double		_x,_y;
		       parent->getPosition(_x, _y);
		       cube->setPosition((_x-x)*3, (_y-y)*3,
					 object3d::cubeVertex::NONE);
		       x = _x;
		       y = _y;
		     }));
  }
  playerDisplay::~playerDisplay() { delete cube; }
};
