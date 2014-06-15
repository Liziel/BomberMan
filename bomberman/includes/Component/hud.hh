#ifndef __HUD_H__
# define __HUD_H__

# include "Component.hh"
# include "GraphicEngine.hh"
# include "planVertex.hh"
# include "Event.hpp"
# include "EventType.hh"

namespace Component{
  class HudElement {
  public:
    std::string _texture;
    int _sizeX;
    int _sizeY;
    int _posX;
    int _posY;
    Engine::Graphic* _graphic;
    object3d::AObject* _gp;
    HudElement(Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture);
    ~HudElement();
    void resize(int sizeX, int sizeY, int posX, int posY, const std::string& texture);
  };

  class Hud : public Component::abstract{
  protected:
    bool _validBackground;
    std::string _texture;
    int _sizeX;
    int _sizeY;
    int _posX;
    int _posY;
    std::list<HudElement*> _elems;
    object3d::AObject* _gp;
    Engine::Graphic* _graphic;

  private:
    HudElement *life;
    HudElement *mana;
    HudElement *inv;
    HudElement *mute;
    HudElement *lock;

  private:
    Event::Time invi;
    int		nbBomb;
    int		nblock;

  private:
    int		idElem;
    std::array<HudElement*, 3> elem;
    int		idPlayer;
    int		nbPlayer;

  public:
    Hud(Entity::GameObject* _p, Engine::Graphic* g);
    Hud(Entity::GameObject* _p, Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture);
    ~Hud();
    void addElement(Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture);
    void draw();
  public:
    std::string serialization() { return (""); }
    void	setBySerial(const Tokenizer&) {}
  };
};

# ifndef __EFFECTS_H__
# ifndef __EXPLODE_H__
# ifndef __PLANTBOMB_H__
namespace Component{
  namespace Effects{
      typedef enum etype {Glyph, Fire, Ice, Electricity, Life} type;
      typedef enum elevel {low, med, high} level;
  };
};
# endif
# endif
# endif

namespace Event{
  namespace Type{
# ifndef __PLANTBOMB_H__
    struct changeMute : Event::Data{
      changeMute(bool _m)
	: Event::Data(Event::Info::changeMute, sizeof(struct changeMute), false),
	  mute(_m) {}
      bool mute;
    };

#  ifndef __ARENA_H__
    struct addElement : Event::Data{
      addElement(Component::Effects::type _e)
	: Event::Data(Event::Info::addElement, sizeof(struct addElement), false),
	  element(_e) {}
      Component::Effects::type element;
    };
#  endif
# endif

# ifndef __HEALTH_H__
#  ifndef __BONUS_H__
    struct Immunity : Event::Data{
      Immunity(int _t)
	: Event::Data(Event::Info::Immunity, sizeof(struct Immunity), false),
	  time(_t) {}
      int time;
    };
#  endif
# endif

  };
};

#endif
