#ifndef __KEYBOARD_H__
# define __KEYBOARD_H__

#include "Component.hh"

namespace Component{
  template<int N>
  class Keyboard : public Component::abstract{
  private:
    std::array<char, N>		configuration;
    void			getKeyInTab();

  public:
    Keyboard(Entity::GameObject* _p, std::array<char, N> _a)
      : Component::abstract(_p),
	configuration(_a) {
      attachCallback(Event::Info::Clock,
		     new Event::FixedCallback([this](Event::Data&) {
			 getKeyInTab();
		       }));
    }
    
    inline std::string	subSerial(int n) {
      return (Tokenizer::subserialize<int, std::string>(configuration[N - n], subSerial(n - 1)));
    }

    std::string	serialization() {
      return (Tokenizer::serialize("Keyboard", N, subSerial(N)));
    }

    void		setBySerial(const Tokenizer& t) {
      for (int n = 2; n < N; n++)
	configuration[n - 1] = t.get<int>(n);
    }
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
      Keyboard(int k, bool s)
	: Event::Data(Event::Info::Keyboard, sizeof(struct Keyboard), false),
	  key(k), state(s) {}
      int key;
      bool state;
    };
# endif

  };
};

#endif
