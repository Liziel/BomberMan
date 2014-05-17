#include "Component.hh"

Component::Component();
Component::~Component()
{
  for (auto _cb : _CallbackArray){
    _Dispatch->unsetCallbackForId(_cb.first, _cb.second->getId());
    delete _cb.second;
  }
}
