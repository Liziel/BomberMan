
#ifndef __MENUPRINCIPAL_H__
#define __MENUPRINCIPAL_H__

#include "menu.hh"

namespace Component {
  
  class MenuPrincipal : public Menu {
    MenuPrincipal(Entity::GameObject* _p, Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture);
    ~MenuPrincipal();
  };
}

#endif
