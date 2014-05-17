#ifndef __EVENTTYPE_H__
# define __EVENTTYPE_H__

namespace Event{
  namespace Info{
    /* #### Event Type ##### */
    enum Type{
      Keyboard,
      MouseMove,
      MouseButton
    };
    /* ###### Event Priority ##### */
    enum Priority{
      low, medium, high
    };
  };
};

#endif
