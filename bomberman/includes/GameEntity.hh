#ifndef __GAMEENTITY_H__
# define __GAMEENTITY_H__

#include "Entity.hh"

namespace Entity{
  /* ##### Player ##### */
  class Player : public Entity::GameObject{
  public:
    Player(Event::Dispatcher* _d)
      : Entity::GameObject(_d, Entity::game) {}
    int	getLifeAmount(void) { return (100); }
    std::string getName() { return ("Player"); }
  };
  class Bomb : public Entity::GameObject{
  public:
    Bomb(Event::Dispatcher* _d)
      : Entity::GameObject(_d, Entity::game) {}
    std::string getName() { return ("Bomb"); }
  };
  class Bloc : public Entity::GameObject{
  public:
    Bloc(Event::Dispatcher* _d)
      : Entity::GameObject(_d, Entity::game) {}
    std::string getName() { return ("Bloc"); }
  };
  class AI : public Entity::GameObject{};

  class Menu : public Entity::GameObject{
  public:
    Menu(Event::Dispatcher* _d)
      : Entity::GameObject(_d, Entity::menu) {}
    std::string getName() { return ("Menu"); }
  };

};

#endif
