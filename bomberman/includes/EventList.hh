#ifndef __EVENTLIST_H__
# define __EVENTLIST_H__

#include "EventType.hh"
#include "Event.hpp"

namespace Event{

  namespace Type{
    /* Event Example */
    struct KeyBoard : Event::Data{
      KeyBoard() : Event::Data(Event::Info::Keyboard) {}
      int		keyCode;
      bool		realesed;
    };
    
    struct MouseMove : Event::Data{
      MouseMove(int x, int y)
	: Event::Data(Event::Info::MouseMove),
	  xLocation(x), yLocation(y) {}
      int	xLocation;
      int	yLocation;
    };
    
    struct MouseButton : Event::Data{
      MouseButton(int x, int y, char code, bool state)
	: Event::Data(Event::Info::MouseButton),
	  xLocation(x), yLocation(y), keyCode(code), keyState(state) {}
      int	xLocation;
      int	yLocation;
      char	keyCode;
      bool	keyState;
    };
    struct Clock : Event::Data{
      Clock() : Event::Data(Event::Info::Clock) {}
    };
  };
};

#endif
