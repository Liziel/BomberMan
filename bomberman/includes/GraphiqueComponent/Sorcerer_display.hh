#include ""

namespace Component{
  SorcererDisplay::SorcererDisplay(Entity::GameObject* _p, Engine::Graphique*)
    : Component::abstract(_p), ... () {

    attachCallback(Event::Type::isMute,
		   new Event::FixedCallback([this](Event::Data& e) {
		       Event::Type::isOnFire* event = reinterpret_cast<Event::Type::isOnFire*>(&e);
		       this->isOnFire = event->state;
		     }));

    attachCallback( Event::Type::Refresh,
		    new Event::FixedCallback([this](Event::Data&) {
			this->draw();
		      }));
  }

  std::string	Sorcerer::serialization() {
    return (Tokenizer::serialize("SorcererDisplay", color, "nom", isOnfire, isOnIce));
  }

  void		Collider::Movable::setBySerial(const Tokenizer& t) {
    color = t.get<int>(1);
    nom = t.get<const char*>(2);
    isOnfire = t.get<bool>(3);
  }

};
