#ifndef __PHISIX_H__
# define __PHISIX_H__

# include "Component.hh"

namespace Component{

  /* ###################### PHISIX ############################# */
  class Phisix : public Component::Superior{
  public:
    class Vector : public Component::abstract{
    private:
      Component::Phisix	*phisix;
      
    private:
      double	x;
      double	y;

    private:
      double	speed;

    public:
      enum Direction{ Up, Down, Left, Right };
    private:
      std::array<bool, 4>	direction;

    public:
      Vector(Entity::GameObject*, Component::Phisix*);
      
    public:
      std::string serialization();
      void setBySerial(const Tokenizer&);
      static std::string	getName(void) { return ("PhisixVector"); }
    }; /*  -- vector end --  */

  private:
    double	friction;
  public:
    Phisix(Event::Dispatcher*);

  public:
    double	getFriction();
  };
};

namespace Event{
  namespace Type{

    struct selfMovement : Event::Data{
      selfMovement(Component::Phisix::Vector::Direction _d, bool _b)
	: Event::Data(Event::Info::selfMovement, sizeof(struct selfMovement), false), direction(_d), state(_b) {}
      Component::Phisix::Vector::Direction	direction;
      bool					state;
    };

# ifndef __EFFECTS_H__
    struct speedModifier : Event::Data{
      speedModifier(double _s)
	: Event::Data(Event::Info::speedModifier, sizeof(struct speedModifier), false), speed(_s) {}
      double speed;
    };
# endif

    struct freezeMovement : Event::Data{
      freezeMovement(bool _s)
	: Event::Data(Event::Info::freezeMovement, sizeof(struct freezeMovement), false), state(_s) {}
      bool	state;
    };

    struct setFriction : Event::Data{
      setFriction(double _f)
	: Event::Data(Event::Info::setFriction, sizeof(struct setFriction), false), friction((_f) ? ( 1.f / _f ) : (1.f)) {}
      double friction;
    };

# ifndef  __COLLIDER_H__
    struct RequireMovement :  Event::Data{
      RequireMovement(int _x, int _y, int vx, int vy)
	: Event::Data(Event::Info::RequireMovement, sizeof(struct RequireMovement), false),
	  x(_x), y(_y), vectorX(vx), vectorY(vy) {}
      double x;
      double y;
      double vectorX;
      double vectorY;
    };

    struct Colliding : Event::Data{
      Colliding(int _x, int _y)
	: Event::Data(Event::Info::Colliding, sizeof(struct Colliding), false),
	  endX(_x), endY(_y) {}
      double endX;
      double endY;
      double collide;
    }; 
# endif

  };
};
#endif
