#include "Runic.hh"


namespace Component{
  Runic::Runic(Entity::GameObject* _p)
    : Component::abstract(_p), runeDuration(0), attachedElement(0), attachableElement(0) {
    
  }
};
