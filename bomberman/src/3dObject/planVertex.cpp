#include "planVertex.hh"

namespace object3d {
  planVertex::planVertex(const char* texture, int x, int y, int tx, int ty) : _speed(10.f) {
    if (_texture.load(texture) == false) { 
      std::cerr << "Error : Failed to load texture" << std::endl; 
      return ;
    }		
    _geometry.pushVertex(glm::vec3(0, 0, 0)); 
    _geometry.pushVertex(glm::vec3(x, 0, 0)); 
    _geometry.pushVertex(glm::vec3(x, y, 0)); 
    _geometry.pushVertex(glm::vec3(0, y, 0)); 
		
    _geometry.pushUv(glm::vec2(0.0f, 1.0f)); 
    _geometry.pushUv(glm::vec2(1.0f, 1.0f)); 
    _geometry.pushUv(glm::vec2(1.0f, 0.0f)); 
    _geometry.pushUv(glm::vec2(0.0f, 0.0f)); 
		
    _geometry.build();
    translate(glm::vec3(tx, ty, 0));
  };

  void	planVertex::draw(gdl::AShader& shader, gdl::Clock const&) {
    _texture.bind();
    _geometry.draw(shader, getTransformation(), GL_QUADS);
  }
};
