#include "menuPrincipal.hh"

namespace Component {

  MenuPrincipal::MenuPrincipal(Entity::GameObject* _p, Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture) : Menu(_p, g, sizeX, sizeY, posX, posY, texture)
  {
    std::cout << "menu principal" << std::endl;
    addButton(g, 400, 100, WINDOW_X / 2 - 200, 100, "img/buttons/play.tga", "img/buttons/play_pressed.tga", true);
    addButton(g, 400, 100, WINDOW_X / 2 - 200, 300, "img/buttons/help.tga", "img/buttons/help_pressed.tga", false);
    addButton(g, 400, 100, WINDOW_X / 2 - 200, 500, "img/buttons/exit.tga", "img/buttons/exit_pressed.tga", false);
    draw();
  }
  
  MenuPrincipal::~MenuPrincipal()
  {
    for (auto button : _buttons)
      _graphic->subHudObject(_gp);
  }
}
