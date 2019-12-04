#ifndef VERTEX_H
#define VERTEX_H
#include <climits>

class vertex {
public:
  enum class color { WHITE, GRAY, BLACK };
  color col;
  int dist = INT_MAX;
  vertex* parent = nullptr;
};

#endif /* ifndef VERTEX_H */
