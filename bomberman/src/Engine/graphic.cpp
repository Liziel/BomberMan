#include "GraphicEngine.hh"
#include "AObject.hh"
#include "planVertex.hh"

namespace Engine{
  Graphic::Graphic(Event::Dispatcher* _d)
    : dispatcher(_d), _quit(false) {
    if (!_context.start(1600, 900, "My bomberman!"))
      return ;
    glEnable(GL_DEPTH_TEST);
    if ((!_shader.load("./lib/Gdl_lib/shaders/basic.fp", GL_FRAGMENT_SHADER)) ||
	(!_shader.load("./lib/Gdl_lib/shaders/basic.vp", GL_VERTEX_SHADER))   ||
	(!_shader.build()))
      {
	std::cout << "Error : Failed to load Shaders" << std::endl;
	return;
      }
    addHudObject(new object3d::planVertex("img/preview.tga"));

    /* is it correct? */
    glm::mat4 transformation;
    transformation
      = glm::lookAt(glm::vec3(0, 10, -30),
		    glm::vec3(0, 0, 0),
		    glm::vec3(0, 1, 0)); 

    _shader.bind();
    _shader.setUniform("view", transformation);

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
			       projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f); 
			       _shader.setUniform("projection", projection);
			       
			       glClear(GL_COLOR_BUFFER_BIT
				       | GL_DEPTH_BUFFER_BIT);
			       _shader.bind();
			       for (auto ob : _objects)
				 ob->draw(_shader, _clock);
			       _context.flush();
			     }), Event::Info::low
			   );
    dispatcher
      ->addCallbackOnEvent(Event::Info::Refresh,
			   new Event::FixedCallback([this] (Event::Data&) {
			       glm::mat4 projection;
			       projection = glm::perspective(0.0f, 800.0f, 0.0f, 600.0f); 
			       _shader.setUniform("projection", projection);
			       
			       for (auto ob : _HUDobjects)
				 ob->draw(_shader, _clock);
			       _context.flush();
			     }), Event::Info::high
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
