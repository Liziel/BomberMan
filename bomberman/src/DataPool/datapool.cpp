#include "DataPool.hh"

Entity::Pool::Pool() {}

void	Entity::Pool::addEntity(Entity::GameObject* _c, std::string type) {
  if (EntityMap.find(type) == EntityMap.end())
    EntityMap.insert(std::pair< std::string,
			std::list< Entity::GameObject* > >
			(type, std::list< Entity::GameObject* >(1, _c)));
  else
    EntityMap[type].push_back(_c);
}

void	Entity::Pool::disableType(std::string type) {
  std::list< Entity::GameObject* > *_c;
  if (EntityMap.find(type) != EntityMap.end())
    return ;
  _c = &EntityMap[type];
  for (auto _cs : (*_c))
    _cs->disable();
}

void	Entity::Pool::enableType(std::string type) {
  std::list< Entity::GameObject* > *_c;
  if (EntityMap.find(type) != EntityMap.end())
    return ;
  _c = &EntityMap[type];
  for (auto _cs : (*_c))
    _cs->enable();
}
