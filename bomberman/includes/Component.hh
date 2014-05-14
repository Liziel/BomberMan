#ifndef __COMPONENT_H__
# define __COMPONENT_H__

# include <iostream>
# include <string>

# include "EventDispatcher.hh"

typedef struct s_3d{float x,y,z;} t3d;

class IComponent{
public:
  struct Definition{//may struct be better?
    enum	type{ TWO_DIM, THREE_DIM }	type;
    std::string*				reference;
    t3d						position;
    t3d						size;
  };

public:
  void		setEventDispatcher(EventDispatcher*) = 0;
  void		dispatchEvent(const EventDispatcher::Event) = 0;

public:
  bool		isVisible() = 0;
  const Definition&	getDefinitions(void) const = 0;
};

#endif
