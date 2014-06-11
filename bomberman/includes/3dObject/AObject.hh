#ifndef __AOBJECT_H__
# define __AOBJECT_H__

#include "GraphicEngine.hh"

namespace object3d {
  class AObject{
  public:
    AObject();
    virtual ~AObject() {}

  public:
    virtual void draw(gdl::AShader &shader, gdl::Clock const& clock) = 0;

  public:
    void translate(glm::vec3 const &);
    void rotate(glm::vec3 const&, float);
    void scale(glm::vec3 const&);

    glm::mat4 getTransformation() ;

  protected:
    glm::vec3 _position; 
    glm::vec3 _rotation; 
    glm::vec3 _scale; 
  };
};

#include "animatedVertex.hh"

#endif
