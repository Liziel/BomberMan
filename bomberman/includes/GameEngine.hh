#ifndef __GAMEENGINE_H__
# define __GAMEENGINE_H__

# include "Entity.hh"
# include "Component.hh"
# include "Event.hpp"
# include "GraphicEngine.hh"
# include "GameEngine.hh"

#include "phisix.hh"
#include "effects.hh"
#include "Arena.hh"
#include "collider.hh"
#include "health.hh"
#include "plantBomb.hh"
#include "Bonus.hh"

namespace Engine{
  class Game{
    /* Delay Interface & Online Delay */
  public:

    class Delay{
    public:
      virtual void	operator()(unsigned int delay) = 0;
    };

  private:

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

    /* Ctor && Dtor */
  public:
    Game(Event::Dispatcher*, Engine::Graphic*);
    ~Game();
    
  public:
    Entity::GameObject*	allocate(/* by type and enum specifier*/);
  };
};

#endif
