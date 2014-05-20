#include "Component.hh"

namespace Component{

  /* Collider::Object */
  Collider::Object::Object(Collider::Object::Id _id, int _x, int _y)
    : id(_id), x(_x), y(_y) {}

  Collider::Object::Id Collider::Object::getId(void) const {
    return (id);
  }

  void	Collider::Object::setPosition(int _x, int _y) {
    x = _x;
    y = _y;
  }

  bool	Collider::Object::doCollide(int _x, int _y) const {
    return (_x == x && _y == y);
  }

  /* Collider */
  Collider::Collider(Event::Dispatcher* dispatcher)
    : _dispatcher(dispatcher), _idGen(0) {
    _dispatcher
      ->addCallbackOnEvent(Event::Info::CollidableObjectMovement,
			   new Event::Callback([this](Event::Data& e) {
			       Event::Type::CollidableObjectMovement* event =
				 reinterpret_cast<Event::Type::CollidableObjectMovement*>(&e);
			       moveColliderObject(event->objectId, event->x, event->y);
			     })
			   );
  }

  Collider::Object::Id	Collider::addColliderObject(int x, int y) {
    collideList.push_back(new Object(_idGen, x, y));
    _idGen += 1;
    return (_idGen - 1);
  }

  void		Collider::moveColliderObject(Collider::Object::Id objRef, int x, int y) {
    for (auto obj : collideList)
      if (obj->getId() == objRef)
	obj->setPosition(x, y);
  }

  bool		Collider::operator()(int x, int y, Collider::Object::Id ignore) const {
    for (auto obj : collideList)
      if ((ignore == -1 || obj->getId() != ignore) && obj->doCollide(x, y))
	return (false);
    return (true);
  }

};
