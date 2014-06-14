#include "Runic.hh"

namespace Component{
  void	Runic::dispatchElement(Component::Effects::type t){
    dispatchAll(new Event::Type::Explosion(x, y));
    if (t == Component::Effects::Fire)
      dispatchAll(new Event::Type::FireExplosion(x, y, Component::Effects::low));
    if (t == Component::Effects::Life)
      dispatchAll(new Event::Type::LifeExplosion(x, y, Component::Effects::low));
    if (t == Component::Effects::Electricity)
      dispatchAll(new Event::Type::ElectricityExplosion(x, y, Component::Effects::low));
    if (t == Component::Effects::Ice)
      dispatchAll(new Event::Type::IceExplosion(x, y, Component::Effects::low));
  }

  Runic::Runic(Entity::GameObject* _p, bool _runable)
    : Component::abstract(_p), runable(_runable), runeDuration(0), runeCooldown(0), runeBurning(0), attachedElement(0), attachableElement(0) {
    parent->getPosition(x, y);
    attachCallback(Event::Info::Clock,
		   new Event::FixedCallback( [this]( Event::Data& ) {
		       if (!runeDuration)
			 return ;
		       //		       std::cout << "element["<< element1 <<"]["<< element2 <<"], duration["<< runeDuration <<"], burning["<< runeBurning <<"], cooldown["<< runeCooldown <<"]" << std::endl;
		       runeDuration -= 1;
		       if (!runeDuration)
			 dispatchSelf(new Event::Type::extinctGlyph());
		       runeBurning -= 1;
		       if (runeBurning)
			 return ;
		       if (attachedElement >= 1)
			 dispatchElement(element1);
		       if (attachedElement == 2)
			 dispatchElement(element2);
		       runeBurning = runeCooldown;
		     }));

    attachCallback(Event::Info::GlyphExplosion,
		   new Event::FixedCallback( [this]( Event::Data& e) {
		       if (!runable)
			 return ;

		       Event::Type::GlyphExplosion* event =
			 reinterpret_cast<Event::Type::GlyphExplosion*>(&e);
		       if (runeDuration)
			 return ;
		       auto hitbox = parent->getHitBox();
		       if (!(x + hitbox[0] <= event->x && event->x <= x + hitbox[1] &&
			     y + hitbox[2] <= event->y && event->y <= y + hitbox[3]))
			 return ;
		       std::cout << "hitbox["<< x + hitbox[0] <<"]["<< x + hitbox[1] <<"]["<< y + hitbox[2] <<"]["<< y + hitbox[3] <<"]" << std::endl;
		       if (event->level == Component::Effects::low) {
			 runeCooldown = 8;
			 runeDuration = 8 * 3;
			 attachableElement = 2;
		       }
		       if (event->level == Component::Effects::med) {
			 runeCooldown = 8;
			 runeDuration = 8 * 5;
			 attachableElement = 1;
		       }
		       if (event->level == Component::Effects::high) {
			 runeCooldown = -1;
			 runeDuration = 8 * 10;
			 attachableElement = 0;
		       }
		       runeBurning = runeCooldown;
		       dispatchSelf(new Event::Type::SocketGlyph());
		     }));
    if (!_runable)
      attachCallback(Event::Info::EnableGlyph,
		     new Event::FixedCallback([this] ( Event::Data& ) {
			 runable = true;
		       }));

    attachCallback(Event::Info::FireExplosion,
		   new Event::FixedCallback([this] ( Event::Data& e ) {
		       Event::Type::FireExplosion* event =
			 reinterpret_cast<Event::Type::FireExplosion*>(&e);
		       if (!attachableElement)
			 return ;
		       if (!(event->x == x && event->y == y))
			 return ;
		       if (event->level == Component::Effects::low) {
			 if (attachableElement == 2)
			   element2 = Component::Effects::Fire;
			 else
			   element1 = Component::Effects::Fire;
			 attachableElement -= 1;
		       } else if (event->level == Component::Effects::med) {
			 element1 = Component::Effects::Fire;
			 element2 = Component::Effects::Fire;
			 attachableElement = 0;
		       }
		     }));

    attachCallback(Event::Info::LifeExplosion,
		   new Event::FixedCallback([this] ( Event::Data& e ) {
		       Event::Type::LifeExplosion* event =
			 reinterpret_cast<Event::Type::LifeExplosion*>(&e);
		       if (!attachableElement)
			 return ;
		       if (!(event->x == x && event->y == y))
			 return ;
		       if (event->level == Component::Effects::low) {
			 if (attachableElement == 2)
			   element2 = Component::Effects::Life;
			 else
			   element1 = Component::Effects::Life;
			 attachableElement -= 1;
		       } else if (event->level == Component::Effects::med) {
			 element1 = Component::Effects::Life;
			 element2 = Component::Effects::Life;
			 attachableElement = 0;
		       }
		     }));

    attachCallback(Event::Info::ElectricityExplosion,
		   new Event::FixedCallback([this] ( Event::Data& e ) {
		       Event::Type::ElectricityExplosion* event =
			 reinterpret_cast<Event::Type::ElectricityExplosion*>(&e);
		       if (!attachableElement)
			 return ;
		       if (!(event->x == x && event->y == y))
			 return ;
		       if (event->level == Component::Effects::low) {
			 if (attachableElement == 2)
			   element2 = Component::Effects::Electricity;
			 else
			   element1 = Component::Effects::Electricity;
			 attachableElement -= 1;
		       } else if (event->level == Component::Effects::med) {
			 element1 = Component::Effects::Electricity;
			 element2 = Component::Effects::Electricity;
			 attachableElement = 0;
		       }
		     }));

    attachCallback(Event::Info::IceExplosion,
		   new Event::FixedCallback([this] ( Event::Data& e ) {
		       Event::Type::IceExplosion* event =
			 reinterpret_cast<Event::Type::IceExplosion*>(&e);
		       if (!attachableElement)
			 return ;
		       if (!(event->x == x && event->y == y))
			 return ;
		       if (event->level == Component::Effects::low) {
			 if (attachableElement == 2)
			   element2 = Component::Effects::Ice;
			 else
			   element1 = Component::Effects::Ice;
			 attachableElement -= 1;
		       } else if (event->level == Component::Effects::med) {
			 element1 = Component::Effects::Ice;
			 element2 = Component::Effects::Ice;
			 attachableElement = 0;
		       }
		     }));

  }
  std::string Runic::serialization() {
    if (runable) {
      if (runeDuration)
	return (Tokenizer::serialize("Runic", runable, runeDuration, runeCooldown, runeBurning, attachedElement, element1, element2));
      else
	return (Tokenizer::serialize("Runic", runable, runeDuration));
    } else
      return (Tokenizer::serialize("Runic", runable));
  }
  void	Runic::setBySerial(const Tokenizer& t) {
    parent->getPosition(x, y);
    if ((runable = t.get<bool>(1)) == true) {
      if ((runeDuration = t.get<Event::Time>(2)) != 0) {
	runeCooldown = t.get<Event::Time>(3);
	runeBurning = t.get<Event::Time>(4);
	attachedElement = t.get<int>(5);
	element1 = static_cast<Component::Effects::type>(t.get<int>(6));
	element2 = static_cast<Component::Effects::type>(t.get<int>(7));
      }
    }
  }
};
