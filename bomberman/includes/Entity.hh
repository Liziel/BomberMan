#ifndef __ENTITY_H__
# define __ENTITY_H__

# include <list>
# include <utility>

# include "Event.hpp"

class GraphicEngine;

namespace Entity{
  class GameObject{
  public:
    GameObject();
    
  protected:
    GraphicEngine*		_GrEngine;
    Event::Dispatcher*		_Dispatch;
  private:
    std::list< std::pair< Event::Info::Type,
			  Event::Callback* > > _CallbackArray;
    
  public:
    GameObject(GraphicEngine* GrEngine, Event::Dispatcher* Dispatch);
    
  public:
    ~GameObject();
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
