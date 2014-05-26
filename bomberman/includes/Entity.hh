#ifndef __ENTITY_H__
# define __ENTITY_H__

# include <list>
# include <utility>

# include "Event.hpp"

class GraphicEngine;

namespace Component{
  class abstract;
  class Factory;
};

namespace Entity{
  class GameObject{
  public:
    GameObject();
    
  private:
    GraphicEngine*		_GrEngine;
    Event::Dispatcher*		_Dispatch;
    Component::Factory*		_factory;
  private:
    std::list< std::pair< Event::Info::Type,
			  Event::Callback* > > _CallbackArray;
    
  public:
    GameObject(GraphicEngine* GrEngine, Event::Dispatcher* Dispatch, Component::Factory*);
    
  private:
    std::vector<Component::abstract*>	abstractList;
  public:
    void	attachComponent(Component::abstract*);
    std::string	serialization();

  public:
    ~GameObject();
    Event::Callback::Id	addCallback(Event::Info::Type, Event::Callback*,
				    Event::Info::Priority
				    = Event::Info::medium);
    void	dispatchSelf(Event::Data&);
    void	dispatchAll(Event::Data&);

    void	unsetCallback(Event::Callback*);
    void	unsetCallback(Event::Callback::Id);
    
  public:
    void	enable(void);
    void	disable(void);

  public:
    void	getPosition(double& x, double& y) const;
    void	setPosition(double x, double y);

  public:
    virtual int	getLifeAmount(void) = 0;
  };

};

#endif
