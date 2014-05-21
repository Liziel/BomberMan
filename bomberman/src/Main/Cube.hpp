
#include	"AObject.hpp"

class Cube : public AObject 
{ 
private:
	gdl::Texture _texture;
	gdl::Geometry _geometry;
	float _speed;
	
public:
	Cube(){}
	virtual ~Cube(){} 
	
	virtual bool initialize() 
	{
		_speed = 10.0f;
		
		if (_texture.load("./src/Textures/wall_512_4_05.tga") == false) 
		{
			std::cerr << "Error : Failed to load texture" << std::endl; 
			return (false);
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
		return (true);
	}
	
	virtual void update(gdl::Clock const &clock, gdl::Input &input) 
	{
		if (input.getKey(SDLK_DOWN))
			translate(glm::vec3(0, -1, 0) * static_cast<float>(clock.getElapsed()) * _speed); 
		if (input.getKey(SDLK_UP))
			translate(glm::vec3(0, 1, 0) * static_cast<float>(clock.getElapsed()) * _speed); 
		if (input.getKey(SDLK_RIGHT))
			translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed); 
		if (input.getKey(SDLK_LEFT))
			translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed); 
		if (input.getKey(SDLK_KP_PLUS))
			translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed); 
		if (input.getKey(SDLK_KP_MINUS))
			translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed); 
		if (input.getKey(SDLK_KP_1))
			rotate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed, 10);
		if (input.getKey(SDLK_KP_2))
			rotate(glm::vec3(0, 1, 0) * static_cast<float>(clock.getElapsed()) * _speed, 10);
		if (input.getKey(SDLK_KP_3))
			rotate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed, 10);
	}
	
	virtual void draw(gdl::AShader &shader, gdl::Clock const &clock) 
	{
		(void)clock;
		_texture.bind();
		_geometry.draw(shader, getTransformation(), GL_QUADS);
	}
};