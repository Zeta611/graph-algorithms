#ifndef GRAPH_H
#define GRAPH_H
#include <climits>
#include <iosfwd>
#include "list.h"
#include "pair.h"

class graph {
public:
  graph(bool, int, int, int* const);
  ~graph();

  void bfs(const int);
  void dfs();
  void mst_prim();
  void mst_prim(const int);
  void shortest_dijkstra(const int);

  friend std::ostream& operator<<(std::ostream&, const graph&);

private:
  struct vertex;
  vertex** vertices;

  typedef pair<vertex*, int> vwpair;
  list<vwpair>** adj;

  void initialize();
  void dfs_visit(vertex*, int&);
  vertex* extract_min(vertex**, bool);

  void print_parents();
  void print_dists();

  struct vertex {
    vertex(int);
    int key;
    enum class color { WHITE, GRAY, BLACK };
    color col = color::WHITE;
    int dist = INT_MAX;
    int discov = INT_MAX;
    int finish = INT_MAX;
    int wkey = INT_MAX;
    vertex* parent = nullptr;
  };

  vwpair** pairs;
  bool directed;
  int vcnt;
  int ecnt;
};

#endif /* ifndef GRAPH_H */
