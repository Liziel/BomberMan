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

    class OnlineDelay : public Engine::Game::Delay{
    private:
      const Socket::Select&	select;
    public:
      OnlineDelay(const Socket&);
      void	operator()(unsigned int delay);
    };

    /* Game Part access */
  private:
    Component::Pool*		_datapool;
    Event::Dispatcher*		_dispatcher;
    Engine::Graphic*		_grEngine;
    
    /* Ctor && Dtor */
  public:
    GameEngine(Event::Dispatcher*, Engine::Graphic*, Component::Pool*);
    ~GameEngine();
    
  public:
    Engine::Game::Delay*	delayAllocator();
    bool			refresh();
  public:
    Component::GameObject*	allocate(/* by type and enum specifier*/);
  };
};

#endif
