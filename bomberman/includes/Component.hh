#ifndef __COMPONENT_H__
# define __COMPONENT_H__

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
public:
  class Definition{

  public:
    Dimension::Type	GetType();
    t3d			GetReference();
    t3d			GetPosition();
    t3d			GetSize();
  };

};

#endif
