
#include	<cstdlib>
#include	"GameEngine.hpp"
#include <OpenGL.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SdlContext.hh>
#include <unistd.h>

int main()  /* Main de test */
{
	GameEngine engine;

	if (engine.initialize() == false)
		return (EXIT_FAILURE);

	while (engine.update() == true)
		engine.draw();

	return EXIT_SUCCESS;
}
