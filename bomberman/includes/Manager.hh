#ifndef __MANAGER_H__
# define __MANAGER_H__

# include "Event.hpp"
# include "GameEngine.hh"

namespace Engine{
  class Manager{
  private:
    Event::Dispatcher*	dispatcher;
    Engine::Graphic*	graphic;
    Engine::Game*	game;

  public:
    Manager();
    ~Manager();

  public:
    void	start(void);
  };
};

#endif
