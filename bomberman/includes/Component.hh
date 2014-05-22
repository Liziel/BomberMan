#ifndef __COMPONENT_H__
# define __COMPONENT_H__

# include <list>

# include "Event.hpp"
# include "EventList.hh"
namespace Component{

  /* ############### COLLIDER ####################### */
  class Collider{
  public:
    class Object{
    public:
      typedef int Id;
    private:
      Object::Id	id;
      int		x;
      int		y;
    public:
      Object(Object::Id, int x, int y);

    public:
      Id	getId(void) const;
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
    Object::Id	addColliderObject(int x, int y);
    void	moveColliderObject(Object::Id, int x, int y);

  public:
    bool	operator()(int x, int y, Object::Id ignore = -1) const;
  };

  /* ###################### PHISIX ############################# */
  class Phisix{
  public:
    class Vector{
    public:
      Vector(Phisix*, int, int, double);

    private:
      double	speed;
      bool	movementDirection[4];

    private:
      bool	authorization;
      int	positionX;
      int	positionY;

    private:
      Phisix	*myPhisix;      

    public:
      enum Direction{ Up, Down, Left, Right };
      void	modifyMovement(enum Direction, bool mask);
      void	modifySpeed(double speed);
      void	setSpeed(double speed);
      void	authorizeMovement(bool);

    public:
      void	move(void);
      void	getPosition(int& x, int& y) const;
    }; /*  -- vector end --  */

  private:
    Event::Dispatcher*	DispatchCopy;
    const Collider&	ColliderCopy;
    double		globalFriction;
  public:
    Phisix(Event::Dispatcher*, const Collider&);

  public:
    void		setGlobalFriction(double);
    double		getGlobalFriction(void) const;
    const Collider&	getCollider(void) const;
  };

  /* ################ Health ############## */
  class Health{
  public:
    class Dot {
    private:
      int	damage;
      int	clockLife;
      int	rTime;
      int	aTime;

    public:
      Dot(int damage, int clockLife, unsigned int timeBeetween = 0);

    public:
      int	getDamage(void);
      bool	isOver(void);
    };
  private:
    Event::Callback*	_callback;
    Event::Dispatcher*	dispatcher;
    int			maxLife;
    int			life;
    std::list<Dot*>	dotList;
    bool		_invincible;

  public:
    Health(Event::Dispatcher*, int life);
    ~Health();

  private:
    void	actualize();

  public:
    int		operator+(int n);
    int		operator-(int n);

  public:
    void	revive(unsigned int reviveLife);
    bool	isDead(void);

  public:
    void	addDot(Health::Dot*);

  public:
    bool	isInvicible(void);
    void	invincible(bool);
  };
};

#endif
