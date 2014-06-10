#include "animatedVertex.hh"

namespace object3d {
  animatedVertex::animatedVertex(char* model, double scale)
    : _scale(scale) {
    if (_model.load(model) == false) {
      std::cerr << "can't load model :" << model << std::endl;
      /* better throw here */
      return ;
    }
  }

  animatedVertex::~animatedVertex() {}

  void	animatedVertex::setPosition(int x, int y) {
    translate(glm::vec3(x, y, 0));
  }

  void	animatedVertex::setDirection(double, double) {
    /* I'll need help!!!! */
  }

  void	animatedVertex::draw(gdl::AShader &shader, gdl::Clock const& clock) {
    _model.draw(shader, getTransformation(), clock.getElapsed());
  }

};
