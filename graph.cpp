#include <iostream>
#include "graph.h"
#include "list.h"
#include "pair.h"

graph::graph(int vcnt, int ecnt, int* const ewpairs)
  : adj{new list<vwpair>*[vcnt]},
    pairs{new vwpair*[ecnt]},
    vcnt{vcnt},
    ecnt{ecnt}
{
  vertices = new vertex*[vcnt];
  for (int i = 0; i < vcnt; ++i) {
    auto v = new vertex(i);
    vertices[i] = v;
    adj[i] = new list<vwpair>();
  }

  for (int i = 0; i < ecnt; ++i) {
    int w = ewpairs[3 * i];
    int u = ewpairs[3 * i + 1];
    int v = ewpairs[3 * i + 2];
    auto p = new vwpair(vertices[v], w);
    pairs[i] = p;
    adj[u]->insert(p);
  }
}


graph::~graph()
{
  for (int i = 0; i < vcnt; ++i) {
    delete adj[i];
  }
  delete[] adj;

  for (int i = 0; i < ecnt; ++i) {
    delete pairs[i];
  }
  delete[] pairs;

  for (int i = 0; i < vcnt; ++i) {
    delete vertices[i];
  }
  delete[] vertices;
}


graph::vertex::vertex(int key) : key{key} {}


std::ostream& operator<<(std::ostream& stream, const graph& g)
{
  for (int i = 0; i < g.vcnt; ++i) {
    stream << i;
    for (auto e : *g.adj[i]) {
      stream << " -> (" << e.fst->key << ", " << e.snd << ")";
    }
    stream << "\n";
  }
  return stream;
}
