#include "Component.hh"

bool	Component::matchPosition(double x, double y, double _x, double _y) {
  if (x < 0 && _x > 0)
    return (false);
  if (y < 0 && _y > 0)
    return (false);
  if (static_cast<int>(_x) != static_cast<int>(x) || static_cast<int>(_y) != static_cast<int>(y))
    return (false);
  return (true);
}

Component::abstract::abstract(Entity::GameObject* _p)
  : parent(_p) {}

Component::abstract::~abstract() {}

void		Component::abstract::dispatchAll(Event::Data* e) {
  parent->dispatchAll(e);
}
void	        Component::abstract::dispatchSelf(Event::Data* e) {
  parent->dispatchSelf(e);
}

Event::Callback::Id	Component::abstract::attachCallback
(Event::Info::Type _t, Event::Callback* _c, Event::Info::Priority _p) {
  return (parent->addCallback(_t, _c, _p));
}

