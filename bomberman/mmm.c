#include <typeinfo>
#include <iostream>
#include "includes/Tokenizer.hpp"
int main() {
  std::cout << Tokenizer::serialize("toto", 4, 5, "tata", 6, 6.4) << std::endl;
  std::cout << Tokenizer::serialize("toto", 4, 5, "tata", 6, 6.4) << std::endl;
  std::cout << Tokenizer::serialize("toto", "je", "t'en", "prout", 4.5, -3) << std::endl;

  Tokenizer t(Tokenizer::serialize("toto", 4, 5, "tata", 6, 6.4));

  std::cout << t.get<int>(2) << std::endl;
}
