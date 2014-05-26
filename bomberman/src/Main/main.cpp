#include <iostream>
#include "Tokenizer.hpp"
#include "Keyboard.hh"

int main(){
  enum toto { ture, falsea } t = falsea;

  Tokenizer tt (Tokenizer::subserialize(t));
  t = static_cast<enum toto>(tt.get<int>(0));
  std::cout << Tokenizer::subserialize(t) << t;
}
