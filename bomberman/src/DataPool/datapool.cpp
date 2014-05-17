#include "DataPool.hh"

DataPool::DataPool() {}

void	DataPool::addComponent(Component::GameObject* _c, std::string type) {
  if (ComponentMap.find(type) == ComponentMap.end())
    ComponentMap.insert(std::pair< std::string,
			std::list< Component::GameObject* > >
			(type, std::list< Component::GameObject* >(1, _c)));
  else
    ComponentMap[type].push_back(_c);
}

void	DataPool::disableType(std::string type) {
  std::list< Component::GameObject* > *_c;
  if (ComponentMap.find(type) != ComponentMap.end())
    return ;
  _c = &ComponentMap[type];
  for (auto _cs : (*_c))
    _cs->disable();
}

void	DataPool::enableType(std::string type) {
  std::list< Component::GameObject* > *_c;
  if (ComponentMap.find(type) != ComponentMap.end())
    return ;
  _c = &ComponentMap[type];
  for (auto _cs : (*_c))
    _cs->enable();
}
