#include "cubeVertex.hh"

namespace object3d {
  cubeVertex::cubeVertex(char* texture) : _speed(10.f) {
    if (_texture.load(texture) == false) { 
      std::cerr << "Error : Failed to load texture" << std::endl; 
      return ;
    }
    _geometry.setColor(glm::vec4(1, 0, 0, 1)); 
		
    _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5)); 
    _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5)); 
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5)); 
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5)); 
		
    _geometry.pushUv(glm::vec2(0.0f, 0.0f)); 
    _geometry.pushUv(glm::vec2(1.0f, 0.0f)); 
    _geometry.pushUv(glm::vec2(1.0f, 1.0f)); 
    _geometry.pushUv(glm::vec2(0.0f, 1.0f)); 
		
    _geometry.setColor(glm::vec4(1, 1, 0, 1));  
		
    _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5)); 
    _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5)); 
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5)); 
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5)); 
		
    _geometry.pushUv(glm::vec2(0.0f, 0.0f)); 
    _geometry.pushUv(glm::vec2(1.0f, 0.0f)); 
    _geometry.pushUv(glm::vec2(1.0f, 1.0f)); 
    _geometry.pushUv(glm::vec2(0.0f, 1.0f)); 
		
    _geometry.setColor(glm::vec4(0, 1, 1, 1)); 
		
    _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5)); 
    _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5)); 
    _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5)); 
    _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5)); 
		
    _geometry.pushUv(glm::vec2(0.0f, 0.0f)); 
    _geometry.pushUv(glm::vec2(1.0f, 0.0f)); 
    _geometry.pushUv(glm::vec2(1.0f, 1.0f)); 
    _geometry.pushUv(glm::vec2(0.0f, 1.0f)); 
		
    _geometry.setColor(glm::vec4(1, 0, 1, 1)); 
		
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5)); 
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5)); 
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5)); 
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5)); 
		
    _geometry.pushUv(glm::vec2(0.0f, 0.0f)); 
    _geometry.pushUv(glm::vec2(1.0f, 0.0f)); 
    _geometry.pushUv(glm::vec2(1.0f, 1.0f)); 
    _geometry.pushUv(glm::vec2(0.0f, 1.0f)); 
		
    _geometry.setColor(glm::vec4(0, 1, 0, 1)); 
		
    _geometry.pushVertex(glm::vec3(0.5, 0.5, 0.5)); 
    _geometry.pushVertex(glm::vec3(0.5, 0.5, -0.5)); 
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5)); 
    _geometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5)); 
		
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
		
    _geometry.setColor(glm::vec4(0, 0, 1, 1));
		
    _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
    _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
    _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
		
    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
		
    _geometry.build();
  };

  void	cubeVertex::setPosition(int,int,cubeVertex::Layer) {}

  void	cubeVertex::draw(gdl::AShader& shader) {
    _texture.bind();
    _geometry.draw(shader, getTransformation(), GL_QUADS);
  }
};