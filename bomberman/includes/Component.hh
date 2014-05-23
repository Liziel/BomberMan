#ifndef __COMPONENT_H__
# define __COMPONENT_H__

# include <list>

# include "Entity.hh"
# include "Event.hpp"

namespace Component{

  /*  ############# ICOMPONENT ################  */
  class abstract{
  private:
    Entity::GameObject*		parent;
  public:
    abstract(Entity::GameObject* _p) : parent(_p) {}
    virtual ~abstract();

  public:
    void	dispatchEvent(Event::Data&);
    void	selfEvent(Event::Data&);
    Event::Callback::Id	attachCallback(Event::Info::Type, Event::Callback*,
				       Event::Info::Priority
				       = Event::Info::medium);

    /* serialization */
  public:
    virtual void serialization() = 0;
    virtual void setBySerial(const std::string&) = 0;
  };

};

#endif
