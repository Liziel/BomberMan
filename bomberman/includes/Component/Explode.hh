#ifndef __EXPLODE_H__
# define __EXPLODE_H__

# include "Component.hh"

# ifndef __EFFECTS_H__
# ifndef __PLANTBOMB_H__
namespace Component{
  namespace Effects{
      typedef enum etype {Glyph, Fire, Ice, Electricity, Life} type;
      typedef enum elevel {low, med, high} level;
  };
};
# endif
# endif


namespace  Component{
  namespace Explosion{
    
  };
  class Explode : public Component::abstract{
  private:
    std::array<Component::Effects::type, 3>	elements;
    Event::Time					untilBOOM;
  public:
    Explode(Entity::GameObject*);

  public:
    void	EXPLODE		(Entity::GameObject*);
    void	dispatch	(int x, int y);
    double	getSpread	(Component::Effects::type);
  public:
    std::string serialization();
    void	setBySerial(const Tokenizer&);
   };
};

namespace Event{
  namespace Type{

    struct Explosion : Event::Data{
      Explosion(int _x, int _y)
	: Event::Data(Event::Info::Explosion, sizeof(struct Explosion), false), x(_x), y(_y) {}
      int x;
      int y;
    };

# ifndef __COLLIDER_H__
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
      Colliding(double _x, double _y, double _f)
	: Event::Data(Event::Info::Colliding, sizeof(struct Colliding), false),
	  endX(_x), endY(_y), collide(_f) {}
      double endX;
      double endY;
      double collide;
    }; 
# endif

    struct GlyphExplosion : Event::Data{
      GlyphExplosion(int _x, int _y, Component::Effects::level _l)
	: Event::Data(Event::Info::GlyphExplosion, sizeof(struct GlyphExplosion), false),
	  x(_x), y(_y), level(_l) {}
      int x;
      int y;
      Component::Effects::level level;
    };

# ifndef __EFFECTS_H__
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
# endif
  };
};
#endif
