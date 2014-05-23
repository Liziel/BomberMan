#include "collider.hh"

namespace Component{

  /* Collider::Movable */
  Collider::Movable::Movable(Entity::GameObject* _p, Component::Collider* _c)
    : Component::abstract(_p), collider(_c), id(_c->addSelf(this)), x(-1), y(-1) {
    attachCallback(Event::Info::RequireMovement,
		   new Event::Callback([this](Event::Data& e) {
		       Event::Type::RequireMovement *event = reinterpret_cast<Event::Type::RequireMovement*> (&e);
		       if ((*collider)(event->x + event->vectorX, event->y + event->vectorY, Component::Collider::noType, id))
			 dispatchSelf(new Event::Type::Colliding(event->x + event->vectorX, event->y + event->vectorY));
		       else
			 dispatchSelf(new Event::Type::Colliding(event->x, event->y));
		     }));
    attachCallback(Event::Info::Colliding,
		   new Event::Callback([this] (Event::Data&e) {
		       Event::Type::Colliding *event = reinterpret_cast<Event::Type::RequireMovement*> (&e);
		       x = (event->endX); 
		       y = (event->endY);
		     }));
  }

  Collider::Id	Collider::Movable::getId(void) {
    return (id);
  }

  bool		doCollide(int _x, int _y) {
    return (x == _x && y == _y);
  }

  std::string	serialization() {
    return ();
  }
  /* Collider::Static */
  

  /* Collider */
  Collider::Collider()
    : , _idGen(0) {);
  }

  bool		Collider::operator()(int x, int y, Collider::Object::type _c, Collider::Object::Id ignore) const {
    for (auto obj : collideList)
      if ((ignore == -1 || obj->getId() != ignore || obj->getType() != _c) && obj->doCollide(x, y))
	return (false);
    return (true);
  }

};
