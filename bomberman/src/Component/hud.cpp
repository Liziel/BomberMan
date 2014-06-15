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
    HudElement *life;
    HudElement *mana;
    HudElement *inv;
    HudElement *mute;
    HudElement *lock;

    life = new HudElement(g, WINDOW_X / 2 / nbPlayer * , 100, (WINDOW_X / 2 / nbPlayer) * idPlayer, WINDOW_Y - 200, "img/lifeBar.tga");
    mana = new HudElement(g, WINDOW_X / 10 / nbPlayer, 100, (WINDOW_X / 2 / nbPlayer) * idPlayer, WINDOW_Y - 100, "img/manaBar.tga");
    attachCallback(Event::Info::/* mutechange*/,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::/**/ * event =
			 reinterpret_cast<Event::Type:/**/*>(&e);
		       if (/*active*/)
			 mute = new HudElement(g, 50, 50, (WINDOW_X / 2 / nbPlayer) * idPlayer - 50, WINDOW_Y - 250, "img/mute.tga");
		       else
			 delete(mute);
		     }));
    attachCallback(Event::Info::/* invinciblechange*/,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::/**/ * event =
			 reinterpret_cast<Event::Type:/**/*>(&e);
		       if (/*active*/)
			 inv = new HudElement(g, 50, 50, (WINDOW_X / 2 / nbPlayer) * idPlayer - 150, WINDOW_Y - 250, "img/invincible.tga");
		       else
			 delete(inv);
		     }));
    attachCallback(Event::Info::/* lifechange*/,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::/**/ * event =
			 reinterpret_cast<Event::Type:/**/*>(&e);
		       life->resize(g, (WINDOW_X / 2 / nbPlayer) * (currentLife / 100), 100, (WINDOW_X / 2 / nbPlayer) * idPlayer, WINDOW_Y - 200, "img/lifeBar.tga");
		     }));
    attachCallback(Event::Info::/* manachange*/,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::/**/ * event =
			 reinterpret_cast<Event::Type:/**/*>(&e);
		       mana->resize(g,  (WINDOW_X / 2 / nbPlayer) * (nbBomb * 0.2), 100, (WINDOW_X / 2 / nbPlayer) * idPlayer, WINDOW_Y - 200, "img/manaBar.tga");
		     }));
    attachCallback(Event::Info::/* lockchange*/,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::/**/ * event =
			 reinterpret_cast<Event::Type:/**/*>(&e);
		       if (/*active*/)
			 lock = new HudElement(g, 20 , 100, (WINDOW_X / 2 / nbPlayer) * (nbBomb * 0.2) + (WINDOW_X / 2 / nbPlayer) * idPlayer, WINDOW_Y - 200, "img/lock.tga");
		       else
			 delete(lock);
		     }));

    attachCallback(Event::Info::/* element in bomb*/,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::/**/ * event =
			 reinterpret_cast<Event::Type:/**/*>(&e);
		       if (typeElem == 0)
			 inv = new HudElement(g, 100, 100, (WINDOW_X / nbPlayer) * idPlayer + 100 * idElem, WINDOW_Y - 200, "img/life.tga");
		       else if (typeElem == 0)
			 inv = new HudElement(g, 100, 100, (WINDOW_X / nbPlayer) * idPlayer + 100 * idElem, WINDOW_Y - 200, "img/ice.tga");
		       else if (typeElem == 0)
			 inv = new HudElement(g, 100, 100, (WINDOW_X / nbPlayer) * idPlayer + 100 * idElem, WINDOW_Y - 200, "img/fire.tga");
		       else if (typeElem == 0)
			 inv = new HudElement(g, 100, 100, (WINDOW_X / nbPlayer) * idPlayer + 100 * idElem, WINDOW_Y - 200, "img/glyphe.tga");
		       else if (typeElem == 0)
			 inv = new HudElement(g, 100, 100, (WINDOW_X / nbPlayer) * idPlayer + 100 * idElem, WINDOW_Y - 200, "img/light.tga");
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
