#include "Component.hh"

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

