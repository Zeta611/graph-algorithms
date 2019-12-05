#ifndef LIST_H
#define LIST_H
#include "node.h"

template <typename T>
class list {
public:
  list<T>();
  ~list<T>();

  void insert(node<T>*);
  void remove(node<T>*);
  node<T>* search(T*);

  class iterator;
  iterator begin();
  iterator end();

  class iterator {
  public:
    iterator(list<T>&);
    iterator(list<T>&, node<T>*);
    iterator& operator++();
    iterator& operator++(int);
    bool operator!=(const iterator&) const;
    T& operator*() const;

  private:
    node<T>* curr;
    list<T>& l;
  };

// private:
  node<T>* const nil;
};

#include "list.tpp"
#endif /* ifndef LIST_H */
