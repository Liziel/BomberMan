#ifndef __HUD_H__
# define __HUD_H__

# include "Component.hh"
# include "GraphicEngine.hh"
# include "planVertex.hh"
# include "Event.hpp"
# include "EventType.hh"

namespace Component{
  class HudElement {
  public:
    std::string _texture;
    int _sizeX;
    int _sizeY;
    int _posX;
    int _posY;
    Engine::Graphic* _graphic;
    object3d::AObject* _gp;
    HudElement(Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture);
    ~HudElement();
    void resize(int sizeX, int sizeY, int posX, int posY, const std::string& texture);
  };

  class Hud : public Component::abstract{
  protected:
    bool _validBackground;
    std::string _texture;
    int _sizeX;
    int _sizeY;
    int _posX;
    int _posY;
    std::list<HudElement*> _elems;
    object3d::AObject* _gp;
    Engine::Graphic* _graphic;
  public:
    Hud(Entity::GameObject* _p, Engine::Graphic* g);
    Hud(Entity::GameObject* _p, Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture);
    ~Hud();
    void addElement(Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture);
    void draw();
  public:
    std::string serialization() { return (""); }
    void	setBySerial(const Tokenizer&) {}
  };
};

namespace Event{
  namespace Type{
# ifndef __ARENA_H__
#  ifndef __KEYBOARD_H__
    struct Keyboard : Event::Data{
      Keyboard(int k, bool s)
	: Event::Data(Event::Info::Keyboard, sizeof(struct Keyboard), false),
	  key(k), state(s) {}
      int key;
      bool state;
    };
#  endif
# endif
  };
};

#endif
