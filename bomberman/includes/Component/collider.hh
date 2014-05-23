#ifndef __COLLIDER_H__
# define __COLLIDER_H__

# include "Component.hh" 

namespace Component {

  /* ############### COLLIDER ####################### */
  class Collider : public Component::abstract{
  public:
    class Object{
    public:
      typedef int Id;
      typedef enum eType { Movable, Static, None } type;
    private:
      Object::Id	id;
      Object::type	t;
      int		x;
      int		y;
    public:
      Object(Object::Id, int x, int y, Object::type);

    public:
      Id	getId(void) const;
      type	getType(void) const;
      void	setPosition(int x, int y);

    public:
      bool	doCollide(int x, int y) const;
    };

  private:
    Event::Dispatcher*_dispatcher;
    Object::Id	_idGen;

  public:
    Collider(Event::Dispatcher*);

  private:
    std::list< Object* >collideList;
  public:
    Object::Id	addColliderObject(int x, int y, Object::type type = Object::Static);
    void	moveColliderObject(Object::Id, int x, int y);

  public:
    bool	operator()(int x, int y, Object::type _ignore = Object::None, Object::Id ignore = -1) const;
  };
};


#endif
