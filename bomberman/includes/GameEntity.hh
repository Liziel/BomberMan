#ifndef __GAMEENTITY_H__
# define __GAMEENTITY_H__

#include "Entity.hh"

namespace Entity{
  /* ##### Player ##### */
  class Player : public Entity::GameObject{
  private:
    glm::vec4	hitbox;
  public:
    Player(Event::Dispatcher* _d)
      : Entity::GameObject(_d, Entity::game), hitbox(-0.3,0.3,-0.3,-0.3) {}
    int	getLifeAmount(void) { return (100); }
    std::string getName() { return ("Player"); }
    const glm::vec4& getHitBox() { return (hitbox); }
  };

  class Bomb : public Entity::GameObject{
  private:
    glm::vec4	hitbox;
  public:
    Bomb(Event::Dispatcher* _d)
      : Entity::GameObject(_d, Entity::game), hitbox(-0.5,0.5,-0.5,0.5) {}
    std::string getName() { return ("Bomb"); }
    const glm::vec4& getHitBox() { return (hitbox); }
  };

  class Bloc : public Entity::GameObject{
  private:
    glm::vec4	hitbox;
  public:
    Bloc(Event::Dispatcher* _d)
      : Entity::GameObject(_d, Entity::game), hitbox(-0.5,0.5,-1.0,0.5) {}
    std::string getName() { return ("Bloc"); }
    const glm::vec4& getHitBox() { return (hitbox); }
  };
  class AI : public Entity::GameObject{};

  class Menu : public Entity::GameObject{
  private:
    glm::vec4	hitbox;
  public:
    Menu(Event::Dispatcher* _d)
      : Entity::GameObject(_d, Entity::menu), hitbox(-0.5,0.5,-0.5,0.5) {}
    std::string getName() { return ("Menu"); }
    const glm::vec4& getHitBox() { return (hitbox); }
  };

};

#endif
