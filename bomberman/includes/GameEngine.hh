#ifndef __GAMEENGINE_H__
# define __GAMEENGINE_H__

# include "DataPool.hh"

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
    Entity::Pool*		_datapool;
    Event::Dispatcher*		_dispatcher;
    Engine::Graphic*		_grEngine;
    
    /* Ctor && Dtor */
  public:
    GameEngine(Event::Dispatcher*, Engine::Graphic*, Entity::Pool*);
    ~GameEngine();
    
  public:
    Engine::Game::Delay*	delayAllocator();
    bool			refresh();
  public:
    Entity::GameObject*	allocate(/* by type and enum specifier*/);
  };
};

#endif
