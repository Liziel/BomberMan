#include "effects.hh"

namespace Component{
  namespace Effects{

    /* #### Speed M#### */
    Status::SpeedModifier::SpeedModifier(double speed, int time, Status *_p)
      : speedModifier(speed), clock(time), status(_p) {}

    bool	Status::SpeedModifier::isOver(double& sp) {
      if (clock) {
	clock--;
      } else {
	if (!speedModifier)
	  sp = 1;
	else
	  sp = 1 / speedModifier;
	return (true);
      }
      return (false);
    }

    std::string	Status::SpeedModifier::serialization() {
      return (Tokenizer::subserialize(speedModifier, clock));
    }

    /* #### Status #### */
    Status::Status(Entity::GameObject* _p)
      : Component::abstract(_p),
	isOnFire(0), isOnIce(0), isOnElectricity(0), isOnLife(0) {

      attachCallback(Event::Info::Clock,
		     new Event::FixedCallback([this] (Event::Data&) {
			 speedVect.remove_if(std::function<bool(Component::Effects::Status::SpeedModifier*)> ([this] (Status::SpeedModifier* sp) -> bool {
			       double _sp;
			       bool over = sp->isOver(_sp);
			       if (over) {
				 dispatchSelf(new Event::Type::speedModifier(_sp));
				 delete sp;
			       }
			       return (over);
			     }));
			 isOnFire -= (isOnFire != 0);
			 if (!isOnFire)
			   dispatchSelf(new Event::Type::isOnFire(false));
			 isOnIce -= (isOnIce != 0);
			 if (!isOnIce)
			   dispatchSelf(new Event::Type::isOnIce(false));
			 isOnElectricity -= (isOnElectricity != 0);
			 if (!isOnElectricity)
			   dispatchSelf(new Event::Type::isOnElectricity(false));
			 isOnLife -= (isOnLife != 0);
			 if (!isOnLife)
			   dispatchSelf(new Event::Type::isOnLife(false));
		       }));

      const Effects::damage fireLow  = {-3, -5, 10, 2, 1.f, 0, false, 0};
      const Effects::damage fireMed  = {-5, -5, 10, 1, 1.f, 0, false, 0};
      const Effects::damage fireHigh = {-7, -5, 10, 0, 1.f, 0, false, 0};
      attachCallback(Event::Info::FireExplosion,
		     new Event::FixedCallback([this, &fireLow, &fireMed, &fireHigh] (Event::Data& e) {
			 Event::Type::FireExplosion *event = reinterpret_cast<Event::Type::FireExplosion*>(&e);
			 Event::Time _t;
			 double x;
			 double y;
			 std::cout << "peinard"<< std::endl;
			 parent->getPosition(x, y);
			 if (event->x != x || event->y != y)
			   return ;
			 if (event->level == low)  { this->interpretDamage(fireLow); _t = fireLow.dotDuration;  }
			 if (event->level == med)  { this->interpretDamage(fireMed); _t = fireMed.dotDuration;  }
			 if (event->level == high) { this->interpretDamage(fireHigh); _t = fireHigh.dotDuration; }
			 if (!isOnFire)
			   dispatchSelf(new Event::Type::isOnFire(true));
			 isOnFire = _t;
		       }), Event::Info::low);
      attachCallback(Event::Info::Clock,
		     new Event::FixedCallback([this] (Event::Data&) {
		       }));

      const Effects::damage electricityLow  = {0, -1, 10, 2, 1.1, 5, true, 2};
      const Effects::damage electricityMed  = {0, -1, 10, 1, 1.2, 5, true, 5};
      const Effects::damage electricityHigh = {0, -1, 10, 0, 1.5, 5, true, 10};
      attachCallback(Event::Info::ElectricityExplosion,
		     new Event::FixedCallback([this, electricityLow, electricityMed, electricityHigh] (Event::Data& e) {
			 Event::Type::ElectricityExplosion *event = reinterpret_cast<Event::Type::ElectricityExplosion*>(&e);
			 Event::Time _t;
			 double x;
			 double y;

			 parent->getPosition(x, y);
			 if (event->x != x || event->y != y)
			   return ;
			 if (event->level == low)  { this->interpretDamage(electricityLow); _t = electricityLow.dotDuration;  }
			 if (event->level == med)  { this->interpretDamage(electricityMed); _t = electricityMed.dotDuration;  }
			 if (event->level == high) { this->interpretDamage(electricityHigh); _t = electricityHigh.dotDuration; }
			 if (!isOnElectricity)
			   dispatchSelf(new Event::Type::isOnElectricity(true));
			 isOnElectricity = _t;
		       }), Event::Info::low);

      const Effects::damage iceLow  = {-1, 0, 0, 2, 0.9, 3, false, 0};
      const Effects::damage iceMed  = {-2, 0, 0, 1, 0.8, 5, false, 0};
      const Effects::damage iceHigh = {-3, 0, 0, 0, 0.6, 10, false, 0};
      attachCallback(Event::Info::IceExplosion,
		     new Event::FixedCallback([this, iceLow, iceMed, iceHigh] (Event::Data& e) {
			 Event::Type::IceExplosion *event = reinterpret_cast<Event::Type::IceExplosion*>(&e);
			 Event::Time _t;
			 double x;
			 double y;

			 parent->getPosition(x, y);
			 if (event->x != x || event->y != y)
			   return ;
			 if (event->level == low)  { this->interpretDamage(iceLow); _t = iceLow.dotDuration;  }
			 if (event->level == med)  { this->interpretDamage(iceMed); _t = iceMed.dotDuration;  }
			 if (event->level == high) { this->interpretDamage(iceHigh); _t = iceHigh.dotDuration; }
			 if (!isOnIce)
			   dispatchSelf(new Event::Type::isOnIce(true));
			 isOnIce = _t;
		       }), Event::Info::low);

      const Effects::damage lifeLow  = {+3, 0, 10, 2, 1.f, 0, false, 0};
      const Effects::damage lifeMed  = {+6, 0, 10, 1, 1.f, 0, false, 0};
      const Effects::damage lifeHigh = {+9, 0, 10, 0, 1.f, 0, false, 0};
      attachCallback(Event::Info::LifeExplosion,
		     new Event::FixedCallback([this, lifeLow, lifeMed, lifeHigh] (Event::Data& e) {
			 Event::Type::LifeExplosion *event = reinterpret_cast<Event::Type::LifeExplosion*>(&e);
			 double x;
			 double y;

			 parent->getPosition(x, y);
			 if (event->x != x || event->y != y)
			   return ;
			 if (event->level == low)  { this->interpretDamage(lifeLow);  }
			 if (event->level == med)  { this->interpretDamage(lifeMed);  }
			 if (event->level == high) { this->interpretDamage(lifeHigh); }
			 if (!isOnLife)
			   dispatchSelf(new Event::Type::isOnLife(true));
			 isOnLife = 1;
		       }), Event::Info::low);

    }

