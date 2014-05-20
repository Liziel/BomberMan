#ifndef __COMPONENT_H__
# define __COMPONENT_H__

namespace Component{
  class Collider{
  public:
    class Object{
    public:
      typedef unsigned int Id;
    };

  public:
    Collider(Event::Dispatcher*);

  private:
    std::list< Object* >	collideList;
  public:
    Object::Id	addColliderObject(int x, int y);
    void	moveColliderObject(Object::Id, int x, int y);

  public:
    bool	operator()(int x, int y);
  };

  class Phisix{
  public:
    class Vector{
    public:
      Vector(Phisix*);

    private:
      double	speed;
      bool	movementDirection[4];
      bool	authorization;
      int	positionX;
      int	positionY;
      Phisix	*myPhisix;

    public:
      enum Direction{ Up, Down, Left, Right };
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
