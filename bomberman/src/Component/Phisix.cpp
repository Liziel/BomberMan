#include "phisix.hh"

namespace Component
{
  /*  Vector  */
  Phisix::Vector::Vector(Entity::GameObject* _p, Component::Phisix* _c)
    : Component::abstract(_p), phisix(_c), speed(1.f) {
    direction = {false, false, false, false};
    _p->getPosition(x, y);

    attachCallback(Event::Info::Clock,
		   new Event::Callback([this](Event::Data&) {
		       double _speed = speed * phisix->getFriction();
		       dispatchSelf(new Event::Type::RequireMovement(x, y, (direction[Right] * _speed - direction[Left] * _speed),
								     (direction[Down] * _speed - direction[Up] * _speed)));
		     }));

    attachCallback(Event::Info::Colliding,
		   new Event::Callback([this, _p](Event::Data& e) {
		       Event::Type::Colliding *event = reinterpret_cast<Event::Type::Colliding*>(&e);
		       x = event->endX;
		       y = event->endY;
		       _p->setPosition(x, y);
		     }));

    attachCallback(Event::Info::selfMovement,
		   new Event::Callback([this](Event::Data& e){
		       Event::Type::selfMovement *event = reinterpret_cast<Event::Type::selfMovement*>(&e);
		       direction[event->direction] = event->state;
		     }));

    attachCallback(Event::Info::speedModifier,
		   new Event::Callback([this](Event::Data& e){
		       Event::Type::speedModifier *event = reinterpret_cast<Event::Type::speedModifier*>(&e);
		       speed *= event->speed;
		     }));
  }
  
  /* Phisix */
  Phisix::Phisix(Event::Dispatcher *_d)
    : Component::Superior(_d) {
    dispatcher->addCallbackOnEvent(Event::Info::setFriction,
				   new Event::Callback([this](Event::Data& e){
				       Event::Type::setFriction *event = reinterpret_cast< Event::Type::setFriction* >(&e);
				       friction = event->friction;
				     }));
  }

  double	Phisix::getFriction(void) {
    return (friction);
  }
};
