#ifndef GRAPH_H
#define GRAPH_H
#include <climits>
#include <iosfwd>
#include "list.h"
#include "pair.h"

class graph {
public:
  graph(int, int, int* const);
  ~graph();

  struct vertex;
  vertex** vertices;

  typedef pair<vertex*, int> vwpair;
  list<vwpair>** adj;

  struct vertex {
    vertex(int);
    int key;
    enum class color { WHITE, GRAY, BLACK };
    color col = color::WHITE;
    int dist = INT_MAX;
    vertex* parent = nullptr;
  };

  friend std::ostream& operator<<(std::ostream&, const graph&);

private:
  vwpair** pairs;
  int vcnt;
  int ecnt;
};

#endif /* ifndef GRAPH_H */
