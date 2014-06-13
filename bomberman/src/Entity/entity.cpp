#include "Entity.hh"
#include "Component.hh"

Entity::GameObject::GameObject() {}
Entity::GameObject::GameObject(Event::Dispatcher* Dispatch, Entity::Type _t)
  : _Dispatch(Dispatch), selfType(_t), x(0), y(0) {
  _Dispatch->addCallbackOnEvent(Event::Info::EntityDisable,
				new Event::StaticCallback([this] (Event::Data& e) {
				    Event::Type::EntityDisable* event = 
				      reinterpret_cast<Event::Type::EntityDisable*>(&e);
				    if (event->type == selfType)
				      disable();
				  }));
  _Dispatch->addCallbackOnEvent(Event::Info::EntityEnable,
				new Event::StaticCallback([this] (Event::Data& e) {
				    Event::Type::EntityEnable* event = 
				      reinterpret_cast<Event::Type::EntityEnable*>(&e);
				    if (event->type == selfType)
				      enable();
				  }));

  _Dispatch->addCallbackOnEvent(Event::Info::EntitySerialize,
				new Event::StaticCallback([this] (Event::Data& e) {
				    Event::Type::EntitySerialize* event = 
				      reinterpret_cast<Event::Type::EntitySerialize*>(&e);
				    if (event->type == selfType)
				      *(event->localSave) << serialization();
				  }));
}

Entity::GameObject::~GameObject() {
  for (auto _cb : _CallbackArray) {
    _Dispatch->unsetCallbackForId(_cb.first, _cb.second->getId());
  }
  for (auto _cp : ComponentList) {
    delete _cp;
  }
}

Event::Callback::Id	Entity::GameObject::addCallback(Event::Info::Type type,
							Event::Callback* callback,
							Event::Info::Priority _p){
  _CallbackArray.push_back(std::pair< Event::Info::Type, Event::Callback* >
			   (type, callback));
  _Dispatch->addCallbackOnEvent(type, callback, _p);
  return (callback->getId());
}

void	Entity::GameObject::attachComponent(Component::abstract* _c) {
  ComponentList.push_back(_c);
}

std::string Entity::GameObject::serialization() {
  std::string serial;
  serial = Tokenizer::serialize(getName(), x, y) + "\n";
  for (auto component : ComponentList)
    serial += component->serialization() + "\n";
  return (serial + "###\n");
}

void	Entity::GameObject::setBySerial(const Tokenizer& t){
  x = t.get<int>(1);
  y = t.get<int>(2);
}

void	Entity::GameObject::getPosition(double& _x, double& _y) const {
  _x = x;
  _y = y;
}

void	Entity::GameObject::setPosition(double _x, double _y) {
  x = _x;
  y = _y;
}

void	Entity::GameObject::dispatchSelf(Event::Data* e) {
  for (auto pair : _CallbackArray) {
    if (pair.first == e->type)
      (*(pair.second))(*e);
    if (pair.first == Event::Info::Network && e->network == true)
      (*(pair.second))(*e);
  }
  delete e;
}

void	Entity::GameObject::dispatchAll(Event::Data* e) {
  _Dispatch->dispatchEvent(e);
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
