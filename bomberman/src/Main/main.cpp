#include <OpenGL.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SdlContext.hh>
#include <unistd.h>

int main()  /* Main de test */
{
	gdl::SdlContext myContext;
	gdl::Geometry 	myGeometry;
	gdl::Texture	myTexture;

	myContext.start(600, 400, "Bomberman");
	if (myTexture.load("./src/Textures/wall_512_1_05.tga") == false) 
	{ 
		std::cerr << "Cannot load the cube texture" << std::endl; 
		return (false); 
	} 
	
	myGeometry.setColor(glm::vec4(1, 0, 0, 1)); 

	myGeometry.pushVertex(glm::vec3(0.5, -0.5, 0.5)); 
	myGeometry.pushVertex(glm::vec3(0.5, 0.5, 0.5)); 
	myGeometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5)); 
	myGeometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5)); 

	myGeometry.pushUv(glm::vec2(0.0f, 0.0f)); 
	myGeometry.pushUv(glm::vec2(1.0f, 0.0f)); 
	myGeometry.pushUv(glm::vec2(1.0f, 1.0f)); 
	myGeometry.pushUv(glm::vec2(0.0f, 1.0f)); 

	myGeometry.setColor(glm::vec4(1, 1, 0, 1)); 

	myGeometry.pushVertex(glm::vec3(0.5, -0.5, -0.5)); 
	myGeometry.pushVertex(glm::vec3(0.5, 0.5, -0.5)); 
	myGeometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5)); 
	myGeometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5)); 

	myGeometry.pushUv(glm::vec2(0.0f, 0.0f)); 
	myGeometry.pushUv(glm::vec2(1.0f, 0.0f)); 
	myGeometry.pushUv(glm::vec2(1.0f, 1.0f)); 
	myGeometry.pushUv(glm::vec2(0.0f, 1.0f)); 

	myGeometry.setColor(glm::vec4(0, 1, 1, 1)); 

	myGeometry.pushVertex(glm::vec3(0.5, -0.5, -0.5)); 
	myGeometry.pushVertex(glm::vec3(0.5, 0.5, -0.5)); 
	myGeometry.pushVertex(glm::vec3(0.5, 0.5, 0.5)); 
	myGeometry.pushVertex(glm::vec3(0.5, -0.5, 0.5)); 

	myGeometry.pushUv(glm::vec2(0.0f, 0.0f)); 
	myGeometry.pushUv(glm::vec2(1.0f, 0.0f)); 
	myGeometry.pushUv(glm::vec2(1.0f, 1.0f)); 
	myGeometry.pushUv(glm::vec2(0.0f, 1.0f)); 

	myGeometry.setColor(glm::vec4(1, 0, 1, 1)); 

	myGeometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5)); 
	myGeometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5)); 
	myGeometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5)); 
	myGeometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5)); 

	myGeometry.pushUv(glm::vec2(0.0f, 0.0f)); 
	myGeometry.pushUv(glm::vec2(1.0f, 0.0f)); 
	myGeometry.pushUv(glm::vec2(1.0f, 1.0f)); 
	myGeometry.pushUv(glm::vec2(0.0f, 1.0f)); 

	myGeometry.setColor(glm::vec4(0, 1, 0, 1)); 

	myGeometry.pushVertex(glm::vec3(0.5, 0.5, 0.5)); 
	myGeometry.pushVertex(glm::vec3(0.5, 0.5, -0.5)); 
	myGeometry.pushVertex(glm::vec3(-0.5, 0.5, -0.5)); 
	myGeometry.pushVertex(glm::vec3(-0.5, 0.5, 0.5)); 

	myGeometry.pushUv(glm::vec2(0.0f, 0.0f)); 
	myGeometry.pushUv(glm::vec2(1.0f, 0.0f));  

	myGeometry.pushUv(glm::vec2(1.0f, 1.0f)); 
	myGeometry.pushUv(glm::vec2(0.0f, 1.0f)); 

	myGeometry.setColor(glm::vec4(0, 0, 1, 1)); 

	myGeometry.pushVertex(glm::vec3(0.5, -0.5, -0.5)); 
	myGeometry.pushVertex(glm::vec3(0.5, -0.5, 0.5)); 
	myGeometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5)); 
	myGeometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5)); 

	myGeometry.pushUv(glm::vec2(0.0f, 0.0f)); 
	myGeometry.pushUv(glm::vec2(1.0f, 0.0f)); 
	myGeometry.pushUv(glm::vec2(1.0f, 1.0f)); 
	myGeometry.pushUv(glm::vec2(0.0f, 1.0f)); 

	myGeometry.build();
	myTexture.bind();
	myGeometry.draw(shader, getTransformation(), GL_QUADS); 
	while (42)
	{
		sleep(1);
	}
	return (0);
}
