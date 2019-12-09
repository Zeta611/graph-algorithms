#ifndef QUEUE_H
#define QUEUE_H
#include "list.h"

template <typename T>
class queue : public list<T> {
public:
  void enqueue(T* const);
  T* dequeue();
};

#include "queue.tpp"
#endif /* ifndef QUEUE_H */
