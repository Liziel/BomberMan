#include "Manager.hh"

namespace Engine{
  /* ## Manager ## */
  Manager::Manager(ArgsParsing& parsing)
    : data(new Component::Pool()),
      dispatcher(new Event::Dispatcher()),
      graphic(new Engine::Graphic(parsing)),
      game(new Engine::Game(dispatcher, graphic, data))
  {}
  Manager::~Manager() {
    delete dispatcher;
    delete graphic;
    delete data;
    delete game;
  }

  void	Manager::start(void) {
    Engine::Game::Delay*	delay = game->delayAllocator();
    try {
      while (1) {
	game->refresh();
	delay(100);
      }
    } catch (const std::exception& e) {
      std::cerr << "exception non-catched :" << e.what() << std::endl;
    }
  }
};
