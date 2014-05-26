#ifndef __TOKENIZE_H__
# define __TOKENIZE_H__

# include <tuple>
# include <string>
# include <sstream>
# include <vector>

namespace utilsTokenizer{
  inline std::string	gen() { return (""); }

  template<class U>
  std::string conv(U t){ return (std::to_string(t)); }

  template<>
  inline std::string conv<const char*>(const char* t){ return (std::string(t)); }

  template<>
  inline std::string conv<std::basic_string<char>>(std::basic_string<char> t){ return (t); }

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
  template<typename... U>
  static std::string	subserialize(U... argues) {
    return (utilsTokenizer::gen(argues...));
  }

private:
  std::vector<std::string>	_c;
  int				size;

public:
  int		getSize() const { return (size); }
  Tokenizer(const std::string& serial) {
    std::istringstream f(serial);
    std::string s;
    while (std::getline(f, s, ':')) {
      _c.push_back(s);
      size += 1;
    }
  }

  template<class U>
  U	get(int n) const;
};

template<>
inline const char*	Tokenizer::get<const char*>(int n) const{
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


#endif
