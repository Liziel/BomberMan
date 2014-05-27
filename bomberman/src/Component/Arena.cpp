#include "Arena.hh"

namespace Component{
  /* Winner */
  Arena::Winner::Winner(Component::Arena* _g) : game(_g), id(-1), dead(false) {}
  void	Arena::Winner::setId(Arena::Winner::Id _id) {
    id = _id;
  }

  void	Arena::Winner::imDead(bool _s) {dead = _s;}
  bool	Arena::Winner::amIDead(void) {return (dead);}
  /* Player */
  Arena::Player::Player(Entity::GameObject* _p, Component::Arena* _a)
    : Component::abstract(_p), Arena::Winner(_a) {
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
		   new Event::FixedCallback([this, _p] (Event::Data&) {
		       _p->disable();
		       imDead(true);
		     }));
  }
};
