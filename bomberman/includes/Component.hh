#ifndef __COMPONENT_H__
# define __COMPONENT_H__

# include <list>

# include "Event.hpp"

namespace Component{

  /* ############### COLLIDER ####################### */
  class Collider{
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
    Health(Event::Dispatcher*, int life = 1);
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

  namespace Effects{ /* Glyph, Fire, Ice, Electricity, Life,  */
    typedef enum etype {Glyph, Fire, Ice, Electricity, Life} type;
    typedef enum elevel {low, med, high} level;

    struct damage{
      int damage;
      int dotDamage;
      int dotDuration;
      int dotTimed;
      double speedModifier;
      int speedModifierDuration;
      bool mute;
      int muteDuration;
    };

    class Status{
    private:
      Event::Dispatcher*	_dispatcher;

    private:
      Component::Health*	_health;
      Component::Phisix*	_phisix;

    public:
      Status(Event::Dispatcher*, Component::Health*, Component::Phisix*);

    public:
      void	interpretDamage(const Effects::damage&);

    public:
      void	applySlow(double slow, int duration);

    public:
      void	applyMute(int duration);
      bool	isMute(void);
    };
  };
};

namespace Event{
  namespace Type{
    struct PlantBomb : Event::Data{
      PlantBomb(int _x, int _y, Component::Effects::type _a, Component::Effects::type _b, Component::Effects::type _c)
	: Event::Data(Event::Info::PlantBomb, sizeof(struct PlantBomb), true),
	  x(_x), y(_y), prim(_a), second(_b), ter(_c) {}
      int x;
      int y;
      Component::Effects::type	prim;
      Component::Effects::type	second;
      Component::Effects::type	ter;
    };

    struct FireExplosion : Event::Data{
      FireExplosion(int _x, int _y, Component::Effects::level _l)
	: Event::Data(Event::Info::FireExplosion, sizeof(struct FireExplosion), false),
	  x(_x), y(_y), level(_l) {}
      int x;
      int y;
      Component::Effects::level level;
    };

    struct LifeExplosion : Event::Data{
      LifeExplosion(int _x, int _y, Component::Effects::level _l)
	: Event::Data(Event::Info::LifeExplosion, sizeof(struct LifeExplosion), false),
	  x(_x), y(_y), level(_l) {}
      int x;
      int y;
      Component::Effects::level level;
    };

    struct ElectricityExplosion : Event::Data{
      ElectricityExplosion(int _x, int _y, Component::Effects::level _l)
	: Event::Data(Event::Info::ElectricityExplosion, sizeof(struct ElectricityExplosion), false),
	  x(_x), y(_y), level(_l) {}
      int x;
      int y;
      Component::Effects::level level;
    };

    struct IceExplosion : Event::Data{
      IceExplosion(int _x, int _y, Component::Effects::level _l)
	: Event::Data(Event::Info::IceExplosion, sizeof(struct IceExplosion), false),
	  x(_x), y(_y), level(_l) {}
      int x;
      int y;
      Component::Effects::level level;
    };
  };
};

#endif
