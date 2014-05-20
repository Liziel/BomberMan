#ifndef __EVENTTYPE_H__
# define __EVENTTYPE_H__

namespace Event{

  namespace Info{
    /* #### Event Type ##### */
    enum Type{
      Network = -1,
      Keyboard,
      MouseMove,
      MouseButton,
      PlayerMove, DeniedMove,
      DamageFixed, PlantBomb,
      CollidableObjectMovement,
      Clock, Refresh,
    };
  };

  namespace Info{
    /* ###### Event Priority ##### */
    enum Priority{
      low, medium, high
    };
  };
};

#endif
