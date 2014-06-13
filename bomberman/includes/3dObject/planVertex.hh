#ifndef __PLANVERTEX_H__
# define __PLANVERTEX_H__

# include <iostream>
# include "AObject.hh"

namespace object3d {
  class planVertex : public object3d::AObject {
  private:
    gdl::Texture _texture;
    gdl::Geometry _geometry;
    float _speed;

  public:
    planVertex(const char* texture, int x, int y, int tx = 0, int ty = 0);
    virtual ~planVertex() {}

  public:
    void	draw(gdl::AShader &shader, gdl::Clock const& clock);
  };
};

#endif
