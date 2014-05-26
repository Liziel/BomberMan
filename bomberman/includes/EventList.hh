#ifndef __EVENTLIST_H__
# define __EVENTLIST_H__

# include "EventType.hh"
# include "Event.hpp"
# include "GameEntity.hh"

namespace Event{

  namespace Type{
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
