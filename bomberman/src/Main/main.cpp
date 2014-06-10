#include <iostream>
#include "GameEngine.hh"
#include "Tokenizer.hpp"

int main(){
  Engine::Game* game = new Engine::Game(new Event::Dispatcher, new Engine::Graphic);

  game->launch();
  return (0);
}
