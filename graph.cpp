#include <iostream>
#include <climits>
#include "graph.h"
#include "list.h"
#include "pair.h"
#include "queue.h"

graph::graph(bool directed, int vcnt, int ecnt, int* const ewpairs)
  : adj{new list<vwpair>*[vcnt]},
    pairs{new vwpair*[directed ? ecnt : 2 * ecnt]},
    directed{directed},
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

    if (!directed) {
      auto q = new vwpair(vertices[u], w);
      pairs[i + ecnt] = q;
      adj[v]->insert(q);
    }
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
    if (!directed) { delete pairs[i + ecnt]; }
  }
  delete[] pairs;

  for (int i = 0; i < vcnt; ++i) {
    delete vertices[i];
  }
  delete[] vertices;
}


void graph::bfs(int s)
{
  vertex* const src = vertices[s];

  for (int i = 0; i < vcnt; ++i) {
    auto u = vertices[i];
    if (u == src) { continue; }
    u->col = vertex::color::WHITE;
    u->dist = INT_MAX;
    u->parent = nullptr;
  }

  src->col = vertex::color::GRAY;
  src->dist = 0;
  src->parent = nullptr;

  queue<vertex> q;
  q.enqueue(src);

  while (!q.is_empty()) {
    vertex* const u = q.dequeue();

    for (const pair<vertex*, int>& p : *adj[u->key]) {
      vertex* const v = p.fst;
      if (v->col == vertex::color::WHITE) {
        v->col = vertex::color::GRAY;
        v->dist = u->dist + 1;
        v->parent = u;
        q.enqueue(v);
      }
    }

    u->col = vertex::color::BLACK;
    std::cout << u->key << " ";
  }
  std::cout << "\b\n";
}


void graph::dfs()
{
  for (int i = 0; i < vcnt; ++i) {
    auto u = vertices[i];
    u->col = vertex::color::WHITE;
    u->parent = nullptr;
  }

  int time = 0;
  for (int i = 0; i < vcnt; ++i) {
    auto u = vertices[i];
    if (u->col == vertex::color::WHITE) {
      dfs_visit(u, time);
    }
  }
  std::cout << "\b\n";
}


void graph::dfs_visit(vertex* u, int& time)
{
  std::cout << u->key << " ";
  ++time;
  u->discov = time;
  u->col = vertex::color::GRAY;

  for (const pair<vertex*, int>& p : *adj[u->key]) {
    vertex* const v = p.fst;
    if (v->col == vertex::color::WHITE) {
      v->parent = u;
      dfs_visit(v, time);
    }
  }

  u->col = vertex::color::BLACK;
  ++time;
  u->finish = time;
}


graph::vertex::vertex(int key) : key{key} {}


std::ostream& operator<<(std::ostream& stream, const graph& g)
{
  for (int i = 0; i < g.vcnt; ++i) {
    stream << i;
    for (const pair<graph::vertex*, int>& e : *g.adj[i]) {
      stream << " → (" << e.fst->key << ", w=" << e.snd << ")";
    }
    stream << "\n";
  }
  return stream;
}
