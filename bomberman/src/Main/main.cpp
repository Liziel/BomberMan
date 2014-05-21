
#include	<cstdlib>
#include	"GameEngine.hpp"

int main()  /* Main de test */
{
	GameEngine engine;

	if (engine.initialize() == false)
		return (EXIT_FAILURE);

	while (engine.update() == true)
		engine.draw();

	return EXIT_SUCCESS;
}
