#ifndef __PLANTBOMB_H__
# define __PLANTBOMB_H__

#include "Component.hh"

# ifndef __EFFECTS_H__
# ifndef __EXPLODE_H__
namespace Component{
  namespace Effects{
      typedef enum etype {Glyph, Fire, Ice, Electricity, Life} type;
      typedef enum elevel {low, med, high} level;
  };
};
# endif
# endif

namespace Component{
  class BombCast : public Component::abstract{
  private:
    struct Cooldown { enum _c{value = 35}; };
  private:
    Event::Time					isMuted;

  private:
    unsigned int				stackedSpells;
    std::array<Component::Effects::type, 3>	spellArray;

  private:
    unsigned int				maxBomb;
    unsigned int				stackedBomb;
    Event::Time					BombReloading;
  public:
    BombCast(Entity::GameObject* _p);

    std::string serialization();
    void	setBySerial(const Tokenizer&);
  };
};

namespace Event{
  namespace Type{

# ifndef __PLAYER_UI_H__
    struct BombReloaded : Event::Data {
      BombReloaded()
	: Event::Data(Event::Info::BombReloaded, sizeof(struct BombReloaded), false) {}
    };

    struct BombReleased : Event::Data {
      BombReleased()
	: Event::Data(Event::Info::BombReleased, sizeof(struct BombReleased), false) {}
    };

#  ifndef __BONUS_H__
    struct IncreaseBombStack : Event::Data{
      IncreaseBombStack()
	: Event::Data(Event::Info::IncreaseBombStack, sizeof(struct IncreaseBombStack), false) {}
    };
#  endif
# endif

# ifndef __ARENA_H__
    struct PlantBomb : Event::Data{
      PlantBomb(double _x, double _y,
		Component::Effects::type _p,
		Component::Effects::type _s,
		Component::Effects::type _t)
	: Event::Data(Event::Info::plantBomb, sizeof(struct PlantBomb), true),
	  x(_x), y(_y), prim(_p), second(_s), ter(_t) {}
      double x;
      double y;
      Component::Effects::type prim;
      Component::Effects::type second;
      Component::Effects::type ter;
    };
# endif

# ifndef __PHISIX_H__
    struct speedModifier : Event::Data{
      speedModifier(double _s)
	: Event::Data(Event::Info::speedModifier, sizeof(struct speedModifier), false), speed(_s) {}
      double speed;
    };
# endif


# ifndef __EFFECTS_H__
    struct isMute : Event::Data{
      isMute(Event::Time _t)
	: Event::Data(Event::Info::isMute, sizeof(struct isMute), true),
	  time(_t) {}
      Event::Time	time;
    };
# endif

# ifndef __ARENA_H__
    struct selfPlantBomb : Event::Data{
      selfPlantBomb()
	: Event::Data(Event::Info::selfPlantBomb, sizeof(struct selfPlantBomb), false)
      {}
    };

    struct addElement : Event::Data{
      addElement(Component::Effects::type _e)
	: Event::Data(Event::Info::addElement, sizeof(struct addElement), false),
	  element(_e) {}
      Component::Effects::type element;
    };

# endif

  };
};

#endif
