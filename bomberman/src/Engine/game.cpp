#include "GameEngine.hh"


namespace Engine{

  /* ## Online Delay ## */
  OnlineDelay(const Socket::Select& slct) : select(slct) {}
  void	Engine::Game::OnlineDelay::operator()(unsigned int delay){
    select->readChange();
  };

  /* ## Game ## */
  
};
