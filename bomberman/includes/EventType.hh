#ifndef __EVENTTYPE_H__
# define __EVENTTYPE_H__

namespace Event{

  namespace Info{
    /* #### Event Type ##### */
    enum Type{
      Keyboard,
      MouseMove,
      MouseButton,
      Clock
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
