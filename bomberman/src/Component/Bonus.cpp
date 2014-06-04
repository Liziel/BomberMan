#include "Bonus.hh"

namespace  Component{
  namespace Bonus{
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
		       if (event->x == x && event->y == y)
			 parent->unsetCallback(dispenserId);
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
