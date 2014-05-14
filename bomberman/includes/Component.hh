#ifndef __COMPONENT_H__
# define __COMPONENT_H__

#include <iostream>
#include <string>
//#include "EventDispatcher.hh"

/* Interface Component:
 * 2 sided utility:
 *  -> Game
 *   - Receive Event
 *   - Access to EventDispatcher
 *  -> Graphic
 *   - am i visible?
 *   - renvoie la Nested Definition
 *     : 2d/3d
 *     : Reference (string)
 *     : Position and Size (t3d);
 # Done
 */

typedef struct s_3d{float x,y,z;} t3d; 

namespace Dimension
{
enum	Type
  {
    TWO_DIM = 0,
    THREE_DIM
  };
}

class Component{
private:
    EventDispatcher	*Dispatcher;

public:
  void			receiveEvent(EventDispatcher::Event);
  bool			amIVisible();
  
  class Definition{
  public:
    Dimension::Type	getType() const;
    t3d			getReference(const std::string &) const;
    t3d			getPosition(t3d) const;
    t3d			getSize() const;
  };

};

#endif
