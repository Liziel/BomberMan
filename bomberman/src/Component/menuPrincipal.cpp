#include "menuPrincipal.hh"

namespace Component {

  MenuPrincipal::MenuPrincipal(Entity::GameObject* _p, Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture) : Menu(_p, g, sizeX, sizeY, posX, posY)
  {
    addButton(400, 150, WINDOW_X / 2 - 200, 100, "buttons/play.tga", true);
    draw();
  }
  
  MenuPrincipal::~MenuPrincipal()
  {

  }
}
