#ifndef __ANIMATEDVERTEX_H__
# define __ANIMATEDVERTEX_H__

# include "AObject.hh"

namespace object3d {
  class animatedVertex : public AObject {
  protected:
    gdl::Model	_model;
    double	_scale;

  public:
    animatedVertex(const char* model, double _sc)
      : _scale(_sc) {
      if (_model.load(model) == false) {
	std::cerr << "can't load model :" << model << std::endl;
	return ;
      }
      scale(glm::vec3(_scale,_scale,_scale));
    }

    ~animatedVertex() {}

  public:
    void	setPosition(double x, double y) {
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
