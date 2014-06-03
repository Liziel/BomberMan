#ifndef __ENTITY_H__
# define __ENTITY_H__

# include <map>
# include <list>
# include <utility>
# include <string>
# include <iostream>

# include "Event.hpp"
# include "Tokenizer.hpp"

namespace Component{
  class abstract;
  class Factory;
};

namespace Component{
  class Factory;
}

namespace Entity{
  enum Type {_default, game, gameOption};
  class GameObject{
  private:
    GameObject();

  private:
    Event::Dispatcher*		_Dispatch;
  private:
    std::list< std::pair< Event::Info::Type,
			  Event::Callback* > > _CallbackArray;
  private:
    Entity::Type	selfType;
  public:
    GameObject(Event::Dispatcher* Dispatch, Entity::Type);

  private:
    std::vector<Component::abstract*>	ComponentList;
  public:
    void	attachComponent(Component::abstract*);

  public:
    virtual void	setBySerial(const Tokenizer&);
    virtual std::string	serialization();
    virtual std::string getName() { return ("entity"); }

  public:
    virtual ~GameObject();
    Event::Callback::Id	addCallback(Event::Info::Type, Event::Callback*,
				    Event::Info::Priority
				    = Event::Info::medium);
    void	dispatchSelf(Event::Data*);
    void	dispatchAll(Event::Data*);

    void	unsetCallback(Event::Callback*);
    void	unsetCallback(Event::Callback::Id);
    
  public:
    void	enable(void);
    void	disable(void);

  protected:
    int x;
    int y;
  public:
    void	getPosition(double& x, double& y) const;
    void	setPosition(double x, double y);

  public:
    virtual int	getLifeAmount(void) { return (-1); }
  };

  class Factory{
  private:
    std::map< std::string, std::function< Entity::GameObject*(bool) > > _EntityAllocator;
    Component::Factory*	_componentFactory;

  public:
    Factory(Component::Factory*);

  public:
    Entity::GameObject* allocateEntityByType(const std::string&, bool init = true);
    Entity::GameObject* allocateEntityBySerial(const std::string&);
    
  public:
    void	addAllocator(const std::string&, std::function< Entity::GameObject*(bool) >);
  };

};

namespace Event{
  namespace Type{

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

    struct EntityFlush : Event::Data{
      EntityFlush(Entity::Type _n)
	: Event::Data(Event::Info::EntityFlush, sizeof(EntityFlush), false),
	  type(_n) {}
      Entity::Type	type;
    };

    struct EntitySerialize : Event::Data{
      EntitySerialize(Entity::Type _n)
	: Event::Data(Event::Info::EntitySerialize, sizeof(EntitySerialize), false),
	  type(_n) {}
      Entity::Type	type;
      std::fstream*	localSave;
    };

  };
};

#endif
