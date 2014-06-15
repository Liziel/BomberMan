#include "Bonus.hh"

namespace  Component{
  namespace Bonus{
    Receiver::Receiver(Entity::GameObject* _p)
      : Component::abstract(_p), stackLevel(1) {
      std::cout << "pute des boies sauvages" << std::endl;
      attachCallback(Event::Info::BonusLocation,
		     new Event::FixedCallback([this](Event::Data& e) {
			 Event::Type::BonusLocation* event =
			   reinterpret_cast<Event::Type::BonusLocation*>(&e);
			 double x;
			 double y;
			 parent->getPosition(x, y);
			 if (Component::matchPosition(x, y, event->x, event->y)) {
			   if (reactByType(event->type)) {
			     dispatchAll(new Event::Type::TakeBonus(x, y));
			   }
			 }
		       }));
    }

    std::string	Receiver::serialization() {
      return (Tokenizer::serialize("BonusReceiver",
				   stackLevel));
    }

    void	Receiver::setBySerial(const Tokenizer& t){	
      stackLevel = t.get<int>(1);
    }

    bool	Receiver::reactByType(Bonus::Type _t) {
      if (_t == Immunity) {
	dispatchSelf(new Event::Type::Immunity(100));
      } else {
	stackLevel += 1;
	if (stackLevel > 5)
	  return (false);
	dispatchSelf(new Event::Type::IncreaseBombStack());
      }
      return (true);
    }

    Giver::Giver(Entity::GameObject* _p)
      : Component::abstract(_p), dispenserId(0), type(None) {
      parent->getPosition(x, y);
      attachCallback(Event::Info::LootBonus,
		     new Event::FixedCallback([this](Event::Data&) {
		       if (rand() % 2)
			 type = Immunity;
		       else
			 type = IncreaseStack;
		       dispenserId = attachCallback(Event::Info::Clock,
						    new Event::FixedCallback([this] (Event::Data&) {
						      dispatchAll(new Event::Type::BonusLocation(x, y, type));
						      }));
		       }));
      attachCallback(Event::Info::TakeBonus,
		     new Event::FixedCallback([this](Event::Data& e){
		       Event::Type::TakeBonus* event =
			 reinterpret_cast<Event::Type::TakeBonus*>(&e);
		       double x,y;
		       parent->getPosition(x,y);
		       if (Component::matchPosition(x,y, event->x, event->y)) {
			 std::cout << "Here is ...." << std::endl;
			 parent->unsetCallback(dispenserId);
			 std::cout << ".... the segfault?" << std::endl;
		       }
		       }));
    }

    std::string	Giver::serialization() {
      return (Tokenizer::serialize("BonusGiver",
				   type,
				   x,y));
    }

    void	Giver::setBySerial(const Tokenizer& t){
      if ((type = static_cast<Type>(t.get<int>(1))) != None)
	dispenserId
	  = attachCallback(Event::Info::Clock,
			   new Event::FixedCallback([this] (Event::Data&) {
			       dispatchAll(new Event::Type::BonusLocation(x, y, type));
			     }));
	
      x = t.get<double>(2);
      y = t.get<double>(3);
    }

  };
};
