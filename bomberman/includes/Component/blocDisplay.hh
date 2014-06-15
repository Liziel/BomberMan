#ifndef __GROUNDDISPLAY_H__
# define __GROUNDDISPLAY_H__

# include "Component.hh"

# include "cubeVertex.hh"
# include "bombAnimated.hh"
# include "bookAnimated.hh"

# define __GROUNDTEXTURE "./textures/ground/lava.tga"

# define __GROUNDFIRETEXTURE "./textures/effects/fire.tga"
# define __GROUNDHEALTHTEXTURE "./textures/effects/health.tga"
# define __GROUNDICETEXTURE "./textures/effects/ice.tga"
# define __GROUNDLIGHTTEXTURE "./textures/effects/light.tga"

# define __GLYPHEDTEXTURE "./textures/ground/glyphe.tga"
# define __INDESTEXTURE "./textures/diamond/Diamond.tga"
# define __BOOKSHELFTEXTURE "./textures/bookshelf/bookshelf.tga"

# define EFFECTS_TIME	5

namespace Component{
  class groundDisplay : public Component::abstract{
  private:
    object3d::cubeVertex	*cube;
    object3d::cubeVertex	*glyphed;
    bool			_glyphed;

  private:
    object3d::cubeVertex	*cubeFire;
    object3d::cubeVertex	*cubeIce;
    object3d::cubeVertex	*cubeLight;
    object3d::cubeVertex	*cubeHealth;
    object3d::cubeVertex	*cubeEffects;
    Event::Time			effects;

  private:
    Engine::Graphic*		engine;

  public:
    groundDisplay(Entity::GameObject*, Engine::Graphic*);
    ~groundDisplay();

  public:
    std::string serialization() { return (""); }
    void	setBySerial(const Tokenizer&) {}
  };

  class indestructibleDisplay : public Component::abstract {
  private:
    object3d::cubeVertex	*cube;
    Engine::Graphic*		engine;

  public:
    indestructibleDisplay(Entity::GameObject*, Engine::Graphic*);
    ~indestructibleDisplay();

  public:
    std::string serialization() { return (""); }
    void	setBySerial(const Tokenizer&) {}
  };

  class bookshelfDisplay : public Component::abstract {
  private:
    object3d::cubeVertex	*cube;
    Engine::Graphic*		engine;

  public:
    bookshelfDisplay(Entity::GameObject*, Engine::Graphic*);
    ~bookshelfDisplay();

  public:
    std::string serialization() { return (""); }
    void	setBySerial(const Tokenizer&) {}
  };

  class playerDisplay : public Component::abstract {
  private:
    object3d::animatedVertex	*ziggs;
    Engine::Graphic*		engine;

  private:
    double x,y;
    std::array<bool, 4>	_direction;
  public:
    playerDisplay(Entity::GameObject*, Engine::Graphic*);
    ~playerDisplay();

  public:
    std::string serialization() { return (""); }
    void	setBySerial(const Tokenizer&) {}
  };

  class bombDisplay : public Component::abstract {
  private:
    object3d::animatedVertex	*bomb;
    Engine::Graphic*		engine;

  public:
    bombDisplay(Entity::GameObject*, Engine::Graphic*);
    ~bombDisplay();

  public:
    std::string serialization() { return (""); }
    void	setBySerial(const Tokenizer&);
  };

  class bonusDisplay : public Component::abstract {
  private:
    object3d::animatedVertex	*book;
    Engine::Graphic*		engine;

  public:
    bonusDisplay(Entity::GameObject*, Engine::Graphic*);
    ~bonusDisplay();

  public:
    std::string serialization() { return (""); }
    void	setBySerial(const Tokenizer&) {}
  };
};

# ifndef __EFFECTS_H__
#  ifndef __PLANTBOMB_H__
#   ifndef __EXPLODE_H__
namespace Component{
  namespace Effects{
      typedef enum etype {Glyph, Fire, Ice, Electricity, Life} type;
      typedef enum elevel {low, med, high} level;
  };
};
#   endif
#  endif
# endif

namespace Component{
# ifndef __PHISIX_H__
#  ifndef __ARENA_H__
  namespace Phisix{
    namespace Vector{
      enum Direction {Up, Down, Right, Left};
    };
  };
#  endif
# endif
};

namespace Event{
  namespace Type{
# ifndef __PHISIX_H__
    struct selfMovement : Event::Data{
      selfMovement(Component::Phisix::Vector::Direction _d, bool _b)
	: Event::Data(Event::Info::selfMovement, sizeof(struct selfMovement), false), direction(_d), state(_b) {}
      Component::Phisix::Vector::Direction	direction;
      bool					state;
    };
# endif

# ifndef __EXPLODE_H__
#  ifndef __EFFECTS_H__
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

# ifndef __BONUS_H__
    struct TakeBonus : Event::Data{
      TakeBonus(double _x, double _y)
	: Event::Data(Event::Info::TakeBonus, sizeof(struct TakeBonus), true),
	  x(_x), y(_y) {}
      double x;
      double y;
    };
# endif

  };
};

#endif
