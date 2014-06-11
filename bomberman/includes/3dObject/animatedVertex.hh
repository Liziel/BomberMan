#ifndef __ANIMATEDVERTEX_H__
# define __ANIMATEDVERTEX_H__

# include "AObject.hh"

namespace object3d {
  class animatedVertex : public AObject {
  protected:
    gdl::Model	_model;
    double	_scale;

  public:
    animatedVertex(char* model, double scale)
      : _scale(scale) {
      if (_model.load("tamere") == false) {
	std::cerr << "can't load model :" << model << std::endl;
	return ;
      }
    }

    ~animatedVertex() {}

  public:
    void	setPosition(int x, int y) {
      translate(glm::vec3(x, y, 0));
    }
    void	setDirection(double, double) {

    }
    void	setAnimation(std::string animation) {
      _model.setCurrentSubAnim(animation);
    }

  public:
    void	draw(gdl::AShader &shader, gdl::Clock const& clock) {
      _model.draw(shader, getTransformation(), clock.getElapsed());
    }
  };
};

#endif
