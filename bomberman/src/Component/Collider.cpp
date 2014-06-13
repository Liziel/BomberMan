#include "collider.hh"

namespace Component{

  /* Collider::Movable */
  Collider::Movable::Movable(Entity::GameObject* _p, Component::Collider* _c)
    : Component::abstract(_p), collider(_c), id(_c->addSelf(this)), x(-1), y(-1) {
    attachCallback(Event::Info::Clock,
		   new Event::FixedCallback([this, _p](Event::Data&) {
		       _p->getPosition(x, y);
		     }));
    attachCallback(Event::Info::RequireMovement,
		   new Event::FixedCallback([this](Event::Data& e) {
		       Event::Type::RequireMovement *event = reinterpret_cast<Event::Type::RequireMovement*> (&e);
		       double posx = event->x, posy = event->y;
		       double ix = (0.f) , iy = (0.f);
		       double ittx = 1.f - 2 * (event->vectorX < 0), ittY = 1.f - 2 * (event->vectorY < 0);
		       while (!((ittx > 0 && ix <= event->vectorX && ix + 1.f >= event->vectorX) ||
				(ittx < 0 && ix >= event->vectorX && ix - 1.f <= event->vectorX)) ||
			      !((ittY > 0 && iy <= event->vectorY && iy + 1.f >= event->vectorY) ||
				(ittY < 0 && iy >= event->vectorY && iy - 1.f <= event->vectorY))) {
			 if (!(ix <= event->vectorX && ix + 1.f >= event->vectorX)) {
			   if ((*collider)(posx + ittx, posy, parent->getHitBox(), Component::Collider::_Static, id))
			     posx += ittx;
			   ix += ittx;
			 }
			 
			 if (!(iy <= event->vectorY && iy + 1.f >= event->vectorY)) {
			   if ((*collider)(posx, posy + ittY,  parent->getHitBox(), Component::Collider::_Static, id))
			     posy += ittY;
			   iy += ittY;
			 }
		       }
		       
		       if (event->vectorX != 0.f && (*collider)(posx + event->vectorX - ix * ittx, posy, parent->getHitBox(), Component::Collider::_noType, id))
			 posx += event->vectorX - ix;
		       if (event->vectorY != 0.f && (*collider)(posx, posy + event->vectorY - iy * ittY, parent->getHitBox(), Component::Collider::_noType, id))
			 posy += event->vectorY - iy;
		       dispatchSelf(new Event::Type::Colliding(posx, posy, ix + iy));
		     }));

    attachCallback(Event::Info::RequireExplosion,
		   new Event::FixedCallback([this](Event::Data& e) {
		       Event::Type::RequireExplosion *event = reinterpret_cast<Event::Type::RequireExplosion*> (&e);
		       if (static_cast<int>(event->vectorX + event->x) == static_cast<int>(event->x) &&
			   static_cast<int>(event->vectorY + event->y) == static_cast<int>(event->y)) {
			 dispatchSelf(new Event::Type::Colliding(event->x + event->vectorX, event->y + event->vectorY, 0));
		       }
		       else {
			 double posx = event->x, posy = event->y;
			 double ix = (0.f) , iy = (0.f);
			 double ittx = 1.f - 2 * (event->vectorX < 0), ittY = 1.f - 2 * (event->vectorY < 0);
			 bool bx = false, by = false;
			 while (!(ix <= event->vectorX && ix + 1.f >= event->vectorX) ||
				!(iy <= event->vectorY && iy + 1.f >= event->vectorY)) {
			   if (!(ix <= event->vectorX && ix + ittx >= event->vectorX)) {
			     if ((*collider)(posx + ittx, posy, parent->getHitBox(), Component::Collider::_Static, id))
			       posx += ittx;
			     else
			       bx = true;
			     ix += ittx;
			   }

			   if (!(iy <= event->vectorY && iy + ittY >= event->vectorY)) {
			     if ((*collider)(posx, posy + ittY, parent->getHitBox(), Component::Collider::_Static, id))
			       posy += ittY;
			     else
			       by = true;
			     iy += ittY;
			   }
			 }

			 if (event->vectorX != 0.f && (*collider)(posx + event->vectorX - ix, posy, parent->getHitBox(), Component::Collider::_Movable, id))
			   posx += event->vectorX - ix;
			 if (event->vectorY != 0.f && (*collider)(posx, posy + event->vectorY - iy, parent->getHitBox(), Component::Collider::_Movable, id))
			   posy += event->vectorY - iy;
			 if (bx)
			   posx += ittx;
			 if (by)
			   posy += ittY;
			 dispatchSelf(new Event::Type::Colliding(posx, posy, ix + iy));
		       }
		     }));
  }

  Collider::Movable::~Movable() {
    collider->removeSelf(this);
  }

  Collider::Id	Collider::Movable::getId(void) {
    return (id);
  }

