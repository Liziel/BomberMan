#include "Explode.hh"

namespace Component{
  Explode::Explode(Entity::GameObject* _p) : Component::abstract(_p), untilBOOM(-1), exploding(false) {
    attachCallback(Event::Info::Clock,
		   new Event::FixedCallback([this, _p] (Event::Data&) {
		       std::cout << untilBOOM << std::endl;
		       if (!untilBOOM) {
			 delete _p;
			 return ;
		       }
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

		       if (exploding)
			 return ;
		       _p->getPosition(x, y);
		       if (event->x == static_cast<int>(x) && event->y == static_cast<int>(y))
			 EXPLODE(_p);
		     }));
  }

  void	Explode::EXPLODE(Entity::GameObject* _p){
    double x;
    double y;

    exploding = true;
    _p->getPosition(x, y);
    attachCallback(Event::Info::Colliding,
		   new Event::FixedCallback([this, x, y] (Event::Data& e) {
		       Event::Type::Colliding* _ =
			 reinterpret_cast<Event::Type::Colliding*>(&e);

		       std::cout << _->endX << x <<std::endl;
		       std::cout << _->endY << y <<std::endl;
		       if (_->endX > x) {
			 for (; _->endX >= x; --_->endX)
			   dispatch(_->endX, y);
			 return ;
		       }
		       if (_->endX < x) {
			 for (; _->endX <= x; ++_->endX)
			   dispatch(_->endX, y);
			 return ;
		       }
		       if (_->endY > y) {
			 for (; _->endY >= y; --_->endY)
			   dispatch(x, _->endY);
			 return ;
		       }
		       if (_->endY < y) {
			 for (; _->endY <= y; ++_->endY)
			   dispatch(x, _->endY);
			 return ;
		       }
		     }));
    double spread = getSpread(elements[0]) +
      getSpread(elements[1]) +
      getSpread(elements[2]) - 1;
    std::cout << spread << std::endl;
    dispatchSelf(new Event::Type::RequireExplosion(x,y, spread, 0));
    dispatchSelf(new Event::Type::RequireExplosion(x,y, -spread, 0));
    dispatchSelf(new Event::Type::RequireExplosion(x,y, 0, -spread));
    dispatchSelf(new Event::Type::RequireExplosion(x,y, 0, spread));
    dispatch(x, y);
    delete _p;
  }

  void	Explode::dispatch(int x, int y) {
    std::function<void(Effects::type, Effects::level)> mad =
      [this, x, y] (Effects::type t, Effects::level lvl) {
      if (t == Effects::Fire)
	dispatchAll(new Event::Type::FireExplosion(x, y, lvl));
      if (t == Effects::Ice)
	dispatchAll(new Event::Type::IceExplosion(x, y, lvl));
      if (t == Effects::Life)
	dispatchAll(new Event::Type::LifeExplosion(x, y, lvl));
      if (t == Effects::Electricity)
	dispatchAll(new Event::Type::ElectricityExplosion(x, y, lvl));
      if (t == Effects::Glyph)
	dispatchAll(new Event::Type::GlyphExplosion(x, y, lvl));
    };
    std::array<bool, 3> it = {true, false, false};
    Effects::level	lvl = Effects::low;

    if (elements[0] == elements[1]) {
      lvl = Effects::med;
      it[1] = false;
    }
    if (elements[0] == elements[2]) {
      lvl = (lvl == Effects::med) ? (Effects::high) : (Effects::med);
      it[2] = false;
    }
    mad(elements[0], lvl);
    if (!it[1]) {
      lvl = Effects::low;
      if (!it[2] && elements[1] == elements[2]) {
	lvl = Effects::med;
	it[2] = false;
      }
      mad(elements[1], lvl);
    }
    if (!it[2])
      mad(elements[2], Effects::low);
    dispatchAll(new Event::Type::Explosion(x, y));
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
    Component::Effects::type swap;
    untilBOOM	= t.get<Event::Time> (1);
    elements[0]	= static_cast<Component::Effects::type>(t.get<int>(2));
    elements[1]	= static_cast<Component::Effects::type>(t.get<int>(3));
    elements[2]	= static_cast<Component::Effects::type>(t.get<int>(4));
    if (elements[2] == Component::Effects::Glyph) {
      swap = elements[0];
      elements[0] = elements[2];
      elements[2] = swap;
    }
    if (elements[1] == Component::Effects::Glyph) {
      swap = elements[0];
      elements[0] = elements[1];
      elements[1] = swap;
    }
  }
};
