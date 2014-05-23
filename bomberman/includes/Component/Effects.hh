#ifndef __PHISIX_H__
# define __PHISIX_H__

# include "Component.hh"

namespace Component{
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

    class Status : public Component::abstract{
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
