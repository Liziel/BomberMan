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
			 EXPLODE();
		       }
		     }));
  }

  void	Explode::EXPLODE(){}

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
