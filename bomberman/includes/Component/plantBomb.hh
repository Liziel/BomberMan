#ifndef __PLANTBOMB_H__
# define __PLANTBOMB_H__

namespace Component{
  class BombCast : public Component::abstract{
  public:
    BombCast();

  };
};

# ifndef __EFFECTS_H__
namespace Component{
  namespace Effects{
      typedef enum etype {Glyph, Fire, Ice, Electricity, Life} type;
      typedef enum elevel {low, med, high} level;
  };
};
# endif

namespace Event{
  namespace Type{
    struct selfPlantBomb : Event::Data{
      selfPlantBomb()
	: Event::Data(Event::Info::selfPlantBomb, sizeof(struct plantBomb), false)
      {}
    };

    struct PlantBomb : Event::Data{
      plantBomb(Component::Effects::type _p,
		Component::Effects::type _s,
		Component::Effects::type _t)
	: Event::Data(Event::Info::plantBomb, sizeof(struct plantBomb), true),
	  prim(_p), second(_s), ter(_t) {}
      Component::Effects::type prim;
      Component::Effects::type second;
      Component::Effects::type ter;
    };

    struct addElement : Event::Data{
      addElement(Component::Effects::type _e)
	: Event::Data(Event::Info::addElement, sizeof(struct addElement), false),
	  element(_e) {}
      Component::Effects::type element;
    };
  };
};

#endif
