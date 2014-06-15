#include "hud.hh"
#include "Entity.hh"

namespace Component{
  Hud::Hud(Entity::GameObject* _p, Engine::Graphic* g) 
    : Component::abstract(_p), _graphic(g) {
    _validBackground = false;
    attachCallback(Event::Info::Keyboard,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::Keyboard* event =
			 reinterpret_cast<Event::Type::Keyboard*>(&e);
		       if (event->state)
			 std::cout << "key = " << event->key << std::endl;
                       if (event->state && event->key == 0)
			 {
			   std::cout << "haut" << std::endl;
			 }
                       else if (event->state && event->key == 1)
			 {
			   std::cout << "bas" << std::endl;
			 }
		     }));
  }
  
  Hud::Hud(Entity::GameObject* _p, Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture)
    : Hud(_p, g) {
    _sizeX = sizeX;
    _sizeY = sizeY;
    _posX = posX;
    _posY = posY;
    _texture = texture;
    _validBackground = true;
    _gp = NULL;
  }
  
  Hud::~Hud()
  {
    if (_gp)
      _graphic->subHudObject(_gp);
    for (auto elem : _elems)
      {
    	delete (elem);
      }
  }

  void Hud::addElement(Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture){
    _elems.push_back(new Component::HudElement(g, sizeX, sizeY, posX, posY, texture));
  }
  
  void Hud::draw()
  {
    if (_validBackground)
      {
	_gp = new object3d::planVertex(_texture, _sizeX, _sizeY, _posX, _sizeY);
	_graphic->addHudObject(_gp);
      }
    for (auto button : _elems)
      {
	if (!(button->_gp))
	button->_gp = new object3d::planVertex(button->_texture, button->_sizeX, button->_sizeY, button->_posX, button->_posY);
	_graphic->addHudObject(button->_gp);
      }
  }

  HudElement::HudElement(Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture){
    _sizeX = sizeX;
    _sizeY = sizeY;
    _posX = posX;
    _posY = posY;
    _texture = texture;
    _gp = NULL;
    _graphic = g;
  }

  HudElement::~HudElement(){
    if (_gp)
      _graphic->subHudObject(_gp);
  }

  void HudElement::resize(int sizeX, int sizeY, int posX, int posY, const std::string& texture)
  {
    if (_gp)
      _graphic->subHudObject(_gp);
    _gp = new object3d::planVertex(texture, sizeX, sizeY, posX, posY);
    _graphic->addHudObject(_gp);
  }
}
