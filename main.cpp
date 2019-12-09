#include <iostream>
#include "graph.h"

int main(void)
{
  // TEST
  int pairs[] = {
    4, 0, 1,
    8, 1, 2,
    4, 2, 5,
    7, 3, 2,
    9, 3, 4,
    14, 3, 5,
    10, 4, 5,
    2, 6, 5,
    8, 7, 0,
    11, 7, 1,
    1, 7, 6,
    2, 8, 2,
    6, 8, 6,
    7, 8, 7
  };
  graph g(true, 9, 14, pairs);
  std::cout << "Graph Input:\n" << g << "\n";

  int src = 3;
  std::cout << "BFS from source " << src << ": ";
  g.bfs(src);
}
