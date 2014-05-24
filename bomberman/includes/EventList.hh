#ifndef __EVENTLIST_H__
# define __EVENTLIST_H__

# include "EventType.hh"
# include "Event.hpp"
# include "GameEntity.hh"

namespace Event{

  namespace Type{
    /* Event Example */
    struct Keyboard : Event::Data{
      Keyboard(int key, bool _state)
	: Event::Data(Event::Info::Keyboard, sizeof(struct Keyboard), false),
	  keyCode(key), state(_state) {}
      int		keyCode;
      bool		state;
    };
    
    struct MouseMove : Event::Data{
      MouseMove(int x, int y)
	: Event::Data(Event::Info::MouseMove, sizeof(struct MouseMove), false),
	  xLocation(x), yLocation(y) {}
      int	xLocation;
      int	yLocation;
    };
    
    struct MouseButton : Event::Data{
      MouseButton(int x, int y, char code, bool state)
	: Event::Data(Event::Info::MouseButton, sizeof(struct MouseMove), false),
	  xLocation(x), yLocation(y), keyCode(code), keyState(state) {}
      int	xLocation;
      int	yLocation;
      char	keyCode;
      bool	keyState;
    };

    struct Clock : Event::Data{
      Clock() : Event::Data(Event::Info::Clock, sizeof(struct Clock), true) {}
    };

    struct Refresh : Event::Data{
      Refresh() : Event::Data(Event::Info::Refresh,
			      sizeof(struct Refresh), false) {}
    };

  };
};

#endif
