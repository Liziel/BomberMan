#include "menuSuperior.hh"
#include "EventType.hh"
#include "Entity.hh"

namespace Component {

  menuSuperior::menuSuperior(Event::Dispatcher* _d, Entity::Factory* _f){
    _d->addCallbackOnEvent(Event::Info::menuInstanciation,
			   new Event::FixedCallback([this, _f] (Event::Data&) {
			       _menuPrincipal = _f->allocateEntityByType("MenuPrincipal", true);

			     }));				    
  }
  menuSuperior::~menuSuperior(){

  }
}
