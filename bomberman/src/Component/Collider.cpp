#include "collider.hh"

namespace Component{

  /* Collider::Movable */
  Collider::Movable::Movable(Entity::GameObject* _p, Component::Collider* _c)
    : Component::abstract(_p), collider(_c), id(_c->addSelf(this)), x(-1), y(-1) {
    attachCallback(Event::Info::Clock,
		   new Event::Callback([this, _p](Event::Data&) {
		       _p->getPosition(x, y);
		     }));
    attachCallback(Event::Info::RequireMovement,
		   new Event::Callback([this](Event::Data& e) {
		       Event::Type::RequireMovement *event = reinterpret_cast<Event::Type::RequireMovement*> (&e);
		       if ((*collider)(event->x + event->vectorX, event->y + event->vectorY, Component::Collider::_noType, id))
			 dispatchSelf(new Event::Type::Colliding(event->x + event->vectorX, event->y + event->vectorY));
		       else
			 dispatchSelf(new Event::Type::Colliding(event->x, event->y));
		     }));
  }

  Collider::Id	Collider::Movable::getId(void) {
    return (id);
  }

  bool		Collider::Movable::doCollide(int _x, int _y) {
    return (x == _x && y == _y);
  }

  std::string	Collider::Movable::serialization() {
    return (Tokenizer::serialize(Collider::Movable::getName(), x, y));
  }

  void		Collider::Movable::setBySerial(const Tokenizer& t) {
    x = t.get<int>(1);
    y = t.get<int>(2);
  }


  /* Collider::Static */
  Collider::Static::Static(Entity::GameObject* _p, Component::Collider* _c)
    : Component::abstract(_p), collider(_c), id(_c->addSelf(this)), x(-1), y(-1) {
    _p->getPosition(x, y);
  }

  Collider::Id	Collider::Static::getId(void) {
    return (id);
  }

  bool		Collider::Static::doCollide(int _x, int _y) {
    return (x == _x && y == _y);
  }

  std::string	Collider::Static::serialization() {
    return (Tokenizer::serialize(Collider::Static::getName(), x, y));
  }

  void		Collider::Static::setBySerial(const Tokenizer& t) {
    x = t.get<int>(1);
    y = t.get<int>(2);
  }

  /* Collider */
  Collider::Collider()
    : _idGen(0) {}

  Collider::Id	Collider::addSelf(Component::Collider::Static* st){
    listStatic.push_back(st);
    _idGen += 1;
    return (_idGen - 1);
  }

  Collider::Id	Collider::addSelf(Component::Collider::Movable* mv){
    listMovable.push_back(mv);
    _idGen += 1;
    return (_idGen - 1);
  }

  bool		Collider::operator()(int x, int y, Collider::Type _c, Collider::Id ignore) const {
    if (_c != _Movable)
      for (auto obj : listStatic)
	if ((ignore == -1 || obj->getId() != ignore) && obj->doCollide(x, y))
	  return (false);
    if (_c != _Static)
      for (auto obj : listMovable)
	if ((ignore == -1 || obj->getId() != ignore) && obj->doCollide(x, y))
	  return (false);
    return (true);
  }

};
