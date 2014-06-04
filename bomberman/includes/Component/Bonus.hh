#ifndef __BONUS_H__
# define __BONUS_H__

# include "Component.hh"

namespace Component{
  namespace Bonus{
    enum Type {None, Immunity, IncreaseStack};

    class Giver : public Component::abstract{
    public:
      Giver(Entity::GameObject*);
    private:
      double			x;
      double			y;
      Event::Callback::Id	dispenserId;
      Bonus::Type		type;
    public:
      std::string serialization();
      void	setBySerial(const Tokenizer&);
    };

    class Receiver : public Component::abstract{
    private:
      int	stackLevel;
    public:
      Receiver(Entity::GameObject*);
      bool	reactByType(Bonus::Type);

    public:
      std::string serialization();
      void	setBySerial(const Tokenizer&);
    };

  };

};

namespace Event{
  namespace Type{
# ifndef __HEALTH_H__
    struct Immunity : Event::Data{
      Immunity(int _t)
	: Event::Data(Event::Info::Immunity, sizeof(struct Immunity), false),
	  time(_t) {}
      int time;
    };
# endif

# ifndef __PLANTBOMB_H__
    struct IncreaseBombStack : Event::Data{
      IncreaseBombStack()
	: Event::Data(Event::Info::IncreaseBombStack, sizeof(struct IncreaseBombStack), false) {}
    };
# endif

    struct LootBonus : Event::Data{
      LootBonus()
	: Event::Data(Event::Info::LootBonus, sizeof(struct LootBonus), true)
      {}
    };

    struct BonusLocation : Event::Data{
      BonusLocation(int _x, int _y, Component::Bonus::Type _t)
	: Event::Data(Event::Info::BonusLocation, sizeof(struct BonusLocation), true),
	  x(_x), y(_y), type(_t) {}
      int x;
      int y;
      Component::Bonus::Type type;
    };

    struct TakeBonus : Event::Data{
      TakeBonus(int _x, int _y)
	: Event::Data(Event::Info::BonusLocation, sizeof(struct TakeBonus), true),
	  x(_x), y(_y) {}
      int x;
      int y;
    };
  };
};

#endif
