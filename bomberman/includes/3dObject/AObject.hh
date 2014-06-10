#ifndef __AOBJECT_H__
# define __AOBJECT_H__

#include <SdlContext.hh>
#include <OpenGL.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace object3d {
  class AObject{
  public:
    AObject();
    virtual ~AObject() {}

  public:
    void	draw(gdl::AShader &shader, gdl::Clock const& clock);

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

#endif
