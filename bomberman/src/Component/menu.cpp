#include "menu.hh"
#include "Entity.hh"

namespace Component{
  Menu::Menu(Entity::GameObject* _p, Engine::Graphic* g) 
    : Component::abstract(_p), _graphic(g) {
    _validBackground = false;
    std::cout << "oui j'ai été sauté par ton père!...." << std::endl;
    attachCallback(Event::Info::Keyboard,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::Keyboard* event =
			 reinterpret_cast<Event::Type::Keyboard*>(&e);
		       std::cout << "keyevent" << std::endl;
                       if (event->state && event->key == 0)
			 moveFocus(1);
                       else if (event->state && event->key == 1)
			 moveFocus(-1);
		       //move to each menu
		       //else if (event->state && event->key == 4)
		     }));
  }

  Menu::Menu(Entity::GameObject* _p, Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture)
    : Menu(_p, g) {
    _sizeX = sizeX;
    _sizeY = sizeY;
    _posX = posX;
    _posY = posY;
    _texture = texture;
    _validBackground = true;
    _gp = NULL;
    std::cout << "...... et par ta mère!" << std::endl;
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

  void Menu::moveFocus(int i)
  {
    std::cout << "moveFocus" << std::endl;
    for (auto it = _buttons.cbegin(); it != _buttons.cend(); ++it)
      if ((*it)->_isFocus)
	{
	  (*it)->onLooseFocus();
	  if (it == _buttons.cend())
	    (*(_buttons.cbegin()))->onFocus();
	  else if (it == _buttons.cbegin())
	    (*(_buttons.cend()))->onFocus();
	  else
	    ((*it) + 1)->onFocus();
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
    std::cout << "onFocus" << std::endl;
    _isFocus = true;
    if (_gp)
      _graphic->subHudObject(_gp);
    _gp = new object3d::planVertex(_textureFocus.c_str(), _sizeX, _sizeY, _posX, _posY);
    _graphic->addHudObject(_gp);
  }

  void Button::onLooseFocus()
  {
    _isFocus = false;
    if (_gp)
      _graphic->subHudObject(_gp);
    _gp = new object3d::planVertex(_textureFocus.c_str(), _sizeX, _sizeY, _posX, _posY);
    _graphic->addHudObject(_gp);
  }
}
