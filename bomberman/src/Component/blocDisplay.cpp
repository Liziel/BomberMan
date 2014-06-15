#include "ziggsAnimated.hpp"
#include "blocDisplay.hh"

namespace Component{
  groundDisplay::groundDisplay(Entity::GameObject* _p, Engine::Graphic* _g)
    : Component::abstract(_p),
      cube(new object3d::cubeVertex(__GROUNDTEXTURE)),
      glyphed(new object3d::cubeVertex(__GLYPHEDTEXTURE)),
      _glyphed(false),
      cubeFire(new object3d::cubeVertex(__GROUNDFIRETEXTURE)),
      cubeIce(new object3d::cubeVertex(__GROUNDICETEXTURE)),
      cubeLight(new object3d::cubeVertex(__GROUNDLIGHTTEXTURE)),
      cubeHealth(new object3d::cubeVertex(__GROUNDHEALTHTEXTURE)),
      effects(-1), engine(_g) {
    double		x,y;
    const glm::vec4&	hitbox = parent->getHitBox();
    parent->getPosition(x, y);
    x+=hitbox[0];
    y+=hitbox[2];
    cube->setPosition(x*3, y*3, object3d::cubeVertex::Ground);
    cube->scale(glm::vec3(3,3,3));
    cubeFire->setPosition(x*3, y*3, object3d::cubeVertex::Ground);
    cubeFire->scale(glm::vec3(3,3,3));
    cubeIce->setPosition(x*3, y*3, object3d::cubeVertex::Ground);
    cubeIce->scale(glm::vec3(3,3,3));
    cubeLight->setPosition(x*3, y*3, object3d::cubeVertex::Ground);
    cubeLight->scale(glm::vec3(3,3,3));
    cubeHealth->setPosition(x*3, y*3, object3d::cubeVertex::Ground);
    cubeHealth->scale(glm::vec3(3,3,3));
    glyphed->setPosition(x*3, y*3, object3d::cubeVertex::Ground);
    glyphed->scale(glm::vec3(3,3,3));
    engine->addObject(cube);
    attachCallback(Event::Info::Clock,
		   new Event::FixedCallback([this] (Event::Data&) {
		       if (effects > 0) {
			 effects--;
			 return ;
		       } else if (!effects) {
			 engine->subObject(cubeEffects);
			 if (_glyphed)
			   engine->addObject(glyphed);
			 else
			   engine->addObject(cube);
			 effects = -1;
		       }
		     }));

    attachCallback(Event::Info::LifeExplosion,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::LifeExplosion* event =
			 reinterpret_cast<Event::Type::LifeExplosion*>(&e);
		       double x;
		       double y;

		       parent->getPosition(x, y);
		       if (!Component::matchPosition(event->x, event->y, x, y))
			 return ;
		       if (effects > 0)
			 return ;
		       cubeEffects = cubeHealth;
		       engine->addObject(cubeEffects);
		       engine->subObject(cube);
		       effects = EFFECTS_TIME;
		     }));
    attachCallback(Event::Info::FireExplosion,
		   new Event::FixedCallback([this] (Event::Data&e) {
		       Event::Type::FireExplosion* event =
			 reinterpret_cast<Event::Type::FireExplosion*>(&e);
		       double x;
		       double y;

		       parent->getPosition(x, y);
		       if (!Component::matchPosition(event->x, event->y, x, y))
			 return ;
		       if (effects > 0)
			 return ;
		       cubeEffects = cubeFire;
		       engine->addObject(cubeEffects);
		       engine->subObject(cube);
		       effects = EFFECTS_TIME;
		     }));
    attachCallback(Event::Info::IceExplosion,
		   new Event::FixedCallback([this] (Event::Data&e) {
		       Event::Type::IceExplosion* event =
			 reinterpret_cast<Event::Type::IceExplosion*>(&e);
		       double x;
		       double y;

		       parent->getPosition(x, y);
		       if (!Component::matchPosition(event->x, event->y, x, y))
			 return ;
		       if (effects > 0)
			 return ;
		       cubeEffects = cubeIce;
		       engine->addObject(cubeEffects);
		       engine->subObject(cube);
		       effects = EFFECTS_TIME;
		     }));
    attachCallback(Event::Info::ElectricityExplosion,
		   new Event::FixedCallback([this] (Event::Data&e) {
		       Event::Type::ElectricityExplosion* event =
			 reinterpret_cast<Event::Type::ElectricityExplosion*>(&e);
		       double x;
		       double y;

		       parent->getPosition(x, y);
		       if (!Component::matchPosition(event->x, event->y, x, y))
			 return ;
		       if (effects > 0)
			 return ;
		       cubeEffects = cubeLight;
		       engine->addObject(cubeEffects);
		       engine->subObject(cube);
		       effects = EFFECTS_TIME;
		     }));

    attachCallback(Event::Info::SocketGlyph,
		   new Event::FixedCallback([this, x, y] (Event::Data&) {
		       std::cout << "glyphedLocation{"<< x <<"}{"<< y <<"}" << std::endl;
		       _glyphed = false;
		       engine->subObject(cube);
		       engine->addObject(glyphed);
		     }));
    attachCallback(Event::Info::extinctGlyph,
		   new Event::FixedCallback([this] (Event::Data&) {
		       _glyphed = false;
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
    ziggs->translate(glm::vec3(_x*3, _y*3, -4));
    ziggs->rotate(glm::vec3(-9, 0, 0), 10);
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
		       ziggs->setAnimation("run");
		       if (_direction[Component::Phisix::Vector::Up]
			   && _direction[Component::Phisix::Vector::Right])
			 ziggs->rotate(glm::vec3(9, 13.5, 18), 10);
		       else if (_direction[Component::Phisix::Vector::Up]
			   && _direction[Component::Phisix::Vector::Left])
			 ziggs->rotate(glm::vec3(9, -13.5, 18), 10);
		       else if (_direction[Component::Phisix::Vector::Right]
			   && _direction[Component::Phisix::Vector::Down])
			 ziggs->rotate(glm::vec3(-9, 13.5, 0), 10);
		       else if (_direction[Component::Phisix::Vector::Left]
			   && _direction[Component::Phisix::Vector::Down])
			 ziggs->rotate(glm::vec3(-9, -13.5, 0), 10);
		       else if (_direction[Component::Phisix::Vector::Up])
			 ziggs->rotate(glm::vec3(-9, 0, 0), 10);
		       else if (_direction[Component::Phisix::Vector::Right])
			 ziggs->rotate(glm::vec3(0, 9,-9.f), 10);
		       else if (_direction[Component::Phisix::Vector::Left])
			 ziggs->rotate(glm::vec3(-9, -9, 0), 10);
		       else if (_direction[Component::Phisix::Vector::Down])
			 ziggs->rotate(glm::vec3(-9, 18, 0), 10);
		       else
			 ziggs->setAnimation("stop");
		     }));
  }
  playerDisplay::~playerDisplay() { engine->subObject(ziggs); delete ziggs; }

  bonusDisplay::bonusDisplay(Entity::GameObject* _p, Engine::Graphic* _g)
    : Component::abstract(_p), book(new object3d::bookAnimated()), engine(_g) {
    double		x,y;
    const glm::vec4&	hitbox = parent->getHitBox();
    parent->getPosition(x, y);
    x += hitbox[0];
    y += hitbox[2];
    book->translate(glm::vec3(x*3, y*3, -4));
    book->scale(glm::vec3(0.7f));
    book->rotate(glm::vec3(0,-9,9),10);
    book->setAnimation("run");
    attachCallback(Event::Info::LootBonus,
		   new Event::FixedCallback([this](Event::Data&) {
		       engine->addObject(book);
		     }));
    attachCallback(Event::Info::TakeBonus,
		   new Event::FixedCallback([this](Event::Data& e) {
		       Event::Type::TakeBonus* event=
			 reinterpret_cast<Event::Type::TakeBonus*>(&e);
		       double x,y;
		       parent->getPosition(x,y);
			     std::cout << "bonus position["<< event->x <<"]["<< event->y <<"], receiver["<< x <<"]["<< y <<"]" << std::endl;
		       if (Component::matchPosition(x,y,event->x, event->y))
			 engine->subObject(book);
		     }));
  }
  bonusDisplay::~bonusDisplay() { delete book; } 
  bombDisplay::bombDisplay(Entity::GameObject* _p, Engine::Graphic* _g)
    : Component::abstract(_p), bomb(NULL), engine(_g) {
  }
  void	bombDisplay::setBySerial(const Tokenizer& t) {
    double		x,y;
    const glm::vec4&	hitbox = parent->getHitBox();
    parent->getPosition(x, y);
    if (t.get<int>(1) == 0)
      bomb = new object3d::bombGlyph();
    if (t.get<int>(1) == 1)
      bomb = new object3d::bombFeu();
    if (t.get<int>(1) == 2)
      bomb = new object3d::bombGlace();
    if (t.get<int>(1) == 3)
      bomb = new object3d::bombThunder();
    if (t.get<int>(1) == 4)
      bomb = new object3d::bombHealth();
    x += hitbox[0];
    y += hitbox[2];
    bomb->translate(glm::vec3(x*3, y*3, -4));
    bomb->scale(glm::vec3(0.7f));
    bomb->rotate(glm::vec3(0,-9,9),10);
    bomb->setAnimation("run");
    engine->addObject(bomb);
  }

  bombDisplay::~bombDisplay() { engine->subObject(bomb); delete bomb; }
};
