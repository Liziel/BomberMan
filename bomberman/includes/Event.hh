#ifndef __EVENTDISPATCHER__
# define __EVENTDISPATCHER__

#include <unordered_map>
#include <list>
#include <functional>

#include "EventType.hh"

/* pre declaration of component (just in case) */
namespace Component{ class GameObject; };

namespace Event{

  /* ###### Event Data ####### */
  struct Data{
    Data(Event::Info::Type _type) : type(_type) {}
    Event::Info::Type	type;
  };


  /* ###### CallBack ######## */
  unsigned int CallbackIdGenerator(void);
  class Callback{
  public:
    typedef unsigned int Id;
    /* id */
  private:
    Event::Callback::Id	_id;
  public:
    bool	operator==(Event::Callback::Id) const;
    Event::Callback::Id	getId(void) const;

    /* Component::GameObject */
  private:
    Component::GameObject&		_object;
    std::function< void(Component::GameObject&, Event::Data&) > _callback;
  public:
    void	operator()(Event::Data&);

    /* enable/disable */
  private:
    bool	_enabled;
  public:
    void	enable();
    void	disable();

    /* Ctor */
  public:
    template <class U = void(Component::GameObject::*)(Event::Data&)>
    Callback(Component::GameObject& object, U callback,
	     Event::Callback::Id genId = Event::CallbackIdGenerator());
  };

  /* ####### Callback Remover ####### */
  class CallbackRemover{
  private:
    Event::Callback::Id _r;
  public:
    CallbackRemover(Event::Callback::Id);
    bool operator()(Callback*);
  };

  /* ####### Dispatcher ######## */
  class Dispatcher{
  private:
    std::unordered_map< Event::Info::Type, std::list< Event::Callback* >, std::hash<int> > _high;
    std::unordered_map< Event::Info::Type, std::list< Event::Callback* >, std::hash<int> > _med;
    std::unordered_map< Event::Info::Type, std::list< Event::Callback* >, std::hash<int> > _low;
  public:
    Event::Callback::Id addCallbackOnEvent(Event::Info::Type, Event::Callback*,
					   Event::Info::Priority = Event::Info::medium);
    void		unsetCallbackForId(Event::Info::Type,
					   Event::Callback::Id);

    void		dispatchEvent(Event::Data&);

    /* Ctor */
  public:
    Dispatcher();
  };
};


/* Event Example */
struct KeyBoardEvent : Event::Data{
  KeyBoardEvent() : Event::Data(Event::Info::Keyboard) {}
  int		keyCode;
  bool		realesed;
};

struct MouseMoveEvent : Event::Data{
  MouseMoveEvent(int x, int y)
    : Event::Data(Event::Info::MouseMove),
      xLocation(x), yLocation(y) {}
  int	xLocation;
  int	yLocation;
};

struct MouseButtonEvent : Event::Data{
  MouseButtonEvent(int x, int y, char code, bool state)
    : Event::Data(Event::Info::MouseButton),
      xLocation(x), yLocation(y), keyCode(code), keyState(state) {}
  int	xLocation;
  int	yLocation;
  char	keyCode;
  bool	keyState;
};

#endif