    void	Status::interpretDamage(const Effects::damage& _d) {
      if (_d.dotDamage)
	dispatchSelf(new Event::Type::PlaceDot(_d.dotDamage, _d.dotDuration, _d.dotTimed));
      if (_d.damage < 0)
	dispatchSelf(new Event::Type::lifeLoss( -_d.damage ));
      if (_d.damage > 0)
	dispatchSelf(new Event::Type::lifeGain(  _d.damage ));
      if (_d.speedModifier != 1.f)
	applySlow(_d.speedModifier, _d.speedModifierDuration);
      if (_d.mute)
	applyMute(_d.muteDuration);
    };

    void	Status::applySlow(double slow, int duration) {
      dispatchSelf(new Event::Type::speedModifier(slow));
      speedVect.push_back(new Status::SpeedModifier(slow, duration, this));
    }

    void	Status::applyMute(int duration) {
      dispatchSelf(new Event::Type::isMute(duration));
    }

    std::string Status::speedSerialization(std::list<SpeedModifier*>::iterator itt) {
      auto nextItt = ++itt;
      --itt;
      if (nextItt == speedVect.end())
	return (Tokenizer::serialize((*itt)->serialization(), speedSerialization(nextItt)));
      else
	return ((*itt)->serialization());
    }

    std::string	Status::serialization() {
      return (Tokenizer::serialize("Status",
				   isOnFire, isOnElectricity, isOnLife, isOnIce,
				   speedSerialization(speedVect.begin())));
    }

    void		Status::setBySerial(const Tokenizer& t) {
      int	n = 5;
      isOnFire		= t.get<Event::Time>(1);
      isOnElectricity	= t.get<Event::Time>(2);
      isOnLife		= t.get<Event::Time>(3);
      isOnIce		= t.get<Event::Time>(4);
      for (; n < t.getSize(); n += 2)
	applySlow(t.get<double>(n), t.get<int>(n + 1));
    }

  };
};
