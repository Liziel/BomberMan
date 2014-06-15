#include "hud.hh"
#include "Entity.hh"

/*create and set var nbPlayer to compile*/ 
/*create and set var idPlayer to compile*/ 
/*create and set var currentLife to compile*/ 
/*create and set var idElem to compile (0, 1, 2)*/ 
/*create and set var typeElem to compile(0, 1, 2, 3, 4)*/ 

namespace Component{
  Hud::Hud(Entity::GameObject* _p, Engine::Graphic* g) 
    : Component::abstract(_p), _graphic(g) {
    _validBackground = false;
    mute = NULL;
    inv = NULL;
    nbBomb = 0;
    nblock = 1;

    life = new HudElement(_graphic, (WINDOW_X / 2) / nbPlayer , 100, ((WINDOW_X / 2) / nbPlayer) * idPlayer, WINDOW_Y - 200, "img/lifeBar.tga");
    mana = new HudElement(_graphic, (WINDOW_X / 10) / nbPlayer , 100, ((WINDOW_X / 2) / nbPlayer) * idPlayer, WINDOW_Y - 100, "img/manaBar.tga");
    attachCallback(Event::Info::Clock,
		   new Event::FixedCallback([this] (Event::Data&) {
		       invi--;
		       if (!invi && inv)
			 delete (inv);		       
		     }));

    attachCallback(Event::Info::changeMute,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::changeMute * event =
			 reinterpret_cast<Event::Type::changeMute*>(&e);
		       if (event->mute)
			 mute = new HudElement(_graphic, 50, 50, (WINDOW_X / 2 / nbPlayer) * idPlayer - 50, WINDOW_Y - 250, "img/mute.tga");
		       else
			 delete(mute);
		     }));

    attachCallback(Event::Info::Immunity,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::Immunity * event =
			 reinterpret_cast<Event::Type:Immunity*>(&e);
			 inv = new HudElement(_graphic, 50, 50, (WINDOW_X / 2 / nbPlayer) * idPlayer - 150, WINDOW_Y - 250, "img/invincible.tga");
			 invi = event->time;
		     }));

    attachCallback(Event::Info::lifeActualize,
		   new Event::FixedCallback([this] (Event::Data&) {
		       Event::Type::lifeActualize * event =
			 reinterpret_cast<Event::Type:lifeActualize *>(&e);
		       life->resize(_graphic, (WINDOW_X / 2 / nbPlayer) * (currentLife / 100), 100, (WINDOW_X / 2 / nbPlayer) * idPlayer, WINDOW_Y - 200, "img/lifeBar.tga");
		     }));
    attachCallback(Event::Info::bombReloaded,
		   new Event::FixedCallback([this] (Event::Data&) {
		       nbBomb += 1;
		       mana->resize(_graphic,  (WINDOW_X / 2 / nbPlayer) * (nbBomb * 0.2), 100, (WINDOW_X / 2 / nbPlayer) * idPlayer, WINDOW_Y - 200, "img/manaBar.tga");
		     }));

    attachCallback(Event::Info::bombReleased,
		   new Event::FixedCallback([this] (Event::Data&) {
		       nbBomb -= 1;
		       mana->resize(_graphic,  (WINDOW_X / 2 / nbPlayer) * (nbBomb * 0.2), 100, (WINDOW_X / 2 / nbPlayer) * idPlayer, WINDOW_Y - 200, "img/manaBar.tga");
		     }));

    attachCallback(Event::Info::IncreaseBombStack,
		   new Event::FixedCallback([this] (Event::Data&) {
		       nblock += 1;
		       lock = new HudElement(_graphic, 20 , 100, (WINDOW_X / 2 / nbPlayer) * (nblock * 0.2) + (WINDOW_X / 2 / nbPlayer) * idPlayer, WINDOW_Y - 200, "img/lock.tga");
		     }));

    attachCallback(Event::Info::addElement,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::addElement * event =
			 reinterpret_cast<Event::Type::addElement*>(&e);
		       int typeElem = event->element;
		       if (typeElem == 0)
			 elem[idElem] = new HudElement(_graphic, 100, 100, (WINDOW_X / nbPlayer) * idPlayer + 100 * idElem, WINDOW_Y - 200, "img/life.tga");
		       else if (typeElem == 0)
			 elem[idElem] = new HudElement(_graphic, 100, 100, (WINDOW_X / nbPlayer) * idPlayer + 100 * idElem, WINDOW_Y - 200, "img/ice.tga");
		       else if (typeElem == 0)
			 elem[idElem] = new HudElement(_graphic, 100, 100, (WINDOW_X / nbPlayer) * idPlayer + 100 * idElem, WINDOW_Y - 200, "img/fire.tga");
		       else if (typeElem == 0)
			 elem[idElem] = new HudElement(_graphic, 100, 100, (WINDOW_X / nbPlayer) * idPlayer + 100 * idElem, WINDOW_Y - 200, "img/glyphe.tga");
		       else if (typeElem == 0)
			 elem[idElem] = new HudElement(_graphic, 100, 100, (WINDOW_X / nbPlayer) * idPlayer + 100 * idElem, WINDOW_Y - 200, "img/light.tga");
		     }));

    attachCallback(Event::Info::flushElement,
		   new Event::FixedCallback([this] (Event::Data&) {
		       
		     }));

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
