
#include	"AObject.hpp"

class Marvin : public AObject 
{ 
private:
	gdl::Model		_Model;
	float	_speed;
	
public:
	Marvin(){}
	virtual ~Marvin(){} 
	
	virtual bool initialize() 
	{
		_speed = 10.0f;
		if (_Model.load("./lib/Gdl_lib/assets/marvin.fbx") == false) 
		{
			std::cerr << "Error : Failed to load model" << std::endl; 
			return (false);
		}
		// _Model.createSubAnim(0, "accelerate", 0, 33);
		// _Model.createSubAnim(0, "run", 33, 66);
		// _Model.createSubAnim(0, "decelerate", 66, 100);
		// _Model.setCurrentSubAnim("run");
		_Model.setCurrentAnim(0);
		scale(glm::vec3(0.025f));
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
		_Model.draw(shader, getTransformation(), clock.getElapsed());
	}
};