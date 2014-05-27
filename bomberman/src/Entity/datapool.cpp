#include "DataPool.hh"

Entity::Pool::Pool(Event::Dispatcher* _d) {
  _d->addCallbackOnEvent(Event::Info::EntityDisable,
			 new Event::FixedCallback([this] (Event::Data& e){
			     Event::Type::EntityDisable* event = 
			       reinterpret_cast<Event::Type::EntityDisable*>
			       (&e);
			     disableType(event->type);
			   }));
  _d->addCallbackOnEvent(Event::Info::EntityEnable,
			 new Event::FixedCallback([this] (Event::Data& e){
			     Event::Type::EntityEnable* event = 
			       reinterpret_cast<Event::Type::EntityEnable*>
			       (&e);
			     enableType(event->type);
			   }));
}

void	Entity::Pool::addEntity(Entity::GameObject* _c, Entity::Type type) {
  if (EntityMap.find(type) == EntityMap.end())
    EntityMap.insert(std::pair< Entity::Type,
			std::list< Entity::GameObject* > >
			(type, std::list< Entity::GameObject* >(1, _c)));
  else
    EntityMap[type].push_back(_c);
}

void	Entity::Pool::disableType(Entity::Type type) {
  std::list< Entity::GameObject* > *_c;
  if (EntityMap.find(type) != EntityMap.end())
    return ;
  _c = &EntityMap[type];
  for (auto _cs : (*_c))
    _cs->disable();
}

void	Entity::Pool::enableType(Entity::Type type) {
  std::list< Entity::GameObject* > *_c;
  if (EntityMap.find(type) != EntityMap.end())
    return ;
  _c = &EntityMap[type];
  for (auto _cs : (*_c))
    _cs->enable();
}
