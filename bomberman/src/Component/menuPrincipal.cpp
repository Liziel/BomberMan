#include "menuPrincipal.hh"

namespace Component {

  MenuPrincipal::MenuPrincipal(Entity::GameObject* _p, Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture) : Menu(_p, g, sizeX, sizeY, posX, posY, texture)
  {
    std::cout << "menu principal" << std::endl;
    addButton(g, 400, 100, WINDOW_X / 2 - 200, 100, "img/buttons/play.tga", "buttons/play_pressed.tga", true);
    addButton(g, 400, 100, WINDOW_X / 2 - 200, 300, "img/buttons/help.tga", "buttons/help_pressed.tga", true);
    addButton(g, 400, 100, WINDOW_X / 2 - 200, 500, "img/buttons/exit.tga", "buttons/exit_pressed.tga", true);
    draw();
  }
  
  MenuPrincipal::~MenuPrincipal()
  {

  }
}
