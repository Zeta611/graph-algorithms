#ifndef LIST_H
#define LIST_H

template <typename T>
class list {
public:
  list<T>();
  ~list<T>();

  void insert(T* const);
  void remove(T* const);

  class iterator;
  iterator begin();
  iterator end();

  struct node {
    node();
    node(T* const key);
    node* next = nullptr;
    node* prev = nullptr;
    T* const key = nullptr;
  };

  class iterator {
  public:
    iterator(list<T>&);
    iterator(list<T>&, node*);
    iterator& operator++();
    iterator& operator++(int);
    bool operator!=(const iterator&) const;
    T& operator*() const;

  private:
    node* curr;
    list<T>& l;
  };

private:
  node* const nil;
  node* search(T* const);
};

#include "list.tpp"
#endif /* ifndef LIST_H */
