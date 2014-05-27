#ifndef __EXPLODE_H__
# define __EXPLODE_H__

# include "Component.h"

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
  class Explode : public Component::abstract{
  private:
    std::array<Component::Effects::type, 3>	elements;

  public:
    Explode(Entity::GameObject*);
  };
};

namespace Event{
  namespace Type{

# ifndef __PLANTBOMB_H__
    struct PlantBomb : Event::Data{
      PlantBomb(Component::Effects::type _p,
		Component::Effects::type _s,
		Component::Effects::type _t)
	: Event::Data(Event::Info::plantBomb, sizeof(struct PlantBomb), true),
	  prim(_p), second(_s), ter(_t) {}
      Component::Effects::type prim;
      Component::Effects::type second;
      Component::Effects::type ter;
    };
# endif

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
