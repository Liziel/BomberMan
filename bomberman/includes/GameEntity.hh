#ifndef __GAMEENTITY_H__
# define __GAMEENTITY_H__

#include "Entity.hh"

namespace Entity{
  /* ##### Player ##### */
  class Player : public Entity::GameObject{
  public:
    Player(Event::Dispatcher* Dispatch);
  };
  class Bloc : public Entity::GameObject{};
  class Bomb : public Entity::GameObject{};
  class AI : public Entity::GameObject{};
};

#endif
