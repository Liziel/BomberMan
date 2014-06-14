#ifndef __GRAPHIQUEENGINE_H__
# define __GRAPHIQUEENGINE_H__

#include <Game.hh>
#include <SdlContext.hh>
#include <iostream>

#include <SdlContext.hh>
#include <OpenGL.hh>
#include <glm/gtc/matrix_transform.hpp>

#include "Event.hpp"

#define WINDOW_X 1600.0f
#define WINDOW_Y 900.0f

namespace object3d {
  class AObject;
};

namespace Engine{
  class Graphic : public gdl::Game{
  private: 
    gdl::SdlContext _context; 
    gdl::Clock _clock; 
    gdl::Input _input; 
    gdl::BasicShader _shader; 
    std::list<object3d::AObject*> _objects; 
    std::list<object3d::AObject*> _HUDobjects; 

  private:
    Event::Dispatcher*	dispatcher;

  public:
    Graphic(Event::Dispatcher*);
    ~Graphic();

  private:
    bool		_quit;
  public:
    bool		getQuit();

  public:
    void addObject(object3d::AObject*);
    void subObject(object3d::AObject*);
    void addHudObject(object3d::AObject*);
    void subHudObject(object3d::AObject*);

  public:
    bool initialize() {return (true);}
    bool update() {return (true);}
    void draw() {}

  public:
    gdl::BasicShader&	getShader(void);
    gdl::Clock&		getClock(void);
  };
};

#endif
