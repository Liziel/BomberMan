#include "Entity.hh"

Entity::GameObject::GameObject() {}
Entity::GameObject::GameObject(GraphicEngine* GrEngine, Event::Dispatcher* Dispatch)
  : _GrEngine(GrEngine), _Dispatch(Dispatch) {}
Entity::GameObject::~GameObject() {
  for (auto _cb : _CallbackArray) {
    _Dispatch->unsetCallbackForId(_cb.first, _cb.second->getId());
    delete _cb.second;
  }
}

Event::Callback::Id	Entity::GameObject::addCallback(Event::Info::Type type,
					       Event::Callback* callback,
					       Event::Info::Priority _p) {
  _CallbackArray.push_back(std::pair< Event::Info::Type, Event::Callback* >
			   (type, callback));
  _Dispatch->addCallbackOnEvent(type, callback, _p);
  return (callback->getId());
}

void	Entity::GameObject::unsetCallback(Event::Callback* callback) {
  class unsetCallback{
  private:
    Event::Callback* prim;
    Event::Dispatcher* dispatch;
  public:
    unsetCallback(Event::Callback* _prim, Event::Dispatcher* _dispatch)
      : prim(_prim), dispatch(_dispatch) {}
    bool operator()(std::pair< Event::Info::Type, Event::Callback* > pair) {
      bool is = ((pair.second) == prim);
      if (is)
	dispatch->unsetCallbackForId(pair.first, pair.second->getId());
      return (is);
    }
  } remove(callback, _Dispatch);
  _CallbackArray.remove_if(remove);
}

void	Entity::GameObject::unsetCallback(Event::Callback::Id callback) {
  class unsetCallback{
  private:
    Event::Callback::Id prim;
    Event::Dispatcher* dispatch;
  public:
    unsetCallback(Event::Callback::Id _prim, Event::Dispatcher* _dispatch)
      : prim(_prim), dispatch(_dispatch) {}
    bool operator()(std::pair< Event::Info::Type, Event::Callback* > pair) {
      bool is = (*(pair.second) == prim);
      if (is)
	dispatch->unsetCallbackForId(pair.first, pair.second->getId());
      return (is);
    }
  } remove(callback, _Dispatch);
  _CallbackArray.remove_if(remove);
}

void	Entity::GameObject::enable(void) {
  for (auto callback : _CallbackArray)
    callback.second->enable();
}

void	Entity::GameObject::disable(void) {
  for (auto callback : _CallbackArray)
    callback.second->disable();
}
