#ifndef __MANAGER_H__
# define __MANAGER_H__

# include "Event.hpp"
# include "DataPool.hh"
# include "GameEngine.hh"

namespace Engine{
  class Manager{
  private:
    Entity::Pool*	data;
    Event::Dispatcher*	dispatcher;
    Engine::Graphic*	graphic;
    Engine::Game*	game;

  public:
    Manager(ArgsParsing&);
    ~Manager();

  public:
    void	start(void);
  };
};

#endif
