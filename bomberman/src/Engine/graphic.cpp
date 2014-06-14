#include "GraphicEngine.hh"
#include "AObject.hh"
#include "planVertex.hh"
#include "ziggsAnimated.hpp"

namespace Engine{
  Graphic::Graphic(Event::Dispatcher* _d)
    : dispatcher(_d), _quit(false) {
    if (!_context.start(WINDOW_X, WINDOW_Y, "My bomberman!"))
      return ;
    glEnable(GL_DEPTH_TEST);
    if ((!_shader.load("./lib/Gdl_lib/shaders/basic.fp", GL_FRAGMENT_SHADER)) ||
	(!_shader.load("./lib/Gdl_lib/shaders/basic.vp", GL_VERTEX_SHADER))   ||
	(!_shader.build()))
      {
	std::cout << "Error : Failed to load Shaders" << std::endl;
	return;
      }

    /* is it correct? */

    _shader.bind();

    dispatcher
      ->addCallbackOnEvent(Event::Info::Refresh,
			  new Event::FixedCallback([this] (Event::Data&) {
			      if (_input.getKey(SDLK_ESCAPE) ||
				  _input.getInput(SDL_QUIT)) {
				_quit = true;
				return ;
			      }
			      _context.updateClock(_clock);
			      _context.updateInputs(_input);
			    }), Event::Info::high
			   );

    dispatcher
      ->addCallbackOnEvent(Event::Info::Refresh,
			   new Event::FixedCallback([this] (Event::Data&) {
			       glm::mat4 projection;
			       projection = glm::perspective(60.0f, WINDOW_X / WINDOW_Y, 0.1f, 100.0f); 
			       _shader.setUniform("projection", projection);
			       glm::mat4 transformation;
			       transformation = glm::lookAt(glm::vec3(0, -10.0, -((12.0 * 1.41f) / (tan(30 * 3.14159 / 180)))), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
			       _shader.setUniform("view", transformation);
				   glClear(GL_COLOR_BUFFER_BIT
				       | GL_DEPTH_BUFFER_BIT);
			       _shader.bind();
			        for (auto ob : _objects)
				  ob->draw(_shader, _clock);
			       //_context.flush();
			     }), Event::Info::medium
			   );
    dispatcher
      ->addCallbackOnEvent(Event::Info::Refresh,
			   new Event::FixedCallback([this] (Event::Data&) {
			       glm::mat4 projection;
			       projection = glm::ortho(0.0f, WINDOW_X, WINDOW_Y, 0.0f, -1.0f, 1.0f); 
			       _shader.setUniform("projection", projection);
			       _shader.setUniform("view", glm::mat4(1));

			       for (auto ob : _HUDobjects){
				 ob->draw(_shader, _clock);
			       }
			       _context.flush();
			     }), Event::Info::low
			   );
  }

  Graphic::~Graphic() {}

  void	Graphic::addObject(object3d::AObject* o) {
    if (o)
      _objects.push_back(o);
  }

  void	Graphic::addHudObject(object3d::AObject* o) { 
    if (o)
      _HUDobjects.push_back(o);
  }

  void	Graphic::subObject(object3d::AObject* o) {
    for (auto itt = _objects.begin(); itt != _objects.end(); ++itt) {
      if (*itt == o)
	itt = _objects.erase(itt);
    }
  }

  void	Graphic::subHudObject(object3d::AObject* o) {
    for (auto itt = _HUDobjects.begin(); itt != _HUDobjects.end(); ++itt) {
      if (*itt == o)
	_HUDobjects.erase(itt);
    }
  }

  bool	Graphic::getQuit(void) {
    return (_quit);
  }
};
