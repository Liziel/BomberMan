#ifndef __COMPONENT_H__
# define __COMPONENT_H__

namespace Component{
  class Collider{
  public:
    class Object{
    private:
      Id	id;
      int	x;
      int	y;
    public:
      typedef int Id;
      Object(Id, int x, int y);

    public:
      Id	getId(void);
      void	setPosition(int x, int y);

    public:
      bool	doCollide(int x, int y);
    };
  private:
    Event::Dispatcher*	_dispatcher;
    Object::Id		_idGen;
  public:
    Collider(Event::Dispatcher*);

  private:
    std::list< Object* >	collideList;
  public:
    Object::Id	addColliderObject(int x, int y);
    void	moveColliderObject(Object::Id, int x, int y);

  public:
    bool	operator()(int x, int y, Object::Id ignore = -1);
  };

  class Phisix{
  public:
    class Vector{
    public:
      Vector(Phisix*);

    public:
      enum Direction{ Up, Down, Left, Right};
      void	modifyMovement(enum Direction, bool mask);
      void	modifySpeed(double speed);
      void	setSpeed(double speed);
      void	authorizeMovement(bool);

    public:
      void	move(void);
      void	getPosition(int& x, int& y);
    };

  public:
    Phisix(Event::Dispatcher*, const Collider&);

  public:
    void	modifyFisix(/* ??? */);
  };
};

#endif
