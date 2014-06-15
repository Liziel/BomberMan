#ifndef __EFFECTS_H__
# define __EFFECTS_H__

# include <list>
# include "Component.hh"

namespace Component{
  namespace Effects{ /* Glyph, Fire, Ice, Electricity, Life,  */
# ifndef __PLANTBOMB_H__
      typedef enum etype {Glyph, Fire, Ice, Electricity, Life} type;
      typedef enum elevel {low, med, high} level;
# endif
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
    public:
      class SpeedModifier{
      private:
	double	speedModifier;
	int	clock;
	Status* status;
      public:
	std::string serialization();
	SpeedModifier(double, int, Status*);

      public:
        bool	isOver(double&);
      };
    private:
      std::list<SpeedModifier*> speedVect; 
    public:
      Status(Entity::GameObject*);

    private:
      Event::Time	isOnFire;
      Event::Time	isOnIce;
      Event::Time	isOnElectricity;
      Event::Time	isOnLife;
    public:
      void	interpretDamage(const Effects::damage&);

    public:
      void	applySlow(double slow, int duration);

    public:
      void	applyMute(int duration);

    public:
      std::string speedSerialization(std::list<SpeedModifier*>::iterator);
      std::string serialization();
      void	setBySerial(const Tokenizer&);
    };
  };
};

namespace Event{
  namespace Type{

# ifndef __PHISIX_H__
    struct speedModifier : Event::Data{
      speedModifier(double _s)
	: Event::Data(Event::Info::speedModifier, sizeof(struct speedModifier), false), speed(_s) {}
      double speed;
    };
# endif

# ifndef __PLANTBOMB_H__
    struct isMute : Event::Data{
      isMute(Event::Time _t)
	: Event::Data(Event::Info::isMute, sizeof(struct isMute), true),
	  time(_t) {}
      Event::Time	time;
    };
# endif

# ifndef __HEALTH_H__
    struct PlaceDot : Event::Data{
    PlaceDot(int _d, unsigned int _dd, unsigned _w)
	: Event::Data(Event::Info::PlaceDot, sizeof(struct PlaceDot), false),
	  damage(_d), duration(_dd), warmUp(_w) {}
      int	damage;
      int	duration;
      int	warmUp;
    };

    struct lifeLoss : Event::Data{
      lifeLoss(int _a)
	: Event::Data(Event::Info::lifeLoss, sizeof(struct lifeLoss), false),
	  amount(_a) {}
      int amount;
    };

    struct lifeGain : Event::Data{
      lifeGain(int _a)
	: Event::Data(Event::Info::lifeGain, sizeof(struct lifeLoss), false),
	  amount(_a) {}
      int amount;
    };
# endif

# ifndef __EXPLODE_H__
    struct FireExplosion : Event::Data{
      FireExplosion(double _x, double _y, Component::Effects::level _l)
	: Event::Data(Event::Info::FireExplosion, sizeof(struct FireExplosion), false),
	  x(_x), y(_y), level(_l) {}
      double x;
      double y;
      Component::Effects::level level;
    };

    struct LifeExplosion : Event::Data{
      LifeExplosion(double _x, double _y, Component::Effects::level _l)
	: Event::Data(Event::Info::LifeExplosion, sizeof(struct LifeExplosion), false),
	  x(_x), y(_y), level(_l) {}
      double x;
      double y;
      Component::Effects::level level;
    };

    struct ElectricityExplosion : Event::Data{
      ElectricityExplosion(double _x, double _y, Component::Effects::level _l)
	: Event::Data(Event::Info::ElectricityExplosion, sizeof(struct ElectricityExplosion), false),
	  x(_x), y(_y), level(_l) {}
      double x;
      double y;
      Component::Effects::level level;
    };

    struct IceExplosion : Event::Data{
      IceExplosion(double _x, double _y, Component::Effects::level _l)
	: Event::Data(Event::Info::IceExplosion, sizeof(struct IceExplosion), false),
	  x(_x), y(_y), level(_l) {}
      double x;
      double y;
      Component::Effects::level level;
    };
# endif

# ifndef __SORCERER_DISPLAY_H__
    struct isOnFire : Event::Data{
      isOnFire(bool _s)
	: Event::Data(Event::Info::isOnFire, sizeof(struct isOnFire), true),
	  state(_s) {}
      bool state;
    };

    struct isOnElectricity : Event::Data{
      isOnElectricity(bool _s)
	: Event::Data(Event::Info::isOnElectricity, sizeof(struct isOnElectricity), true),
	  state(_s) {}
      bool state;
    };

    struct isOnIce : Event::Data{
      isOnIce(bool _s)
	: Event::Data(Event::Info::isOnIce, sizeof(struct isOnIce), true),
	  state(_s) {}
      bool state;
    };

    struct isOnLife : Event::Data{
      isOnLife(bool _s)
	: Event::Data(Event::Info::isOnLife, sizeof(struct isOnLife), true),
	  state(_s) {}
      bool state;
    };
# endif
  };
};

#endif