  bool		Collider::Movable::doCollide(double _x, double _y, const glm::vec4& _hitbox) {
    const glm::vec4& hitbox = parent->getHitBox();
    if (x + hitbox[XMIN] < _x + _hitbox[XMIN] && _x + _hitbox[XMIN] < x + hitbox[XMAX] &&
	y + hitbox[YMIN] < _y + _hitbox[YMIN] && _y + _hitbox[YMIN] < y + hitbox[YMAX])
      return (true);
    if (x + hitbox[XMIN] < _x + _hitbox[XMAX] && _x + _hitbox[XMAX] < x + hitbox[XMAX] &&
	y + hitbox[YMIN] < _y + _hitbox[YMIN] && _y + _hitbox[YMIN] < y + hitbox[YMAX])
      return (true);
    if (x + hitbox[XMIN] < _x + _hitbox[XMIN] && _x + _hitbox[XMIN] < x + hitbox[XMAX] &&
	y + hitbox[YMIN] < _y + _hitbox[YMAX] && _y + _hitbox[YMAX] < y + hitbox[YMAX])
      return (true);
    if (x + hitbox[XMIN] < _x + _hitbox[XMAX] && _x + _hitbox[XMAX] < x + hitbox[XMAX] &&
	y + hitbox[YMIN] < _y + _hitbox[YMAX] && _y + _hitbox[YMAX] < y + hitbox[YMAX])
      return (true);
    return (false);
  }

  std::string	Collider::Movable::serialization() {
    return (Tokenizer::serialize(Collider::Movable::getName(), x, y));
  }

  void		Collider::Movable::setBySerial(const Tokenizer& t) {
    x = t.get<double>(1);
    y = t.get<double>(2);
  }


  /* Collider::Static */
  Collider::Static::Static(Entity::GameObject* _p, Component::Collider* _c)
    : Component::abstract(_p), collider(_c), id(_c->addSelf(this)), x(-1), y(-1), disabled(false) {
    _p->getPosition(x, y);
    attachCallback(Event::Info::disableCollision,
		   new Event::FixedCallback([this] (Event::Data&) {
		       disabled = true;
		     }));
  }

  Collider::Static::~Static() {
    collider->removeSelf(this);
  }

  Collider::Id	Collider::Static::getId(void) {
    return (id);
  }

  bool		Collider::Static::doCollide(double _x, double _y, const glm::vec4& _hitbox) {
    if (disabled)
      return (false);
    const glm::vec4& hitbox = parent->getHitBox();
    if (x + hitbox[XMIN] < _x + _hitbox[XMIN] && _x + _hitbox[XMIN] < x + hitbox[XMAX] &&
	y + hitbox[YMIN] < _y + _hitbox[YMIN] && _y + _hitbox[YMIN] < y + hitbox[YMAX])
      return (true);
    if (x + hitbox[XMIN] < _x + _hitbox[XMAX] && _x + _hitbox[XMAX] < x + hitbox[XMAX] &&
	y + hitbox[YMIN] < _y + _hitbox[YMIN] && _y + _hitbox[YMIN] < y + hitbox[YMAX])
      return (true);
    if (x + hitbox[XMIN] < _x + _hitbox[XMIN] && _x + _hitbox[XMIN] < x + hitbox[XMAX] &&
	y + hitbox[YMIN] < _y + _hitbox[YMAX] && _y + _hitbox[YMAX] < y + hitbox[YMAX])
      return (true);
    if (x + hitbox[XMIN] < _x + _hitbox[XMAX] && _x + _hitbox[XMAX] < x + hitbox[XMAX] &&
	y + hitbox[YMIN] < _y + _hitbox[YMAX] && _y + _hitbox[YMAX] < y + hitbox[YMAX])
      return (true);
    return (false);
  }

  std::string	Collider::Static::serialization() {
    return (Tokenizer::serialize(Collider::Static::getName(), x, y, disabled));
  }

  void		Collider::Static::setBySerial(const Tokenizer& t) {
    x = t.get<double>(1);
    y = t.get<double>(2);
    disabled = t.get<bool>(3);
  }

  /* Collider */
  Collider::Collider()
    : _idGen(0) {}

  Collider::Id	Collider::addSelf(Component::Collider::Static* st){
    listStatic.push_back(st);
    _idGen += 1;
    return (_idGen - 1);
  }

  void	Collider::removeSelf(Component::Collider::Static* st){
    for (auto itt = listStatic.begin(); itt != listStatic.end(); itt++)
      if (*itt == st) {
	listStatic.erase(itt);
	return ;
      }
  }

  void	Collider::removeSelf(Component::Collider::Movable* mv){
    for (auto itt = listMovable.begin(); itt != listMovable.end(); itt++)
      if (*itt == mv) {
	listMovable.erase(itt);
	return ;
      }
  }

  Collider::Id	Collider::addSelf(Component::Collider::Movable* mv){
    listMovable.push_back(mv);
    _idGen += 1;
    return (_idGen - 1);
  }

  bool		Collider::operator()(double x, double y, const glm::vec4& hitbox, Collider::Type _c, Collider::Id ignore) const {
    if (_c != _Movable)
      for (auto obj : listStatic)
	if ((ignore == -1 || obj->getId() != ignore) && obj->doCollide(x, y, hitbox))
	  return (false);
    if (_c != _Static)
      for (auto obj : listMovable)
	if ((ignore == -1 || obj->getId() != ignore) && obj->doCollide(x, y, hitbox))
	  return (false);
    return (true);
  }

};
