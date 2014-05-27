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
    Event::Time					isMuted;
    unsigned int				stackedSpells;
    std::array<Component::Effects::type, 3>	spellArray;

  public:
    BombCast(Entity::GameObject* _p);

    std::string serialization();
    void	setBySerial(const Tokenizer&);
  };
};

namespace Event{
  namespace Type{
# ifndef __EXPLODE_H__
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

# ifndef __PLAYER_UI_H__
# endif

  };
};

#endif
