#include "EventDispatcher.hh"

namespace Event{
  /* Callback */
  Callback::Callback(T object, U callback, Event::Callback::Id genId)
    : _id(genId), _object(object), _callback(callback) {}    
  
  void	Callback::operator()(Event::Event& event) {
    _callback(_object, event);
  }

  void	Callback::operator==(Event::Callback::Id oth) {
    return (chs == _id);
  }

  Event::Callback::Id	getId(void) {
    return (_id);
  }

  /* Gen Id */
  Event::Callback::Id CallbackIdGenerator() {
    static Event::Callback::Id genId;
    genId += 1;
    return (genId);
  }


  /* Callback Remover */
  CallbackRemover::CallbackRemover(Event::Callback::Id r)
    : _r(r) {}

  bool CallbackRemover::operator()(Callback* oth) {
    bool is = (oth == _r);
    if (is) delete oth;
    return (is);
  }


  /* Dispatcher */
  Dispatcher::Dispatcher() {}

  Event::Callback::Id
    Dispatcher::addCallbackOnEvent(Event::Type type,
				   Event::Callback* callback,
				   Event::Priority prio){
    if (prio == HIGH){
      if (_high.find(type) == _high.end())
	_high.
	  insert(std::pair< Event::Type, std::list<Event::Callback> >
		 (type, std::list<Event::Callback*>()));
      _high[type].push_front(callback);
    } else if (prio == MEDIUM) {
      if (_med.find(type) == _med.end())
	_med.
	  insert(std::pair< Event::Type, std::list<Event::Callback> >
		 (type, std::list<Event::Callback*>()));
      _med[type].push_front(callback);
    } else if (prio == LOW) {
      if (_low.find(type) == _low.end())
	_low.
	  insert(std::pair< Event::Type, std::list<Event::Callback> >
		 (type, std::list<Event::Callback*>()));
      _low[type].push_front(callback);
    }
      return (callback->getId());

  }

  void	Dispatcher::unsetCallbackForId(Event::Type type,
				       Event::Callback::Id id){
    Event::CallbackRemover remove(id);

    if (_high.find(type) != _high.end())
      _high[type].remove_if(remove);
    if (_med.find(type) != _med.end())
      _med[type].remove_if(remove);
    if (_low.find(type) != _low.end())
      _low[type].remove_if(remove);
  }

  void	Dispatcher::dispatchEvent(Event::Event& event) {
    if (_high.find(event.type) != _high.end())
      for (auto callback : _high[event.type])
	callback(event);
    if (_med.find(event.type) != _med.end())
      for (auto callback : _med[event.type])
	callback(event);
    if (_low.find(event.type) != _low.end())
      for (auto callback : _low[event.type])
	callback(event);
  }
  
};
