#ifndef __CUBEVERTEX_H__
# define __CUBEVERTEX_H__

# include <iostream>
# include "AObject.hh"

namespace object3d {
  class cubeVertex : public object3d::AObject {
  private:
    gdl::Texture _texture;
    gdl::Geometry _geometry;
    float _speed;

  public:
    cubeVertex(char* texture);
    virtual ~cubeVertex() {}

  public:
    enum Layer{Up, Ground};
    void setPosition(int x, int y, Layer = Up);

  public:
    void	draw(gdl::AShader &shader, gdl::Clock const& clock);
  };
};

#endif
