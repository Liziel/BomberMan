#ifndef __KEYBOARD_H__
# define __KEYBOARD_H__

#include "Component.hh"

namespace Component{
  class Keyboard : public Component::abstract{
  private:
    std::array<char, 10>	configuration;
    void			getKeyInTab();

  public:
    Keyboard(Entity::GameObject*, std::array<char, 10>);
    
  private:
    template<int U>
    std::string	subSerial();

  public:
    std::string serialization();
    void	setBySerial(const Tokenizer&);    
  };
};

namespace Event{
  namespace Type{

    struct ChangeKeyConfig : Event::Data{
      ChangeKeyConfig(std::array<char, 10> _c)
	: Event::Data(Event::Info::ChangeKeyConfig, sizeof(struct ChangeKeyConfig), false) {
	for (int i = 0; i < 10; ++i)
	  conf[i] = _c[i];
      }
      char	conf[10];
    };

# ifndef __ARENA_H__
    struct Keyboard : Event::Data{
      Keyboard(int k)
	: Event::Data(Event::Info::Keyboard, sizeof(struct Keyboard), false),
	  key(k) {}
      int key;
    };
# endif

  };
};

#endif
