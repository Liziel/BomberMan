#ifndef __GAMEENGINE_H__
# define __GAMEENGINE_H__

# include "DataPool.hh"

/* Component and Event query are so powerfull....
 so what the goal about having a game Engine????? (maybe a dictionnarie about compo...?)*/
/*
 *So it will:
 * switching beetwen each mode (by enabling/disabling)
 * storing Component::*::Allocator
 */
class GameEngine{
  /* Game Part access */
private:
  Component::Pool*		_datapool;
  Event::Dispatcher*		_dispatcher;
  GraphicEngine*		_grEngine;

  /* Ctor && Dtor */
public:
  GameEngine(DataPool* data);
  ~GameEngine();

public:
  Component::GameObject*	allocate(/* by type and enum specifier*/);
};

#endif
