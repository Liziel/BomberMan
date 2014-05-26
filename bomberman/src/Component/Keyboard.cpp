#include "Keyboard.hh"

namespace Component{
  Keyboard::Keyboard(Entity::GameObject* _p, std::array<char, 10> _a)
    : Component::abstract(_p),
      configuration(_a) {}

  template<int n>
  inline std::string	Keyboard::subSerial() {
    return (Tokenizer::subserialize<int, std::string>(configuration[10 - n], subSerial<n - 1>()));
  }

  template<>
  inline std::string	Keyboard::subSerial<0>() {
    return ("");
  }

  std::string	Keyboard::serialization() {
    return (Tokenizer::serialize("Keyboard", subSerial<10>()));
  }

  void		Keyboard::setBySerial(const Tokenizer& t) {
    for (int n = 1; n < 11; n++)
      configuration[n - 1] = t.get<int>(n);
  }

};
