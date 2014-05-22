#include "Component.hh"

namespace Component{
  namespace Effects{

    Status::Status(Event::Dispatcher* _d, Component::Health* _h, Component::Phisix* _p)
      : _dispatcher(_d), _health(_h), _phisix(_p) {

      const Effects::damage fireLow  = {-3, -5, 10, 2, 1.f, 0, false, 0};
      const Effects::damage fireMed  = {-5, -5, 10, 1, 1.f, 0, false, 0};
      const Effects::damage fireHigh = {-7, -5, 10, 0, 1.f, 0, false, 0};
      _dispatcher->addCallbackOnEvent(Event::Info::FireExplosion,
				      new Event::Callback([this, fireLow, fireMed, fireHigh] (Event::Data& e) {
					  Event::Type::FireExplosion *event = reinterpret_cast<Event::Type::FireExplosion*>(&e);
					  if (event->level == low)  { this->interpretDamage(fireLow);  }
					  if (event->level == med)  { this->interpretDamage(fireMed);  }
					  if (event->level == high) { this->interpretDamage(fireHigh); }
					}), Event::Info::low);

      const Effects::damage electricityLow  = {0, -1, 10, 2, 1.1, 2, true, 2};
      const Effects::damage electricityMed  = {0, -1, 10, 1, 1.2, 5, true, 5};
      const Effects::damage electricityHigh = {0, -1, 10, 0, 1.5, 10, true, 10};
      _dispatcher->addCallbackOnEvent(Event::Info::ElectricityExplosion,
				      new Event::Callback([this, electricityLow, electricityMed, electricityHigh] (Event::Data& e) {
					  Event::Type::ElectricityExplosion *event = reinterpret_cast<Event::Type::ElectricityExplosion*>(&e);
					  if (event->level == low)  { this->interpretDamage(electricityLow);  }
					  if (event->level == med)  { this->interpretDamage(electricityMed);  }
					  if (event->level == high) { this->interpretDamage(electricityHigh); }
					}), Event::Info::low);

      const Effects::damage iceLow  = {-1, 0, 0, 2, 0.9, 0, false, 0};
      const Effects::damage iceMed  = {-2, 0, 0, 1, 0.8, 0, false, 0};
      const Effects::damage iceHigh = {-3, 0, 0, 0, 0.6, 0, false, 0};
      _dispatcher->addCallbackOnEvent(Event::Info::IceExplosion,
				      new Event::Callback([this, iceLow, iceMed, iceHigh] (Event::Data& e) {
					  Event::Type::IceExplosion *event = reinterpret_cast<Event::Type::IceExplosion*>(&e);
					  if (event->level == low)  { this->interpretDamage(iceLow);  }
					  if (event->level == med)  { this->interpretDamage(iceMed);  }
					  if (event->level == high) { this->interpretDamage(iceHigh); }
					}), Event::Info::low);

      const Effects::damage lifeLow  = {+3, 0, 10, 2, 1.f, 0, false, 0};
      const Effects::damage lifeMed  = {+6, 0, 10, 1, 1.f, 0, false, 0};
      const Effects::damage lifeHigh = {+9, 0, 10, 0, 1.f, 0, false, 0};
      _dispatcher->addCallbackOnEvent(Event::Info::LifeExplosion,
				      new Event::Callback([this, lifeLow, lifeMed, lifeHigh] (Event::Data& e) {
					  Event::Type::LifeExplosion *event = reinterpret_cast<Event::Type::LifeExplosion*>(&e);
					  if (event->level == low)  { this->interpretDamage(lifeLow);  }
					  if (event->level == med)  { this->interpretDamage(lifeMed);  }
					  if (event->level == high) { this->interpretDamage(lifeHigh); }
					}), Event::Info::low);

    }

    void	Status::interpretDamage(const Effects::damage& _d) {
      *_health + _d.damage;
      if (_d.dotDamage)
	_health->addDot(new Health::Dot(_d.dotDamage, _d.dotDuration, _d.dotTimed));
      applySlow(_d.speedModifier, _d.speedModifierDuration);
      if (_d.mute)
	applyMute(_d.muteDuration);
    };
  };
};
