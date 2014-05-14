#ifndef __DATAPOOL_H__
# define __DATAPOOL_H__

# include <list>

# include "Component.hh"

class DataPool{
public:
  namespace iterator{
    class Game{
    private:
      std::list< Component* >::iterator	itt;
    public:
      Game&	operator++() { ++itt; return (*this); }
      Game&	operator++(int) {++itt; return (*this); }
      bool	operator==(const Game& rhs) { return (itt == rhs.itt); }
      bool	operator!=(const Game& rhs) { return (itt != rhs.itt); }

    public:
      void DispatchEvent(EventDispatcher::)
      { (*itt)->dispatchEvent(Event); };
    };
  };

  /* Component List */
private:
  std::list< Component* >	ComponentList;
public:
  DataPool::iterator::Game		GameBegin();
  DataPool::iterator::Game		GameEnd();

  DataPool::iterator::Graphic		GraphicBegin();
  DataPool::iterator::Graphic		GraphicEnd();
};

#endif
