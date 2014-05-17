#ifndef __COMPONENT_H__
# define __COMPONENT_H__

# include <iostream>
# include <string>

# include "EventDispatcher.hh"

class Component{
private:
  Component();
  ~Component();

protected:
  GraphicEngine*	_GrEngine;
private:
  EventDispatcher*		_Dispatch;
  std::vector< std::pair< Event::Info::Type, Callback* > > _CallbackArray;

public:
  Component(GraphicEngine* GrEngine, EventDispatcher* Dispatch);

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

#endif
