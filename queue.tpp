template <typename T>
void queue<T>::enqueue(T* const key)
{
  this->insert(key);
}


template <typename T>
T* queue<T>::dequeue()
{
  auto last = this->nil->prev;
  if (last == this->nil) { return nullptr; }
  T* key = last->key;
  last->prev->next = last->next;
  last->next->prev = last->prev;
  delete last;
  return key;
}
