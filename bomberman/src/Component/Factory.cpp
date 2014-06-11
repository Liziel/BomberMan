#include <iostream>
#include <map>
#include "Component.hh"

namespace Component{

  Factory::Factory()
  {}
  void		Factory::storeComponentAllocator(std::string name, std::function<Component::abstract*(Entity::GameObject*)> _f) {
    _ComponentAllocator.insert(std::pair<std::string, std::function< Component::abstract*(Entity::GameObject *) > >(name, _f));
  }

  Component::abstract*	Factory::allocateComponentByType(const std::string& key, Entity::GameObject *game)
  {
    auto it = _ComponentAllocator.find(key);
    if (it != _ComponentAllocator.end())
      return (it->second(game));
    else
      return (NULL);
  }

  Component::abstract*	Factory::allocateComponentBySerial(const std::string& key, Entity::GameObject *game)
  {
    Tokenizer t(key);
    Component::abstract* a = allocateComponentByType(std::string(t.get<const char*>(0)), game);
    a->setBySerial(t);
    return (a);
  }

};
