#ifndef __COMPONENT_H__
# define __COMPONENT_H__

# include <iostream>
# include <string>

# include "EventDispatcher.hh"

class Component{
private:
  Component();

protected:
  GraphicEngine&	_GrEngine;
  EventDispatcher&	_Dispatch;

public:
  Component(GraphicEngine& GrEngine, EventDispatcher& Dispatch)
    : _GrEngine(GrEngine), _Dispatch(Dispatch) {}

  virtual void refresh(void) = 0;
  virtual void draw(void) = 0;
};

#endif
