#ifndef __GRAPHIQUEENGINE_H__
# define __GRAPHIQUEENGINE_H__

#include <Game.hh>
#include <SdlContext.hh>
#include <iostream>

#include "AObject.hh"
#include "Event.hpp"

namespace Engine{
  class Graphic : public gdl::Game{
  private: 
    gdl::SdlContext _context; 
    gdl::Clock _clock; 
    gdl::Input _input; 
    gdl::BasicShader _shader; 
    std::list<object3d::AObject*> _objects; 

  private:
    Event::Dispatcher*	dispatcher;
    bool		_quit;

  public:
    Graphic(Event::Dispatcher*);
    ~Graphic();

  public:
    void addObject(object3d::AObject*);
    void subObject(object3d::AObject*);

  public:
    bool initialize() {return (true);}
    bool update() {return (true);}
    void draw() {}
  };
};

#endif
