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
  public:
    virtual bool	operator()(Event::Data&) = 0;

    /* enable/disable */
  public:
    virtual void	enable() = 0;
    virtual void	disable() = 0;

    /* Ctor */
  public:
    virtual ~Callback();
    Callback(Event::Callback::Id genId = CallbackIdGenerator())
      : _id(genId) {}
  };

  class FixedCallback : public Event::Callback {
  private:
    std::function< void(Event::Data&) > _lambdaCallback;
  public:
    bool operator()(Event::Data&);

  private:
    bool	_enable;
  public:
    void	enable();
    void	disable();

  public:
    FixedCallback(std::function < void(Event::Data&) > _c)
      : Callback(), _lambdaCallback(_c) {}
  };

  typedef int	Time;
  class TimedCallback : public Event::Callback {
  private:
    std::function< void(Event::Data&, Event::Time) > _lambdaCallback;
  public:
    bool operator()(Event::Data&);

  private:
    bool	_enable;
  public:
    void	enable();
    void	disable();

  private:
    Event::Time		_time;
  public:
    TimedCallback(Event::Time time, std::function < void(Event::Data&, Event::Time)> _c)
      : Callback(), _lambdaCallback(_c), _time(time) {}
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
