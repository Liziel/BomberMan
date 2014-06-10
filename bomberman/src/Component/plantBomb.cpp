#include "plantBomb.hh"

namespace Component{
  BombCast::BombCast(Entity::GameObject* _p)
    : Component::abstract(_p),
      isMuted(0), stackedSpells(0),
      spellArray({
	  Component::Effects::Glyph,
	    Component::Effects::Glyph, 
	    Component::Effects::Glyph}),
      maxBomb(1), stackedBomb(0), BombReloading(0) {

    attachCallback(Event::Info::Clock,
		   new Event::FixedCallback([this] (Event::Data&) {
		       if (!BombReloading && stackedBomb < maxBomb) {
			 stackedBomb += 1;
			 BombReloading = BombCast::Cooldown::value;
			 dispatchSelf(new Event::Type::speedModifier(0.98));
			 dispatchSelf(new Event::Type::BombReloaded());
		       }
		       if (BombReloading && !(stackedBomb == maxBomb)) {
			 BombReloading--;
		       }
		       if (isMuted > 0)
			 --isMuted;
		     }));

    attachCallback(Event::Info::addElement,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::addElement* event =
			 reinterpret_cast<Event::Type::addElement*>(&e);

		       if (stackedSpells >= 3 || isMuted)
			 return ;
		       spellArray[stackedSpells] = event->element;
		       stackedSpells += 1;
		     }));

    attachCallback(Event::Info::isMute,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::isMute* event =
			 reinterpret_cast<Event::Type::isMute*>(&e);
		       isMuted = event->time;
		     }));

    attachCallback(Event::Info::IncreaseBombStack,
		   new Event::FixedCallback([this] (Event::Data&) {
		       if (maxBomb < 5) {
			 maxBomb += 1;
		       }
		     }));

    attachCallback(Event::Info::selfPlantBomb,
		   new Event::FixedCallback([this, _p] (Event::Data&) {
		       if (stackedSpells != 3 || isMuted)
			 return ;
		       double x;
		       double y;
		       _p->getPosition(x, y);
		       dispatchAll(new Event::Type::PlantBomb
				   (static_cast<int>(x), static_cast<int>(y),
				    spellArray[0],
				    spellArray[1],
				    spellArray[2]));
		       dispatchSelf(new Event::Type::speedModifier(1 / 0.98));
		       dispatchSelf(new Event::Type::BombReleased());
		       stackedSpells = 0;
		     }));

  }

  std::string BombCast::serialization() {
    return (Tokenizer::serialize("BombCast", isMuted, stackedSpells,
				 spellArray[0], spellArray[1], spellArray[2]));
  }
  void	BombCast::setBySerial(const Tokenizer& t) {
    isMuted		= t.get<Event::Time> (1);
    stackedSpells	= t.get<unsigned int>(2);
    spellArray[0]	= static_cast<Component::Effects::type>(t.get<int>(3));
    spellArray[1]	= static_cast<Component::Effects::type>(t.get<int>(3));
    spellArray[2]	= static_cast<Component::Effects::type>(t.get<int>(3));
  }

};
