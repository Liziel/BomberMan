#include "ziggsAnimated.hpp"
#include "blocDisplay.hh"

namespace Component{
  groundDisplay::groundDisplay(Entity::GameObject* _p, Engine::Graphic* _g)
    : Component::abstract(_p),
      cube(new object3d::cubeVertex(__GROUNDTEXTURE)),
      glyphed(new object3d::cubeVertex(__GLYPHEDTEXTURE)), engine(_g) {
    double		x,y;
    const glm::vec4&	hitbox = parent->getHitBox();
    parent->getPosition(x, y);
    x+=hitbox[0];
    y+=hitbox[2];
    cube->setPosition(x*3, y*3, object3d::cubeVertex::Ground);
    cube->scale(glm::vec3(3,3,3));
    glyphed->setPosition(x*3, y*3, object3d::cubeVertex::Ground);
    glyphed->scale(glm::vec3(3,3,3));
    engine->addObject(cube);
    attachCallback(Event::Info::SocketGlyph,
		   new Event::FixedCallback([this, x, y] (Event::Data&) {
		       std::cout << "glyphedLocation{"<< x <<"}{"<< y <<"}" << std::endl;
		       engine->subObject(cube);
		       engine->addObject(glyphed);
		     }));
    attachCallback(Event::Info::extinctGlyph,
		   new Event::FixedCallback([this] (Event::Data&) {
		       engine->subObject(glyphed);
		       engine->addObject(cube);
		     }));
  }
  groundDisplay::~groundDisplay() { delete cube; }

  indestructibleDisplay::indestructibleDisplay(Entity::GameObject* _p, Engine::Graphic* _g)
    : Component::abstract(_p), cube(new object3d::cubeVertex(__INDESTEXTURE)), engine(_g) {
    double		x,y;
    const glm::vec4&	hitbox = parent->getHitBox();
    parent->getPosition(x, y);
    x+=hitbox[0];
    y+=hitbox[2];
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
    x+=hitbox[0];
    y+=hitbox[2];
    cube->scale(glm::vec3(2.5,2.5,2.5));
    cube->setPosition(x*3, y*3, object3d::cubeVertex::Up);
    engine->addObject(cube);
    attachCallback(Event::Info::disableCollision,
		   new Event::FixedCallback([this,x,y](Event::Data&) {
		       std::cout <<  x << y << std::endl;
		       engine->subObject(cube);
		     }));
  }
  bookshelfDisplay::~bookshelfDisplay() { delete cube; }

  playerDisplay::playerDisplay(Entity::GameObject* _p, Engine::Graphic* _g)
    : Component::abstract(_p), ziggs(new object3d::ziggsAnimated()),
      engine(_g) {
    double		_x,_y;
    const glm::vec4&	hitbox = parent->getHitBox();
    _direction = {false, false, false, false};
    parent->getPosition(_x, _y);
    _x += hitbox[0];
    _y += hitbox[2];
    x = _x;
    y = _y;
    ziggs->translate(glm::vec3(_x*3, _y*3, -6));
    ziggs->rotate(glm::vec3(0,100.f,-90.f), 1);
    ziggs->scale(glm::vec3(0.8f));
    engine->addObject(ziggs);
    attachCallback(Event::Info::Clock,
		   new Event::FixedCallback([this, hitbox](Event::Data&) {
		       double		_x,_y;
		       parent->getPosition(_x, _y);
		       _x += hitbox[0];
		       _y += hitbox[2];
		       ziggs->translate(glm::vec3((_x-x)*3, (_y-y)*3,0));
		       x = _x;
		       y = _y;
		     }));
    attachCallback(Event::Info::selfMovement,
		   new Event::FixedCallback([this](Event::Data& e) {
		       Event::Type::selfMovement* event = 
			 reinterpret_cast<Event::Type::selfMovement*>(&e);
		       _direction[event->direction] = event->state;
		     }));
  }
  playerDisplay::~playerDisplay() { delete ziggs; }
};
