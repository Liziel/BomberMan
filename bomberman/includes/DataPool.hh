#ifndef __DATAPOOL_H__
# define __DATAPOOL_H__

# include <list>
# include <string>
# include <map>

# include "Entity.hh"

namespace Entity{
  enum Type {_default, game, gameOption};

  class Pool{
    /* Entity::GameObject List */
  private:
    std::map
    < Entity::Type, std::list< Entity::GameObject* > > EntityMap;
    
    /* Add Entity */
  public:
    void	addEntity(Entity::GameObject*,
			  Entity::Type = _default);
    void	disableType(Entity::Type = _default);
    void	enableType(Entity::Type = _default);
    
    /* Ctor */
  public:
    Pool(Event::Dispatcher*);
  };
};

namespace Event{
  namespace Type{
#ifndef __ARENA_H__
    struct EntityEnable : Event::Data{
      EntityEnable(Entity::Type _n)
	: Event::Data(Event::Info::EntityEnable, sizeof(EntityEnable), false),
	  type(_n) {}
      Entity::Type	type;
    };

    struct EntityDisable : Event::Data{
      EntityDisable(Entity::Type _n)
	: Event::Data(Event::Info::EntityDisable, sizeof(EntityDisable), false),
	  type(_n) {}
      Entity::Type	type;
    };
#endif
  };
};

#endif
