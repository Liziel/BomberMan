#include "animatedVertex.hh"

namespace object3d {
  animatedVertex::~animatedVertex() {}

  void	animatedVertex::setPosition(int x, int y) {
  }

  void	animatedVertex::setDirection(double, double) {}

  void	animatedVertex::setAnimation(std::string animation) {
      _model.setCurrentSubAnim(animation);
  }

  void	animatedVertex::draw(gdl::AShader &shader, gdl::Clock const& clock) {
    _model.draw(shader, getTransformation(), clock.getElapsed());
  }
};
