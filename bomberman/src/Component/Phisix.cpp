#include "phisix.hh"

# define XMIN 0
# define XMAX 1
# define YMIN 2
# define YMAX 3
namespace Component
{
  /*  Vector  */
  Phisix::Vector::Vector(Entity::GameObject* _p, Component::Phisix* _c)
    : Component::abstract(_p), phisix(_c), speed(1.f) {
    direction = {false, false, false, false};
    speedAxe[0] = 0.f;
    speedAxe[1] = 0.f;
    attachCallback(Event::Info::Clock,
		   new Event::FixedCallback([this](Event::Data&) {
		       double _speed = speed * phisix->getFriction();
		       double axeX = (-direction[Right] * _speed + direction[Left] * _speed) * speedAxe[1];
		       double axeY = (-direction[Down] * _speed + direction[Up] * _speed) * speedAxe[0];

		       parent->getPosition(x, y);
		       auto _x = x;
		       auto _y = y;
		       auto _hitbox = parent->getHitBox();
		       if (axeX == 0.f && axeY == 0.f)
			 return ;
		       if (axeX != 0.f && axeY != 0.f) {
			 axeX /= 2;
			 axeY /= 2;
		       }
		       dispatchSelf(new Event::Type::RequireMovement(x, y, axeX, axeY));
		     }));

    attachCallback(Event::Info::Colliding,
		   new Event::FixedCallback([this, _p](Event::Data& e) {
		       Event::Type::Colliding *event = reinterpret_cast<Event::Type::Colliding*>(&e);
		       x = event->endX;
		       y = event->endY;
		       _p->setPosition(x, y);
		     }));

    attachCallback(Event::Info::selfMovement,
		   new Event::FixedCallback([this](Event::Data& e){
		       Event::Type::selfMovement *event = reinterpret_cast<Event::Type::selfMovement*>(&e);
		       direction[event->direction] = event->state;
		     }));

    attachCallback(Event::Info::speedModifier,
		   new Event::FixedCallback([this](Event::Data& e){
		       Event::Type::speedModifier *event = reinterpret_cast<Event::Type::speedModifier*>(&e);
		       speed *= event->speed;
		     }));
    attachCallback(Event::Info::speedAxeSetter,
		   new Event::FixedCallback([this](Event::Data& e){
		       Event::Type::speedAxeSetter* event =
			 reinterpret_cast<Event::Type::speedAxeSetter*>(&e);
		       speedAxe[event->axe] = event->speed;
		     }));
  }
  
  std::string Phisix::Vector::serialization() {
    return (Tokenizer::serialize(getName(),
				 direction[Up], direction[Down],
				 direction[Left], direction[Right],
				 x,y,speed));
  }
  void Phisix::Vector::setBySerial(const Tokenizer& t) {
    direction[Up]	= t.get<bool>(1);
    direction[Down]	= t.get<bool>(2);
    direction[Left]	= t.get<bool>(3);
    direction[Right]	= t.get<bool>(4);
    x			= t.get<double>(5);
    y			= t.get<double>(6);
    speed		= t.get<double>(7);
  }

  /* Phisix */
  Phisix::Phisix(Event::Dispatcher *_d)
    : Component::Superior(_d), friction(0.35f) {
    dispatcher->addCallbackOnEvent(Event::Info::setFriction,
				   new Event::FixedCallback([this](Event::Data& e){
				       Event::Type::setFriction *event = reinterpret_cast< Event::Type::setFriction* >(&e);
				       friction = event->friction;
				     }));
  }

  double	Phisix::getFriction(void) {
    return (friction);
  }
};
