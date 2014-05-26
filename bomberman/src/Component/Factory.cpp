#include <iostream>
#include <map>
#include "Component.hh"

namespace Component{

  Factory::Factory()
  {}

  Component::Abstract*	Factory::allocateComponentByType(const std::string& key, Entity::GameObject *game)
  {
    auto it = _ComponentAllocator.find(key);
    if (it != map.end())
      return (NULL);
    else
      return (it->second(game));
  }

  Component::Abstract*	Factory::allocateComponentBySerial()
  {
    Tokenizer t(key);
    Component::abstract* a = allocateComponentByType(std::string(t.get<const char*>(0)), game);
    a->setBySerial(t);
    return (a);
  }

};
