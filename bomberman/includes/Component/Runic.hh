#ifndef __RUNIC_H__
# define __RUNIC_H__

# include "Component.hh"

# ifndef __EFFECTS_H__
#  ifndef __PLANTBOMB_H__
namespace Component{
  namespace Effects{
      typedef enum etype {Glyph, Fire, Ice, Electricity, Life} type;
      typedef enum elevel {low, med, high} level;
  };
};
#  endif
# endif

namespace Component{
  class Runic : public Component::abstract{
  private:
    bool			runable;

    Event::Time			runeDuration;
    Event::Time			runeCooldown;
    Event::Time			runeBurning;

    double			x;
    double			y;

    int				attachedElement;
    int				attachableElement;

    Component::Effects::type	element1;
    Component::Effects::type	element2;
    
  public:
    Runic(Entity::GameObject*, bool = false);
    void	dispatchElement(Component::Effects::type);

  public:
    std::string serialization();
    void	setBySerial(const Tokenizer&);
  };
};

namespace Event{
  namespace Type{

# ifndef __ARENA_H__
#  ifndef __EXPLODE_H__
    struct Explosion : Event::Data{
      Explosion(int _x, int _y)
	: Event::Data(Event::Info::Explosion, sizeof(struct Explosion), false), x(_x), y(_y) {}
      int x;
      int y;
    };
#  endif
# endif

# ifndef __BLOCDISPLAY_H__
    struct SocketGlyph : Event::Data{
      SocketGlyph()
	: Event::Data(Event::Info::SocketGlyph, sizeof(struct SocketGlyph), false) {}
    };

    struct extinctGlyph : Event::Data{
      extinctGlyph()
	: Event::Data(Event::Info::extinctGlyph, sizeof(struct extinctGlyph), false) {}
    };
# endif

# ifndef __ARENA_H__
    struct EnableGlyph : Event::Data{
      EnableGlyph()
	: Event::Data(Event::Info::EnableGlyph, sizeof(struct EnableGlyph), false) {}
    };
# endif

# ifndef __EXPLODE_H__
#  ifndef __EFFECTS_H__
    struct GlyphExplosion : Event::Data{
      GlyphExplosion(double _x, double _y, Component::Effects::level _l)
	: Event::Data(Event::Info::GlyphExplosion, sizeof(struct GlyphExplosion), false),
	  x(_x), y(_y), level(_l) {}
      double x;
      double y;
      Component::Effects::level level;
    };

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
#  endif
# endif
  };
};

#endif
