#ifndef __COMPONENT_H__
# define __COMPONENT_H__

# include <list>
# include <fstream>
# include <exception>
# include <map>

# include "Tokenizer.hpp"
# include "Entity.hh"
# include "Event.hpp"
# include "EventList.hh"

namespace Component{

  /*  ############# abstract ################  */
  class abstract{
  protected:
    Entity::GameObject*		parent;
  protected:
    abstract(Entity::GameObject* _p);
  public:
    virtual ~abstract();


  protected:
    void		dispatchAll(Event::Data*);
    void		dispatchSelf(Event::Data*);
    Event::Callback::Id	attachCallback(Event::Info::Type, Event::Callback*,
				       Event::Info::Priority
				       = Event::Info::medium);

    /* serialization */
  public:
    virtual std::string serialization() = 0;
    virtual void	setBySerial(const Tokenizer&) = 0;
  };

  class Superior{

  public:
    class Pool{
    private:
      std::vector<Superior*>	superiorPool;
    public:
      void	callSerial(std::fstream&);
      
    };

  protected:
    Event::Dispatcher*	dispatcher;
  public:
    Superior(Event::Dispatcher* _d)
      : dispatcher(_d) {}
  };

  /* ########## Factory ########## */
  class Factory{
  private:
    std::map<std::string, std::function< Component::abstract *(Entity::GameObject *)> >	_ComponentAllocator;
  public:
    Factory();

  public:
    void		storeComponentAllocator(std::string, std::function<Component::abstract*(Entity::GameObject*)>);
    Component::abstract* allocateComponentByType(const std::string&, Entity::GameObject*);
    Component::abstract* allocateComponentBySerial(const std::string&, Entity::GameObject*);
  };
};

#endif
