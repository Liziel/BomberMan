#include <iostream>
#include <map>
#include "Component.hh"

namespace Component{

  Factory::Factory()
  {}

  /* AllocateComponentByType is as its says to allocate a new component and save several states and types */
  Component::Abstract*	Factory::allocateComponentByType(const std::string& key, Entity::GameObject *game)
  {
    auto it = _ComponentAllocator.find(key);
    if (it != map.end())
      return (NULL);
    else
      return (it->second(game));
  }

  /* AllocateComponentBySerial is as its says to allocate a new component by it serialization it also allocateByType just after */
  Component::Abstract*	Factory::allocateComponentBySerial(const std::string& key, Entity::GameObject *game)
  {
    Tokenizer t(key);
    Component::Abstract* a = allocateComponentByType(std::string(t.get<const char*>(0)), game);
    a->setBySerial(t);
    return (a);
  }

};
