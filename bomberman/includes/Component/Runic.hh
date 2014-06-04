#ifndef __RUNIC_H__
# define __RUNIC_H__

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

namespace Component{
  class Runic : public Component::abstract{
  private:
    Event::Time			runeDuration;
    int				attachedElement;
    int				attachableElement;
    Component::Effects::type	element1;
    Component::Effects::type	element2;
    
  public:
    Runic(Entity::GameObject*);
  public:
    std::string serialization();
    void	setBySerial(const Tokenizer&);
  };
};

namespace Event{
  namespace Type{

    struct SocketGlyph : Event::Data{
      SocketGlyph()
	: Event::Data(Event::Info::SocketGlyph, sizeof(struct SocketGlyph), false) {}
    };

# ifndef __BLOC_H__
    struct EnableGlyph : Event::Data{
      EnableGlyph()
	: Event::Data(Event::Info::EnableGlyph, sizeof(struct EnableGlyph), false) {}

    };

# endif

# ifndef __EXPLODE_H__
    struct GlyphExplosion : Event::Data{
      GlyphExplosion(int _x, int _y, Component::Effects::level _l)
	: Event::Data(Event::Info::GlyphExplosion, sizeof(struct GlyphExplosion), false),
	  x(_x), y(_y), level(_l) {}
      int x;
      int y;
      Component::Effects::level level;
    };
# endif
  };
};

#endif
