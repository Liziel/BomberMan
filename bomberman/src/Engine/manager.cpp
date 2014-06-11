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
    dispatcher->dispatchEvent(new Event::
			      Type::beginGame(Component::Game::square, 10, 10, 1, 0));
    try {
      while (!graphic->getQuit()) {
	game->refresh();
      }
    } catch (const std::exception& e) {
      std::cerr << "exception non-catched :" << e.what() << std::endl;
    }
  }
};
