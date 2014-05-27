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
    void	EXPLODE		(void);

  public:
    std::string serialization();
    void	setBySerial(const Tokenizer&);
   };
};

namespace Event{
  namespace Type{

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
