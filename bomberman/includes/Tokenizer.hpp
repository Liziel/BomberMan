#ifndef __TOKENIZER_H__
# define __TOKENIZER_H__

# include <tuple>
# include <string>
# include <sstream>
# include <vector>

namespace utilsTokenizer{
  std::string	gen() { return (""); }

  template<class U>
  std::string conv(U t){ return (std::to_string(t)); }

  template<>
  std::string conv<const char*>(const char* t){ return (std::string(t)); }

  template<typename T, typename... U>
  std::string	gen(T first, U... argues) {
    return (":" + conv<T>(first) + gen(argues... ));
  }
};

class Tokenizer{

public:
  struct outOfRange : std::exception{
    const char* what() const noexcept { return ("tokenizer: getin' out of range..."); }
  };

public:
  template<typename... U>
  static std::string	serialize(const std::string& type, U... argues) {
    return (std::string(type) + utilsTokenizer::gen(argues...));
  }


private:
  std::vector<std::string>	_c;
public:
  Tokenizer(const std::string& serial) {
    std::istringstream f(serial);
    std::string s;
    while (std::getline(f, s, ':')) {
      _c.push_back(s);
    }
  }

  template<class U>
  U	get(int n) const;
};

template<class U>
U	Tokenizer::get(int n) const {
  int t = 0;
  
  for (auto string : _c){
    if (t == n){
      std::istringstream myString(string);
      U value;
      myString >> value;
      return (value);
    }else
      ++t;
  }
  throw Tokenizer::outOfRange();
  return (U());
}

template<>
const char*	Tokenizer::get<const char*>(int n) const{
  int t = 0;

  for (auto string : _c){
    if (t == n){
      return (string.c_str());
    }else
      ++t;
  }
  throw Tokenizer::outOfRange();
  return (NULL);
}

#endif
