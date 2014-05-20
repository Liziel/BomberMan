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

    struct PlayerMove : Event::Data{
      PlayerMove(Entity::Player::Id _p, double x, double y,
		 double axeX, double axeY)
	: Event::Data(Event::Info::PlayerMove, sizeof(struct PlayerMove), true),
	  player(_p), xLocation(x), yLocation(y), xAxis(axeX), yAxis(axeY) {} 
      Entity::Player::Id player;
      double	xLocation;
      double	yLocation;
      double	xAxis;
      double	yAxis;     
    };

    struct DeniedMove : Event::Data{
      DeniedMove(Entity::Player::Id _p, double x, double y)
	: Event::Data(Event::Info::DeniedMove, sizeof(struct DeniedMove), false),
	  player(_p), xLocation(x), yLocation(y) {}
      Entity::Player::Id player;
      double	xLocation;
      double	yLocation;
    };

    struct DamageFixed : Event::Data{
      DamageFixed(int _x, int _y, int _amount)
	: Event::Data(Event::Info::DamageFixed, sizeof(struct DamageFixed), false),
	  x(_x), y(_y), amount(_amount) {}
      int x;
      int y;
      int amount;
    };
    
    struct PlantBomb : Event::Data{
      PlantBomb(int _x, int _y)
	: Event::Data(Event::Info::PlantBomb, sizeof(struct PlantBomb), true),
	  x(_x), y(_y) {}
      int x;
      int y;
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
