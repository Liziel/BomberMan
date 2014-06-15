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
  namespace Game{
    enum mapType {square, croix};
  };
};

namespace Component{
  class Arena : public Component::Superior{

  public:
    class Winner : public Component::abstract{
    private:
      Component::Arena*		game;
    public:
      Winner(Entity::GameObject*, Component::Arena*);

    public:
      Entity::GameObject* getParent(void);

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
    class Player : public Winner{
    public:
      Player(Entity::GameObject*, Component::Arena*);

    public:
      std::string	serialization();
      void		setBySerial(const Tokenizer&);
    };

  public:
    class IA : public Winner{
    private:
      
    public:
      IA(Entity::GameObject*, Component::Arena*);

    public:
      std::string	serialization();
      void		setBySerial(const Tokenizer&);
    };

  public:
    class Bloc : public Component::abstract {
    private:
      double	x;
      double	y;

    private:
      bool	hitted;

    public:
      Bloc(Entity::GameObject*, Component::Arena*);

    public: 
      std::string	serialization();
      void		setBySerial(const Tokenizer&);
   };

  public:
    enum type {Empty, Breakable, Indestructible, Bomb};
  private:
    std::map< double, std::map<double, Arena::type> > Map;

  private:
    Entity::Factory*	_Efactory;

  private:
    std::list<Winner*>	fighter;

  private:
    Component::Game::mapType	_map;

  public:
    Arena(Event::Dispatcher*, Entity::Factory*);

  public:
    bool		PlayerAt(double x, double y, Winner*);
    void		addSelf(Winner*);
    void		GenerateSquareMap(int nplay, int nIa, int x, int y);
  };
};

namespace  Event{
  namespace Type{

    struct endGame : Event::Data {
      endGame()
	: Event::Data(Event::Info::endGame,
		      sizeof(struct endGame), false) {}
    };

    struct winner : Event::Data {
      winner(int _id)
	: Event::Data(Event::Info::winner,
		      sizeof(struct winner), false),
	  id(_id) {}
      int	id;
    };

# ifndef __COLLIDER_H__
    struct disableCollision : Event::Data {
      disableCollision()
	: Event::Data(Event::Info::disableCollision,
		      sizeof(struct disableCollision), false) {}
    };
# endif

    struct beginGame : Event::Data {
      beginGame(Component::Game::mapType _m, int x, int y, int np, int ni)
	: Event::Data(Event::Info::beginGame,
		      sizeof(struct beginGame), true),
	  _map(_m), mapSizex(x), mapSizey(y), nbPlayer(np), nbIa(ni) {}
      Component::Game::mapType	_map;
      int			mapSizex;
      int			mapSizey;
      int			nbPlayer;
      int			nbIa;
    };

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

# ifndef __EXPLODE_H__
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

# ifndef __RUNIC_H__
    struct EnableGlyph : Event::Data{
      EnableGlyph()
	: Event::Data(Event::Info::EnableGlyph, sizeof(struct EnableGlyph), false) {}
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

# ifndef __BONUS_H__
    struct LootBonus : Event::Data{
      LootBonus()
	: Event::Data(Event::Info::LootBonus, sizeof(struct LootBonus), true)
      {}
    };
# endif


# ifndef __EXPLODE_H__
    struct Explosion : Event::Data {
      Explosion(double _x, double _y)
	: Event::Data(Event::Info::Explosion,
		      sizeof(struct Explosion),
		      false),
	  x(_x), y(_y) {}
      double	x;
      double	y;
    };
# endif

  };
};

#endif
