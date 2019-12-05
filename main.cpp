#include <iostream>
#include "list.h"

int main(void)
{
  // TEST
  auto l = list<int>();
  l.insert(new list<int>::node(new int(3)));
  l.insert(new list<int>::node(new int(5)));
  l.insert(new list<int>::node(new int(7)));
  l.insert(new list<int>::node(new int(9)));
  for (auto e : l) {
    std::cout << e << std::endl;
  }
  return 0;
}
