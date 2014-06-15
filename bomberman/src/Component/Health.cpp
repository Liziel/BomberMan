#include "health.hh"

namespace Component {
  /* ###### Dot ##### */
  Health::Dot::Dot(int _v, int _cl, unsigned int _t)
    : damage(_v), clockLife(_cl), rTime(_t), aTime(_t) {}

  Health::Dot::Dot(int _v, int _cl, unsigned int _t, unsigned int _tt)
    : damage(_v), clockLife(_cl), rTime(_t), aTime(_tt) {}

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

  std::string	Health::Dot::serialize() {
    return (Tokenizer::subserialize(damage, clockLife, rTime, aTime));
  }

  /* ##### Health ##### */
  Health::~Health() {}
  Health::Health(Entity::GameObject* _p)
    : Component::abstract(_p), maxLife(_p->getLifeAmount()), life(_p->getLifeAmount()), immunityTime(0) {
    attachCallback(Event::Info::Clock,
		   new Event::FixedCallback([this] (Event::Data&){
		       if (isDead())
			 return ;
		       dispatchSelf(new Event::Type::lifeActualize(life));
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
		       *this + event->amount;
		       if (!(life))
			 dispatchSelf(new Event::Type::dead());
		     }));
    attachCallback(Event::Info::lifeLoss,
		   new Event::FixedCallback([this] (Event::Data& e){
		       Event::Type::lifeLoss* event = reinterpret_cast<Event::Type::lifeLoss*>(&e);
		       if (isDead())
			 return ;
		       *this + event->amount;
		       if (!(life))
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
    if (immunityTime > 0)
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

  std::string Health::dotSerialisation(std::list<Dot*>::iterator itt) {
    if (itt == dotList.end())
      return ("");
    auto nextIt = itt++;
    --itt;
    if (nextIt == dotList.end()) {
      return ((*itt)->serialize());
    } else {
      return (Tokenizer::subserialize((*itt)->serialize(), dotSerialisation(nextIt)));
    }
  }

  std::string Health::serialization() {
    return (Tokenizer::serialize("Health", maxLife, life, immunityTime,
				 dotSerialisation(dotList.begin())));
  }

  void	Health::setBySerial(const Tokenizer& t) {
    int	n = 4;
    life		= t.get<int>(1);
    maxLife		= t.get<int>(2);
    immunityTime	= t.get<int>(3);
    for (; n < t.getSize(); n += 4)
      addDot(new Dot(t.get<double>(n), t.get<int>(n + 1), t.get<unsigned int>(n + 2), t.get<unsigned int>(n + 3)));
  }

  
};
