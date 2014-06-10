#include "GraphicEngine.hh"

namespace Engine{
  Graphic::Graphic() {
    if (!_context.start(800, 600, "My bomberman!"))
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
    glm::mat4 projection;
    glm::mat4 transformation;
    projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f); 
    transformation
      = glm::lookAt(glm::vec3(0, 10, -30), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); 

    _shader.bind();
    _shader.setUniform("view", transformation);
    _shader.setUniform("projection", projection);
  }
  Graphic::~Graphic() {}

  void	Graphic::addObject(object3d::AObject* o) { _objects.push_back(o); }
  void	Graphic::subObject(object3d::AObject* o) {
    for (auto itt = _objects.begin(); itt != _objects.end(); ++itt) {
      if (*itt == o)
	_objects.erase(itt);
    }
  }
};
