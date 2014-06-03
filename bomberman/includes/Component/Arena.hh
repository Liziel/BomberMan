#ifndef __ARENA_H__
# define __ARENA_H__

#include "Component.hh"

namespace Component{
# ifndef __PHISIX_H__
  namespace Phisix{
    namespace Vector{
      enum Direction {Up, Down, Right, Left};
    };
  };
# endif
# ifndef __EFFECTS_H__
  namespace Effects{
      typedef enum etype {Glyph, Fire, Ice, Electricity, Life} type;
      typedef enum elevel {low, med, high} level;
  };
# endif
};

namespace Component{
  class Arena : public Component::Superior{

  public:
    class Winner{
    private:
      Component::Arena*		game;
    public:
      Winner(Component::Arena*);

    public:
      typedef	int	Id;
    private:
      Winner::Id	id;
      void	setId(Winner::Id);

    private:
      bool	dead;
    public:
      void	imDead(bool);
      bool	amIDead(void);

    };

  public:
    class Player : public Component::abstract, public Winner{
    public:
      Player(Entity::GameObject*, Component::Arena*);

    public:
      std::string	serialization();
      void		setBySerial(const Tokenizer&);
    };

  private:
    std::list<Winner*>	fighter;
  public:
    Arena();
  };
};

namespace  Event{
  namespace Type{

# ifndef __KEYBOARD_H__
    struct Keyboard : Event::Data{
      Keyboard(int k, bool s)
	: Event::Data(Event::Info::Keyboard, sizeof(struct Keyboard), false),
	  key(k), state(s) {}
      int key;
      bool state;
    };
# endif

# ifndef __PLANTBOMB_H__
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

# ifndef __PHISIX_H__
    struct selfMovement : Event::Data{
      selfMovement(Component::Phisix::Vector::Direction _d, bool _b)
	: Event::Data(Event::Info::selfMovement, sizeof(struct selfMovement), false), direction(_d), state(_b) {}
      Component::Phisix::Vector::Direction	direction;
      bool					state;
    };
# endif

# ifndef __HEALTH_H__
    struct dead : Event::Data{
      dead()
	: Event::Data(Event::Info::dead, sizeof(struct dead), true) {}
    };
# endif

  };
};

#endif