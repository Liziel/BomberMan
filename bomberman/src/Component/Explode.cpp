#include "Explode.hh"

namespace Component{
  Explode::Explode(Entity::GameObject* _p) : Component::abstract(_p), untilBOOM(-1) {
    attachCallback(Event::Info::Clock,
		   new Event::FixedCallback([this, _p] (Event::Data&) {
		       if (!untilBOOM)
			 delete _p;
		       if (untilBOOM > 0)
			 untilBOOM -= 1;
		       if (!untilBOOM) {
			 EXPLODE(_p);
		       }
		     }));
    attachCallback(Event::Info::Explosion,
		   new Event::FixedCallback([this, _p] (Event::Data& e) {
		       Event::Type::Explosion* event = 
			 reinterpret_cast<Event::Type::Explosion*>(&e);
		       double x;
		       double y;

		       _p->getPosition(x, y);
		       if (event->x == static_cast<int>(x) && event->y == static_cast<int>(y))
			 EXPLODE(_p);
		     }));
  }

  void	Explode::EXPLODE(Entity::GameObject* _p){
    double x;
    double y;

    _p->getPosition(x, y);
    attachCallback(Event::Info::Colliding,
		   new Event::FixedCallback([this, x, y] (Event::Data& e) {
		       Event::Type::Colliding* _ = 
			 reinterpret_cast<Event::Type::Colliding*>(&e);		       
		       if (_->endX > x)
			 for (; _->endX >= x + 1; --_->endX)
			   dispatch(_->endX, y);
		       if (_->endX < x)
			 for (; _->endX <= x - 1; ++_->endX)
			   dispatch(_->endX, y);
		       if (_->endY > y)
			 for (; _->endX >= y + 1; --_->endY)
			   dispatch(x, _->endY);
		       if (_->endY > y)
			 for (; _->endX >= y + 1; --_->endY)
			   dispatch(x, _->endY);
		     }));
    double spread = getSpread(elements[0]) +
      getSpread(elements[1]) +
      getSpread(elements[2]) - 1;
    dispatchSelf(new Event::Type::RequireMovement(x,y, spread, 0));
    dispatchSelf(new Event::Type::RequireMovement(x,y, -spread, 0));
    dispatchSelf(new Event::Type::RequireMovement(x,y, 0, -spread));
    dispatchSelf(new Event::Type::RequireMovement(x,y, 0, spread));
    dispatch(x, y);
    delete _p;
  }

  void	Explode::dispatch(int x, int y) {
    std::function<void(Effects::type, Effects::level)> =
      [this, x, y] (Effects::type t, Effects::level lvl) {
      if (t == Fire)
	dispatch(new Event::Type::FireExplosion(x, y, lvl));
      if (t == Ice)
	dispatch(new Event::Type::IceExplosion(x, y, lvl));
      if (t == Life)
	dispatch(new Event::Type::LifeExplosion(x, y, lvl));
      if (t == Electricity)
	dispatch(new Event::Type::ElectricityExplosion(x, y, lvl));
      if (t == Glyph)
	dispatch(new Event::Type::GlyphExplosion(x, y, lvl));
    }
    std::array<bool, 3> it = {true, false, false}
    Effects::level	lvl = low;

    if (elements[0] == elements[1]) {
      lvl = med;
      it[1] = false;
    }
    if (elements[0] == elements[2]) {
      lvl = (lvl == med) ? (high) : (med);
      it[2] = false;
    }
    if (!it[1]) {
      lvl = low;
      if (!it[2] && elements[1] == elements[2]) {
	lvl = med;
	it[2] = false;
      }
    }
  }
  
  double	Explode::getSpread(Effects::type t){
    if (t == Effects::Glyph)
      return (1.f);
    else if (t != Effects::Electricity)
      return (1.5);
    return (2);
  }

  std::string	Explode::serialization() {
    return (Tokenizer::serialize("Explode", untilBOOM,
				 elements[0], elements[1], elements[2]));
  }

  void		Explode::setBySerial(const Tokenizer& t) {
    untilBOOM	= t.get<Event::Time> (1);
    elements[0]	= static_cast<Component::Effects::type>(t.get<int>(3));
    elements[1]	= static_cast<Component::Effects::type>(t.get<int>(3));
    elements[2]	= static_cast<Component::Effects::type>(t.get<int>(3));
  }
};
