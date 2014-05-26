#include "health.hh"

namespace Component {
  /* ###### Dot ##### */
  Health::Dot::Dot(int _v, int _cl, unsigned int _t)
    : damage(_v), clockLife(_cl), rTime(_t), aTime(_t) {}

  int	Health::Dot::getDamage(void) {
    if (!clockLife) {
      return (0);
    }
    if (aTime) {
      --aTime;
      return (0);
    }
    clockLife--;
    return (damage);
  };

  bool	Health::Dot::isOver(void) {
    return (!clockLife);
  }

  /* ##### Health ##### */
  Health::Health(Entity::GameObject* _p)
    : Component::abstract(_p), maxLife(_p->getLifeAmount()), life(_p->getLifeAmount()), immunityTime(0) {
    attachCallback(Event::Info::Clock,
		   new Event::FixedCallback([this] (Event::Data&){
		       if (isDead())
			 return ;
		       if (!this->actualize())
			 dispatchSelf(new Event::Type::dead());
		     }));
    attachCallback(Event::Info::revive,
		   new Event::FixedCallback([this] (Event::Data&){
		       revive(maxLife);
		     }));
    attachCallback(Event::Info::lifeGain,
		   new Event::FixedCallback([this] (Event::Data& e){
		       Event::Type::lifeGain* event = reinterpret_cast<Event::Type::lifeGain*>(&e);
		       if (isDead())
			 return ;
		       if (*this + event->amount)
			 dispatchSelf(new Event::Type::dead());
		     }));
    attachCallback(Event::Info::lifeLoss,
		   new Event::FixedCallback([this] (Event::Data& e){
		       Event::Type::lifeGain* event = reinterpret_cast<Event::Type::lifeGain*>(&e);
		       if (isDead())
			 return ;
		       if (*this - event->amount)
			 dispatchSelf(new Event::Type::dead());
		     }));
    attachCallback(Event::Info::Immunity,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::Immunity* event = reinterpret_cast<Event::Type::Immunity*>(&e);
		       invincible(event->time);
		     }));
    attachCallback(Event::Info::PlaceDot,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::PlaceDot* event = reinterpret_cast<Event::Type::PlaceDot*>(&e);
		       addDot(new Health::Dot(event->damage, event->duration, event->warmUp));
			 }));
  }

  static bool	unsetDot(Health::Dot* dot) {
    if (dot->isOver()){
      delete dot;
      return (true);
    }
    return (false); 
  }

  int	Health::actualize() {
    immunityTime -= 1;
    if (isInvicible())
      return (life);
    dotList.remove_if(unsetDot);
    if (life)
      for (auto dot : dotList)
	*this + dot->getDamage();
    else
      for (auto dot : dotList)
	dot->getDamage();
    return (life);
  }

  int	Health::operator+(int n) {
    if (isDead() || (isInvicible() && n < 0))
      return (life);
    life += n;
    if (life < 0)
      life = 0;
    if (life > maxLife)
      life = maxLife;
    return (life);
  }
  int	Health::operator-(int n) {
    return (*this + (-n));
  }

  void	Health::revive(unsigned int reviveLife) {
    if (life)
      return ;
    life = reviveLife;
    if (life > maxLife)
      life = maxLife;
  }

  bool	Health::isDead(void) {
    return (!life);
  }

  void	Health::addDot(Health::Dot* dot) {
    dotList.push_back(dot);
  }

  void	Health::invincible(int _t) {
    immunityTime = _t;
  }

  bool	Health::isInvicible() {
    return (immunityTime);
  }
};
