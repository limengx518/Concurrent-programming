// mem_fn example
#include <iostream>     // std::cout
#include <functional>   // std::mem_fn

struct int_holder {
  int value;
  int triple() {return 3*value;}
};

int main () {
  int_holder five {5};

  // call member directly:
  std::cout << five.triple() << '\n';

  // same as above using a mem_fn:
  auto triple = std::mem_fn (&int_holder::triple);
  std::cout << triple(five) << '\n';

  return 0;
}
