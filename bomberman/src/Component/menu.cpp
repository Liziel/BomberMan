#include "menu.hh"

namespace Component{
  Menu::Menu(Entity::GameObject* _p, Engine::Graphic* g)  : Component::abstract(_p)
  {
    _validBackground = false;
    _graphic = g;
  }

  Menu::Menu(Entity::GameObject* _p, Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture)  : Component::abstract(_p)
  {
    _sizeX = sizeX;
    _sizeY = sizeY;
    _posX = posX;
    _posY = posY;
    _texture = texture;
    _validBackground = true;
    _graphic = g;
    _gp = NULL;
  }
  
  Menu::~Menu()
  {
    if (_gp)
      _graphic->subHudObject(_gp);
    for (auto button : _buttons)
      {
	delete (button);
      }
  }

  void Menu::addButton(Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture, const std::string& textureFocus, bool isFocus){
    _buttons.push_back(new Component::Button(g, sizeX, sizeY, posX, posY, texture, textureFocus, isFocus));
  }
  
  void Menu::draw()
  {
    if (_validBackground)
      {
	_gp = new object3d::planVertex(_texture.c_str(), _sizeX, _sizeY, _posX, _sizeY);
	_graphic->addHudObject(_gp);
      }
    for (auto button : _buttons)
      {
	button->_gp = new object3d::planVertex(button->_texture.c_str(), button->_sizeX, button->_sizeY, button->_posX, button->_posY);
	_graphic->addHudObject(button->_gp);
      }
  }

  Button::Button(Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture, const std::string& textureFocus, bool isFocus){
    _sizeX = sizeX;
    _sizeY = sizeY;
    _posX = posX;
    _posY = posY;
    _texture = texture;
    _textureFocus = textureFocus;
    _isFocus = isFocus;
    _gp = NULL;
    _graphic = g;
  }

  Button::~Button(){
    if (_gp)
      _graphic->subHudObject(_gp);
  }

  void Button::onFocus()
  {
    if (_gp)
      _graphic->subHudObject(_gp);
    _gp = new object3d::planVertex(_textureFocus.c_str(), _sizeX, _sizeY, _posX, _posY);
    _graphic->addHudObject(_gp);
  }

  void Button::onLooseFocus()
  {
    if (_gp)
      _graphic->subHudObject(_gp);
    _gp = new object3d::planVertex(_textureFocus.c_str(), _sizeX, _sizeY, _posX, _posY);
    _graphic->addHudObject(_gp);
  }
}
