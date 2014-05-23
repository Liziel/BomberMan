
#include <iostream>

template<int N>
struct toto {
  enum {value = N * toto<N - 1>::value};
};

template<>
struct toto<0>{
  enum {value = 1};
};

int main() {
  std::cout << toto<15>::value;
}
