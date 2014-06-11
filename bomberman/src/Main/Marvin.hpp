
#include	"AObject.hpp"

class Marvin : public AObject 
{ 
private:
  gdl::Model		_Model;
  float			_speed;
	
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
		// _Model.createSubAnim(0, "run", 30, 65);
		// _Model.createSubAnim(0, "decelerate", 66, 100);
		_Model.setCurrentSubAnim("run");
		// _Model.setCurrentAnim(0);
		scale(glm::vec3(0.025f));
		return (true);
	}

	virtual void update(gdl::Clock const &clock, gdl::Input &input)
	{
		if (input.getKey(SDLK_DOWN) && input.getKey(SDLK_RIGHT))
		{
			rotate(glm::vec3(0, 22.5, 0), 10);
			translate(glm::vec3(-4, 0, -4) * static_cast<float>(clock.getElapsed()) * _speed); 
		}
		else if (input.getKey(SDLK_DOWN) && input.getKey(SDLK_LEFT))
		{
			rotate(glm::vec3(0, -22.5, 0), 10);
			translate(glm::vec3(4, 0, -4) * static_cast<float>(clock.getElapsed()) * _speed); 
		}
		else if (input.getKey(SDLK_UP) && input.getKey(SDLK_RIGHT))
		{
			rotate(glm::vec3(0, 67.5, 0), 10);
			translate(glm::vec3(-4, 0, 4) * static_cast<float>(clock.getElapsed()) * _speed); 
		}
		else if (input.getKey(SDLK_UP) && input.getKey(SDLK_LEFT))
		{
			rotate(glm::vec3(0, -67.5, 0), 10);
			translate(glm::vec3(4, 0, 4) * static_cast<float>(clock.getElapsed()) * _speed); 
		}
		else if (input.getKey(SDLK_DOWN))
		{
			rotate(glm::vec3(0, 90, 0), 10);
			translate(glm::vec3(0, 0, -4) * static_cast<float>(clock.getElapsed()) * _speed); 
		}
		else if (input.getKey(SDLK_UP))
		{
			rotate(glm::vec3(0, 0, 0), 10);
			translate(glm::vec3(0, 0, 4) * static_cast<float>(clock.getElapsed()) * _speed); 
		}
		else if (input.getKey(SDLK_RIGHT))
		{
			rotate(glm::vec3(0, -45, 0), 10);
			translate(glm::vec3(-4, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed); 			
		}
		else if (input.getKey(SDLK_LEFT))
		{
			rotate(glm::vec3(0, 45, 0), 10);
			translate(glm::vec3(4, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed); 
		}
	}
	
	virtual void draw(gdl::AShader &shader, gdl::Clock const &clock) 
	{
		_Model.draw(shader, getTransformation(), clock.getElapsed());
	}
};
