#include "joystick.hh"


namespace Component{
  JoystickManager::joystick::joystick(Entity::GameObject* _p, SDL_Joystick* _k, int id)
    : Component::abstract(_p), _joystick(_k), _id(id) {

    joyState = {
      std::pair<int,bool>(1, 0),
      std::pair<int,bool>(0, 0),
    };

    keyState = {
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
		       std::cout << "my id is {" << _id << "}" << std::endl;
		       int	itt = 0;

		       for (auto &axe : joyState) {
			 double axis = SDL_JoystickGetAxis(_joystick, axe.first);
			 int state = (!axis) ? (0) : (axis / axis);
			 if (axis < 0)
			   state = -state;
			 axis = (axis < 0) ? (-axis) : (axis);
			 dispatchSelf(new Event::Type::speedAxeSetter(axis / 32768, !(axe.first)));
			 if (axe.second != state) {
			   dispatchSelf(new Event::Type::Keyboard(!(axe.first) * 2 + 0, state < 0));
			   dispatchSelf(new Event::Type::Keyboard(!(axe.first) * 2 + 1, state > 0));
			   axe.second = state;
			 }
		       }
		       for (auto &key : keyState) {
			 if (SDL_JoystickGetButton(_joystick, key.first) != key.second) {
			   dispatchSelf(new Event::Type::Keyboard(itt + 4, !key.second));
			   key.second = SDL_JoystickGetButton(_joystick, key.first);
			 }
			 ++itt;
		       }
		     }));
  }
  JoystickManager::joystick::~joystick() {}

  std::string JoystickManager::joystick::serialization()
  { return ("joystick" + std::to_string(_id)); }
  void	JoystickManager::joystick::setBySerial(const Tokenizer&) {}

  

  JoystickManager::JoystickManager() {
    _joystick = { NULL, NULL, NULL, NULL};
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
};
