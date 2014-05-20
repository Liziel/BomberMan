#ifndef __EVENTDISPATCHER__
# define __EVENTDISPATCHER__

# include <unordered_map>
# include <list>
# include <functional>
# include <queue>

# include "EventType.hh"

namespace Event{
  /* ###### Event Data ####### */
  namespace Info{ enum Type; };
  struct Data{
    Data(Event::Info::Type _type, size_t DataSize, bool _network)
      : type(_type), size(DataSize), network(_network) {}
    Event::Info::Type	type;
    size_t		size;
    bool		network;
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
    std::queue<Event::Data*>	_eventQueue;

  public:
    Event::Callback::Id addCallbackOnEvent(Event::Info::Type,
					   Event::Callback*,
					   Event::Info::Priority
					    = Event::Info::medium);
    void		unsetCallbackForId(Event::Info::Type,
					   Event::Callback::Id);

    void		dispatchEvent(Event::Data*);

    /* Ctor */
  public:
    Dispatcher();
  };
};

#endif
