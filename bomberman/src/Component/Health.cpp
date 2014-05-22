#include "Component.hh"

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
  Health::Health(Event::Dispatcher* _d, int life)
    : dispatcher(_d), maxLife(life), life(life), _invincible(false) {
    dispatcher->addCallbackOnEvent(Event::Info::Clock,
				   _callback = new Event::Callback([this] (Event::Data&){
				       this->actualize();
				     }));
  }

  Health::~Health() {
    dispatcher->unsetCallbackForId(Event::Info::Clock, _callback->getId());
  }

  static bool	unsetDot(Health::Dot* dot) {
    return (dot->isOver());
  }
  void	Health::actualize() {
    if (isInvicible())
      return ;
    dotList.remove_if(unsetDot);
    if (life)
      for (auto dot : dotList)
	*this + dot->getDamage();
    else
      for (auto dot : dotList)
	dot->getDamage();
  }

  int	Health::operator+(int n) {
    if (isDead() || (isInvicible() && n < 0))
      return (0);
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

  void	Health::invincible(bool inv) {
    _invincible = inv;
  }

  bool	Health::isInvicible() {
    return (_invincible);
  }
};
