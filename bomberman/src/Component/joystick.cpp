#include "joystick.hh"


namespace Component{
  JoystickManager::joystick::joystick(Entity::GameObject* _p, SDL_Joystick* _k)
    : Component::abstract(_p), _joystick(_k) {
    keyState = {
      std::pair<int,bool>(4, false), /* movement */
      std::pair<int,bool>(6, false),
      std::pair<int,bool>(5, false),
      std::pair<int,bool>(7, false),

      std::pair<int,bool>(9, false), /* pose bomb || enter */

      std::pair<int,bool>(11, false), /* elements */
      std::pair<int,bool>(13, false),
      std::pair<int,bool>(15, false),
      std::pair<int,bool>(14, false),
      std::pair<int,bool>(12, false)
    };
    attachCallback(Event::Info::Clock,
		   new Event::FixedCallback([this](Event::Data&) {
		       if (!_joystick)
			 return ;
		       int	itt = 0;

		       for (auto key : keyState) {
			 if (SDL_JoystickGetButton(_joystick, key.first) != key.second) {
			   dispatchSelf(new Event::Type::Keyboard(itt, !key.second));
			   key.second = !key.second;
			 }
			 ++itt;
		       }
		     }));
  }
  JoystickManager::joystick::~joystick() {}

  

  JoystickManager::JoystickManager(Event::Dispatcher* _d)
    : Component::Superior(_d){
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
  }
  JoystickManager::~JoystickManager() {}
  SDL_Joystick* JoystickManager::getJoystick(int _k) {
    if (_k > SDL_NumJoysticks())
      return (NULL);
    if (!_joystick[_k])
      _joystick[_k] = SDL_JoystickOpen(_k);
    return (_joystick[_k]);
  }
  std::string JoystickManager::joystick::serialization() {
    return (Tokenizer::serialize("JoystickManager"));
  }

  void  JoystickManager::joystick::setBySerial(const Tokenizer& t) {
    
  }

};
