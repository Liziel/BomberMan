#ifndef __BOMBANI_H__
# define __BOMBANI_H__

#include "animatedVertex.hh"

namespace object3d{
  class bombGlyph : public object3d::animatedVertex{
  public:
    bombGlyph();
  };
  class bombHealth : public object3d::animatedVertex{
  public:
    bombHealth();
  };
  class bombFeu : public object3d::animatedVertex{
  public:
    bombFeu();
  };
  class bombThunder : public object3d::animatedVertex{
  public:
    bombThunder();
  };
  class bombGlace : public object3d::animatedVertex{
  public:
    bombGlace();
  };
};


#endif
