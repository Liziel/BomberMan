#include "Component.hh"

namespace Component {
  class menuSuperior {
    Entity::GameObject* _menuPrincipal;
  public:
    menuSuperior(Event::Dispatcher* _d, Entity::Factory* _f);
    ~menuSuperior();

  };
};
