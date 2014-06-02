#include <iostream>
#include "GameEngine.hh"
#include "Tokenizer.hpp"

int main(){
  new Engine::Game(new Event::Dispatcher, new Engine::Graphic);
  enum toto { ture, falsea } t = falsea;

  Tokenizer tt (Tokenizer::subserialize(t));
  t = static_cast<enum toto>(tt.get<int>(0));
  std::cout << Tokenizer::subserialize(t) << t;
}
