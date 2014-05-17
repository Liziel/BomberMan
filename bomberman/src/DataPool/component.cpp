#include "Component.hh"

Component::Component() {}
Component::Component(GraphicEngine* GrEngine, EventDispatcher* Dispatch)
  : _GrEngine(GrEngine), _Dispatch(Dispatch) {}
Component::~Component() {
  for (auto _cb : _CallbackArray) {
    _Dispatch->unsetCallbackForId(_cb.first, _cb.second->getId());
    delete _cb.second;
  }
}

void	Component::addCallback(Event::Info::Type type,
			       Event::Callback* callback,
			       Event::Info::Priority _p) {
  _CallbackArray.push_back(std::pair< Event::Info::Type, Event::Callback* >
			   (type, callback));
  _Dispatch.addCallbackOnEvent(type, callback, _p);
}

void	Component::unsetCallback(Event::Callback*)
