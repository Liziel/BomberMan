#ifndef __GAMEENGINE_H__
# define __GAMEENGINE_H__

# include "Entity.hh"
# include "Component.hh"
# include "Event.hpp"
# include "GraphicEngine.hh"
# include "GameEngine.hh"

#include "blocDisplay.hh"
#include "phisix.hh"
#include "effects.hh"
#include "Arena.hh"
#include "collider.hh"
#include "health.hh"
#include "plantBomb.hh"
#include "Bonus.hh"
#include "Runic.hh"
#include "Explode.hh"
#include "joystick.hh"

namespace Engine{
  class Game{
    /* Game Part access */
  private:
    Event::Dispatcher*		_dispatcher;
    Engine::Graphic*		_grEngine;

  public:
    Component::Factory*		_Cfactory;
    Entity::Factory*		_Efactory;

  public:
    Component::Arena*		arena;
    Component::Collider*	collider;
    Component::Phisix		*phisix;
    Component::JoystickManager	*joystick;

    /* Ctor && Dtor */
  public:
    Game(Event::Dispatcher*, Engine::Graphic*);
    ~Game();

  public:
    void	refresh(void);
  };
};

#endif
