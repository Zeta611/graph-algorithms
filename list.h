#ifndef LIST_H
#define LIST_H

template <typename T>
class list {
public:
  list<T>();
  ~list<T>();

  class node;
  void insert(node*);
  void remove(node*);
  node* search(T*);

  class node {
  public:
    node();
    node(T* key);
    ~node();
    node* next = nullptr;
    node* prev = nullptr;
    T* key = nullptr;
  };

  class iterator;
  iterator begin();
  iterator end();

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
};

#include "list.tpp"
#endif /* ifndef LIST_H */
