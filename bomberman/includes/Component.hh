#ifndef __COMPONENT_H__
# define __COMPONENT_H__

# include <list>
# include <utility>

# include "Event.hh"

class GraphicEngine;

namespace Component{
  class GameObject{
  private:
    GameObject();
    ~GameObject();
    
  protected:
    GraphicEngine*	_GrEngine;
  private:
    Event::Dispatcher*		_Dispatch;
    std::list< std::pair< Event::Info::Type,
			  Event::Callback* > > _CallbackArray;
    
  public:
    GameObject(GraphicEngine* GrEngine, Event::Dispatcher* Dispatch);
    
  public:
    Event::Callback::Id	addCallback(Event::Info::Type, Event::Callback*,
				    Event::Info::Priority
				    = Event::Info::medium);
    void	unsetCallback(Event::Callback*);
    void	unsetCallback(Event::Callback::Id);
    
  public:
    void	enable(void);
    void	disable(void);
  };
};

#endif
