#ifndef NODE_H
#define NODE_H

template <typename T>
struct node {
  node();
  node(T* key);
  ~node();
  node<T>* next = nullptr;
  node<T>* prev = nullptr;
  T* key = nullptr;
};

#include "node.tpp"
#endif /* ifndef NODE_H */
