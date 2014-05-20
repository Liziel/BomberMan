#include "Event.hpp"
#include "Component.hh"

namespace Event{
  /*	Data	*/

  /* Callback */
  void	Callback::operator()(Event::Data& event) {
    if (_enabled)
      (_lambdaCallback) ? (_lambdaCallback(event))
	: (_callback(_object, event));
  }

  bool	Callback::operator==(Event::Callback::Id oth) const {
    return (oth == _id);
  }

  Event::Callback::Id	Callback::getId(void) const {
    return (_id);
  }

  void	Callback::enable(void){
    _enabled = true;
  }

  void	Callback::disable(void){
    _enabled = false;
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
    bool is = ((*oth) == _r);
    if (is) delete oth;
    return (is);
  }


  /* Dispatcher */
  Dispatcher::Dispatcher() :_isdispatching(false) {}

  Event::Callback::Id
    Dispatcher::addCallbackOnEvent(Event::Info::Type type,
				   Event::Callback* callback,
				   Event::Info::Priority prio){
    if (prio == Event::Info::high){
      if (_high.find(type) == _high.end())
	_high.
	  insert(std::pair< Event::Info::Type, std::list<Event::Callback*> >
		 (type, std::list<Event::Callback*>()));
      _high[type].push_front(callback);
    } else if (prio == Event::Info::medium) {
      if (_med.find(type) == _med.end())
	_med.
	  insert(std::pair< Event::Info::Type, std::list<Event::Callback*> >
		 (type, std::list<Event::Callback*>()));
      _med[type].push_front(callback);
    } else if (prio == Event::Info::low) {
      if (_low.find(type) == _low.end())
	_low.
	  insert(std::pair< Event::Info::Type, std::list<Event::Callback*> >
		 (type, std::list<Event::Callback*>()));
      _low[type].push_front(callback);
    }
      return (callback->getId());
  }

  void	Dispatcher::unsetCallbackForId(Event::Info::Type type,
				       Event::Callback::Id id){
    Event::CallbackRemover remove(id);

    if (_high.find(type) != _high.end())
      _high[type].remove_if(remove);
    if (_med.find(type) != _med.end())
      _med[type].remove_if(remove);
    if (_low.find(type) != _low.end())
      _low[type].remove_if(remove);
  }

  void	Dispatcher::dispatchEvent(Event::Data* event) {
    std::list< Event::Callback* >* CallbackArray;
    std::unordered_map
      < Event::Info::Type , std::list< Event::Callback* >, std::hash<int> >
      ::iterator itt;

    if (_isdispatching){
      _eventQueue.push(event);
      return ;
    }

    _isdispatching = true;
    if ((itt = _high.find(event->type)) != _high.end()){
      CallbackArray = &(itt->second);
      for (auto callback : *CallbackArray)
	(*callback)(*event);
    }
    if ((itt = _med.find(event->type)) != _med.end()){
      CallbackArray = &(itt->second);
      for (auto callback : *CallbackArray)
	(*callback)(*event);
    }
    if ((itt = _low.find(event->type)) != _low.end()){
      CallbackArray = &(itt->second);
      for (auto callback : *CallbackArray)
	(*callback)(*event);
    }

    if (event->network){
      if ((itt = _high.find(Event::Info::Network)) != _high.end()){
	CallbackArray = &(itt->second);
	for (auto callback : *CallbackArray)
	  (*callback)(*event);
      }
      if ((itt = _med.find(Event::Info::Network)) != _med.end()){
	CallbackArray = &(itt->second);
	for (auto callback : *CallbackArray)
	  (*callback)(*event);
      }
      if ((itt = _low.find(Event::Info::Network)) != _low.end()){
	CallbackArray = &(itt->second);
	for (auto callback : *CallbackArray)
	  (*callback)(*event);
      }
    }

    _isdispatching = false;
    if (!_eventQueue.empty()) {
      dispatchEvent(_eventQueue.front());
      _eventQueue.pop();
    }
    delete event;
  }
};
