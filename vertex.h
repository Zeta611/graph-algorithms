#ifndef VERTEX_H
#define VERTEX_H
#include <climits>

class vertex {
public:
  vertex(int);
  int key;
  enum class color { WHITE, GRAY, BLACK };
  color col = color::WHITE;
  int dist = INT_MAX;
  vertex* parent = nullptr;
};

#endif /* ifndef VERTEX_H */
