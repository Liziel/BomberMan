#ifndef __MENUPRINCIPAL_H__
#define __MENUPRINCIPAL_H__

#include "menu.hh"
#include "Event.hpp"

namespace Component {
  class MenuPrincipal : public Component::Menu {
  public:
    MenuPrincipal(Entity::GameObject* _p, Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture);
    ~MenuPrincipal();
  };
};

namespace Event {
  namespace Type {
    struct menuInstanciation : Event::Data {
      menuInstanciation(int _t)
      : Event::Data(Event::Info::menuInstanciation, sizeof(struct menuInstanciation), false), _type(_t) {}
      int _type;
    };
  };
};
#endif
