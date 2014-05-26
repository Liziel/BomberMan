#include "Arena.hh"

namespace Component{
  /* Player */
  Arena::Player::Player(Entity::GameObject* _p, Component::Arena* _a)
    : Component::abstract(_p), game(_a) {
    attachCallback(Event::Info::Keyboard,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::Keyboard* event = 
			 reinterpret_cast<Event::Type::Keyboard*>(&e);
		       if (event->key >= 0 &&  event->key <= 3)
			 dispatchSelf(new Event::Type::selfMovement
				      (static_cast<Component::Phisix::Vector::Direction>(event->key), event->state));
		       else if (event->state && event->key == 4)
			 dispatchSelf(new Event::Type::selfPlantBomb());
		       else if (event->state)
			 dispatchSelf(new Event::Type::addElement(static_cast<Component::Effects::type>(event->key - 5)));
		     }));

    attachCallback(Event::Info::dead,
		   new Event::FixedCallback([this] (Event::Data&) {
		       imDead();
		     }));
  }
};
