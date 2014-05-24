#ifndef __COMPONENT_H__
# define __COMPONENT_H__

# include <list>
# include <fstream>
# include <exception>

# include "Tokenizer.hpp"
# include "Entity.hh"
# include "Event.hpp"

namespace Component{

  /*  ############# abstract ################  */
  class abstract{
  private:
    Entity::GameObject*		parent;
  protected:
    abstract(Entity::GameObject* _p) : parent(_p) {}
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
      /* superior added at construct or with setter? */
    };
    /* serialization */

  protected:
    Event::Dispatcher*	dispatcher;
  public:
    Superior(Event::Dispatcher* _d)
      : dispatcher(_d) {}

  public:
    virtual std::string serialization() = 0;
    virtual void	setBySerial(const Tokenizer&) = 0;
  };

  /* ########## Factory ########## */
  class Factory{
  public:
    Factory();

  public:
    Component::abstract* allocateComponentByType(const std::string&, Entity::GameObject*);
    Component::abstract* allocateComponentBySerial(const std::string&, Entity::GameObject*);
  };
};

#endif
