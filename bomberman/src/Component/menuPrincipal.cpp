#include "menuPrincipal.hh"

namespace Component {

  MenuPrincipal::MenuPrincipal(Entity::GameObject* _p, Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture) : Menu(_p, g, sizeX, sizeY, posX, posY, texture)
  {
    addButton(g, 400, 100, WINDOW_X / 2 - 200, 100, "img/buttons/play_ia.tga", "img/buttons/play_ia_pressed.tga", true);
    addButton(g, 400, 100, WINDOW_X / 2 - 200, 300, "img/buttons/play_vs.tga", "img/buttons/play_vs_pressed.tga", false);
    addButton(g, 400, 100, WINDOW_X / 2 - 200, 500, "img/buttons/exit.tga", "img/buttons/exit_pressed.tga", false);
    draw();
  }
  
  MenuPrincipal::~MenuPrincipal()
  {
    _graphic->subHudObject(_gp);
  }
}
