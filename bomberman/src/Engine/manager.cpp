#include "Manager.hh"

namespace Engine{
  /* ## Manager ## */
  Manager::Manager()
    : dispatcher(new Event::Dispatcher()),
      graphic(new Engine::Graphic(dispatcher)),
      game(new Engine::Game(dispatcher, graphic))
  {}
  Manager::~Manager() {
    delete dispatcher;
    delete graphic;
    delete game;
  }

  void	Manager::start(void) {
    Uint32	time, spend;
    dispatcher->dispatchEvent(new Event::
			      Type::menuInstanciation(1));
    dispatcher->dispatchEvent(new Event::
    			      Type::beginGame(Component::Game::square, 10, 10, 1, 0));
    dispatcher->dispatchEvent(new Event::Type::PlantBomb(0,1,Component::Effects::Fire,Component::Effects::Fire,Component::Effects::Fire));
    //dispatcher->dispatchEvent(new Event::Type::EntitySerialize(Entity::game, &(std::cout)));
    try {
      while (!graphic->getQuit()) {
	time = SDL_GetTicks();
	game->refresh();
	spend = SDL_GetTicks();
	if (spend - time < 50)
	  SDL_Delay(50 - (spend - time));
      }
    } catch (const std::exception& e) {
      std::cerr << "exception non-catched :" << e.what() << std::endl;
    }
  }
};
