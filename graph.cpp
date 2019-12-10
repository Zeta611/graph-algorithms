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

  initialize();
  src->col = vertex::color::GRAY;
  src->dist = 0;

  queue<vertex> q;
  q.enqueue(src);

  std::cout << "Visit order: ";
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
  std::cout << "\b\n\n";
  print_parents();
}


void graph::dfs()
{
  initialize();

  std::cout << "Visit order: ";
  int time = 0;
  for (int i = 0; i < vcnt; ++i) {
    auto u = vertices[i];
    if (u->col == vertex::color::WHITE) {
      dfs_visit(u, time);
    }
  }
  std::cout << "\b\n\n";
  print_parents();
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


void graph::mst_prim()
{
  mst_prim(0);
}


void graph::mst_prim(int r)
{
  if (vcnt == 0) { return; }
  vertex* const root = vertices[r];

  initialize();
  root->wkey = 0;

  vertex** q = new vertex*[vcnt];
  for (int i = 0; i < vcnt; ++i) {
    q[i] = vertices[i];
  }

  for (int qcnt = 0; qcnt < vcnt; ++qcnt) {
    vertex* u = extract_min(q, false);

    for (const pair<vertex*, int>& p : *adj[u->key]) {
      vertex* const v = p.fst;
      const int w = p.snd;

      bool v_in_q {false};
      for (int i = 0; i < vcnt; ++i) {
        auto curr = q[i];
        if (curr == v) {
          v_in_q = true;
          break;
        }
      }

      if (v_in_q && w < v->wkey) {
        v->parent = u;
        v->wkey = w;
      }
    }
  }

  delete[] q;
  print_parents();
}


void graph::shortest_dijkstra(const int s)
{
  vertex* const src = vertices[s];

  initialize();
  src->dist = 0;

  vertex** q = new vertex*[vcnt];
  for (int i = 0; i < vcnt; ++i) {
    q[i] = vertices[i];
  }

  for (int qcnt = 0; qcnt < vcnt; ++qcnt) {
    vertex* u = extract_min(q, true);
    for (const pair<vertex*, int>& p : *adj[u->key]) {
      vertex* const v = p.fst;
      const int w = p.snd;

      // Relax
      if (v->dist > u->dist + w) {
        v->dist = u->dist + w;
        v->parent = u;
      }
    }
  }

  delete[] q;
  print_parents();
  std::cout << "\n";
  print_dists();
}


graph::vertex* graph::extract_min(vertex** q, bool dist_wkey)
{
  vertex* u = nullptr;
  int min_i;

  for (int i = 0; i < vcnt; ++i) {
    auto curr = q[i];
    if (dist_wkey) {
      if (u == nullptr || (curr != nullptr && u->dist > curr->dist)) {
        u = curr;
        min_i = i;
      }
    } else {
      if (u == nullptr || (curr != nullptr && u->wkey > curr->wkey)) {
        u = curr;
        min_i = i;
      }
    }
  }
  q[min_i] = nullptr;
  return u;
}


void graph::print_parents()
{
  std::cout << "Vertex: Parent\n";
  for (int i = 0; i < vcnt; ++i) {
    auto u = vertices[i];
    std::cout << u->key << ": ";
    auto p = u->parent;
    if (p) {
      std::cout << p->key << "\n";
    } else {
      std::cout << "nil\n";
    }
  }
}


void graph::print_dists()
{
  std::cout << "Vertex: Distance\n";
  for (int i = 0; i < vcnt; ++i) {
    auto u = vertices[i];
    std::cout << u->key << ": " << u->dist << "\n";
  }
}


void graph::initialize()
{
  for (int i = 0; i < vcnt; ++i) {
    auto u = vertices[i];
    u->col = vertex::color::WHITE;
    u->dist = INT_MAX;
    u->discov = INT_MAX;
    u->finish = INT_MAX;
    u->wkey = INT_MAX;
    u->parent = nullptr;
  }
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
