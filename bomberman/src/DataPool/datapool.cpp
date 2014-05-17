#include "DataPool.hh"

void	DataPool::addComponent(Component* _c, std::string type) {
  if (ComponentMap.find(type) == ComponentMap.end())
    ComponentMap.insert(std::pair< std::string, std::list< Component* > >
			(type, std::list< Component* >(1, _c)));
  else
    ComponentMap[type].push_back(_c);
}

void	DataPool::disableType(std::string type) {
  std::list< Component* > *_c;
  if (ComponentMap.find(type) != ComponentMap.end())
    return ;
  _c = ComponentMap[type];
  for (auto _cs : (*_c))
    _cs->disable();
}

void	DataPool::disableType(std::string type) {
  std::list< Component* > *_c;
  if (ComponentMap.find(type) != ComponentMap.end())
    return ;
  _c = ComponentMap[type];
  for (auto _cs : (*_c))
    _cs->enable();
}
