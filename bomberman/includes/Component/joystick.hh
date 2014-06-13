#ifndef __JOYSTICK_H__
# define __JOYSTICK_H__

#include <cstdlib>
#include <SDL/SDL.h>
#include "Component.hh"

namespace Component{
  class JoystickManager : public Component::Superior {
  private:
    std::array<SDL_Joystick*, 4>	_joystick;

  public:
    class joystick : public Component::abstract{
    private:
      SDL_Joystick*		_joystick;
      std::array< std::pair< int, bool >, 10 >	keyState;	

    public:
      joystick(Entity::GameObject*, SDL_Joystick*);
      ~joystick();

    public:
      std::string serialization();
      void	setBySerial(const Tokenizer&);
    };

  public:
SDL_Joystick*	getJoystick(int);

  public:
    JoystickManager(Event::Dispatcher*);
    ~JoystickManager();
  };
};

namespace Event{
namespace Type{
# ifndef __ARENA_H__
    struct Keyboard : Event::Data{
      Keyboard(int k, bool s)
	: Event::Data(Event::Info::Keyboard, sizeof(struct Keyboard), false),
	  key(k), state(s) {}
      int key;
      bool state;
    };
# endif
};
};

#endif
