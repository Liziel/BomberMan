#include "DataPool.hh"

Component::Pool::Pool() {}

void	Component::Pool::addComponent(Component::GameObject* _c, std::string type) {
  if (ComponentMap.find(type) == ComponentMap.end())
    ComponentMap.insert(std::pair< std::string,
			std::list< Component::GameObject* > >
			(type, std::list< Component::GameObject* >(1, _c)));
  else
    ComponentMap[type].push_back(_c);
}

void	Component::Pool::disableType(std::string type) {
  std::list< Component::GameObject* > *_c;
  if (ComponentMap.find(type) != ComponentMap.end())
    return ;
  _c = &ComponentMap[type];
  for (auto _cs : (*_c))
    _cs->disable();
}

void	Component::Pool::enableType(std::string type) {
  std::list< Component::GameObject* > *_c;
  if (ComponentMap.find(type) != ComponentMap.end())
    return ;
  _c = &ComponentMap[type];
  for (auto _cs : (*_c))
    _cs->enable();
}
