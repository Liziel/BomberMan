#include "Entity.hh"
#include "Component.hh"

namespace Entity{
  Factory::Factory(Component::Factory *_f)
    : _componentFactory(_f) {}

  void	Factory::addAllocator(const std::string& def, std::function< Entity::GameObject*(bool, Entity::GameObject*)> allocator) {
    _EntityAllocator.insert(std::pair< std::string, std::function< Entity::GameObject*(bool, Entity::GameObject*) > >(def, allocator));
  }

  Entity::GameObject*	Factory::allocateEntityByType(const std::string& key, bool init) {
    auto it = _EntityAllocator.find(key);
    if (it != _EntityAllocator.end())
      return (it->second(init, NULL));
    else
      return (NULL);
  }

  Entity::GameObject*	Factory::allocateEntityBySerial(const std::string& key)  {
    std::stringstream ssf(key);
    std::string line;

    if (!std::getline(ssf, line, '\n'))
      return (NULL);
    Tokenizer t(line);
    Entity::GameObject* a = allocateEntityByType(std::string(t.get<const char*>(0)), game);
    a->setBySerial(t);
    while (std::getline(ssf, line, '\n'))
      a->attachComponent(_componentFactory->allocateComponentBySerial(line, a));
    return (a);
  }

  Entity::GameObject* Factory::allocateComponentByEntityType(const std::string& key, Entity::GameObject* object) {
    auto it = _EntityAllocator.find(key);
    if (it != _EntityAllocator.end())
      return (it->second(true, object));
    return (object);
  }

};
