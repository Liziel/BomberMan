#ifndef __ANIMATEDVERTEX_H__
# define __ANIMATEDVERTEX_H__

# include <iostream>
# include "AObject.hh"

namespace object3d {
  class animatedVertex : public AObject {
  protected:
    gdl::Model	_model;
    double	_scale;

  public:
    animatedVertex(char* model, double scale);
    virtual ~animatedVertex();

  public:
    void	setPosition(int x, int y);
    void	setDirection(double fX, double fY);
    virtual bool verifyAnimation(std::string) = 0;
    void	setAnimation(std::string animation);

  public:
    void	draw(gdl::AShader &shader, gdl::Clock const& clock);
  };
};

#endif
