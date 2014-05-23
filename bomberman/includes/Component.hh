#ifndef __COMPONENT_H__
# define __COMPONENT_H__

# include <list>

# include "Tokenizer.hpp"
# include "Entity.hh"
# include "Event.hpp"

namespace Component{

  /*  ############# ICOMPONENT ################  */
  class abstract{
  private:
    Entity::GameObject*		parent;
  protected:
    abstract(Entity::GameObject* _p) : parent(_p) {}
    virtual ~abstract();

  protected:
    void	dispatchAll(Event::Data&);
    void	dispatchSelf(Event::Data&);
    Event::Callback::Id	attachCallback(Event::Info::Type, Event::Callback*,
				       Event::Info::Priority
				       = Event::Info::medium);

    /* serialization */
  public:
    virtual std::string serialization() = 0;
    virtual void setBySerial(const std::string&) = 0;
  };


  /* ########## Pool ############# */
  class Pool{};

  /* ########## Factory ########## */
  class Factory{
  public:
    Factory();

  public:
    allocateComponentByType(const std::string&, Entity::GameObject*);
    allocateComponentBySerial(const std::string&, Entity::GameObject);
  };
};

#endif
