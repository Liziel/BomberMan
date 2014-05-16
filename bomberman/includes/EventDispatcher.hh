#ifndef __EVENTDISPATCHER__
# define __EVENTDISPATCHER__

#include <map>
#include <list>
#include <functional>

/* pre declaration of component (just in case) */
class Component;

namespace Event{
  /* #### Event Type ##### */
  enum Type{
    Keyboard,
    MouseMove,
    MouseButton
  };


  /* ###### Event Priority ##### */
  enum Priority{
    LOW, MEDIUM, HIGH
  };


  /* ###### Event Data ####### */
  struct Event{
    Event(Event::Type _type) : type(_type) {}
    Event::Type	type;
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
    bool	operator==(Event::Callback::Id);
    Event::Callback::Id	getId(void);

    /* Component */
  private:
    Component&		_object;
    std::function< void(Component&, Event::Event&) > _callback;
  public:
    void	operator()(Event::Event&);

    /* Ctor */
  public:
    template <class U = void(Component::*)(Event::Event&)>
    Event::Callback(Component& object, U callback,
		    Event::Callback::Id genId = CallbackIdGenerator());
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
    std::unordered_map< Event::Type, std::list< Event::Callback* > > _high;
    std::unordered_map< Event::Type, std::list< Event::Callback* > > _med;
    std::unordered_map< Event::Type, std::list< Event::Callback* > > _low;
  public:
    Event::Callback::Id addCallbackOnEvent(Event::Type, Event::Callback*,
					   Event::Priority = MEDIUM);
    void		unsetCallbackForId(Event::Type,
					   Event::Callback::Id);

    void		dispatchEvent(Event::Event&);

    /* Ctor */
  public:
    EventDispatcher();
  };
};


/* Event Example */
struct KeyBoardEvent : EventDispatcher::Event{
  KeyBoardEvent() : Event::Event(KeyBoard) {}
  int		keyCode;
  bool		realesed;
};

struct MouseMoveEvent{
  MouseMoveEvent(int x, int y)
    : Event::Event(MouseMove),
      xLocation(x), yLocation(y) {}
  int	xLocation;
  int	yLocation;
};

struct MouseButtonEvent{
  MouseButtonEvent(int x, int y, char code, bool state)
    : EventDispatcher::Event(MouseButton),
      xLocation(x), yLocation(y), keyCode(code), keyState(state) {}
  int	xLocation;
  int	yLocation;
  char	keyCode;
  bool	keyState;
};
#endif
