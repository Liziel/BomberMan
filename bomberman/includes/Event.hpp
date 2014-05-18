#ifndef __EVENTDISPATCHER__
# define __EVENTDISPATCHER__

# include <unordered_map>
# include <list>
# include <functional>
# include <queue>

# include "EventType.hh"

/* pre declaration of component (just in case) */
namespace Component{ class GameObject; };

namespace Event{

  /* ###### Event Data ####### */
  namespace Info{ enum Type; };
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
    Component::GameObject*		_object;
    std::function< void(Component::GameObject*, Event::Data&) > _callback;
    std::function< void(Event::Data&) > _lambdaCallback;
  public:
    void	operator()(Event::Data&);

    /* enable/disable */
  private:
    bool	_enabled;
  public:
    void	enable();
    void	disable();

    /* Ctor */
  private:
    Callback();
  public:
    Callback(std::function < void(Event::Data&) > callback,
	     Event::Callback::Id genId = CallbackIdGenerator())
      : _id(genId), _lambdaCallback(callback),
	_enabled(true) {}

    template< class U >
    Callback(Component::GameObject* object,
	     void (U::*callback)(Event::Data&),
	     Event::Callback::Id genId = CallbackIdGenerator())
      : _id(genId), _object(object),
	_callback(reinterpret_cast
		  <void(Component::GameObject::*)(Event::Data&)>(callback)),
	_enabled(true) {}
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
  private:
    bool			_isdispatching;
    std::queue<Event::Data>	_eventQueue;

  public:
    Event::Callback::Id addCallbackOnEvent(Event::Info::Type,
					   Event::Callback*,
					   Event::Info::Priority
					    = Event::Info::medium);
    void		unsetCallbackForId(Event::Info::Type,
					   Event::Callback::Id);

    void		dispatchEvent(Event::Data&);
    void		dispatchEvent(Event::Data*);

    /* Ctor */
  public:
    Dispatcher();
  };
};

#endif
