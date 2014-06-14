#ifndef __MENU_H__
# define __MENU_H__

# include "Component.hh"
# include "GraphicEngine.hh"
# include "planVertex.hh"
# include "Event.hpp"
# include "EventType.hh"

namespace Component{
  class Button {
  public:
    std::string _texture;
    std::string _textureFocus;
    int _sizeX;
    int _sizeY;
    int _posX;
    int _posY;
    bool _isFocus;
    Engine::Graphic* _graphic;
    object3d::AObject* _gp;
    Button(Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture, const std::string& textureFocus, bool _isFocus);
    ~Button();
    void onFocus();
    void onLooseFocus();
  };

  class Menu : public Component::abstract{
  protected:
    bool _validBackground;
    std::string _texture;
    int _sizeX;
    int _sizeY;
    int _posX;
    int _posY;
    std::list<Button*> _buttons;
    object3d::AObject* _gp;
    Engine::Graphic* _graphic;
  public:
    Menu(Entity::GameObject* _p, Engine::Graphic* g);
    Menu(Entity::GameObject* _p, Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture);
    ~Menu();
    void addButton(Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture, const std::string& textureFocus, bool _isFocus);
    void draw();
    void moveFocus(int i);
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
