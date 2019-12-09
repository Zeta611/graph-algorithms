template <typename T>
list<T>::list() : nil{new node()}
{
  nil->next = nil;
  nil->prev = nil;
}


template <typename T>
list<T>::~list()
{
  node* curr = nil->next;
  while (curr != nil) {
    curr = curr->next;
    delete curr->prev;
  }
  delete curr;
}


template <typename T>
list<T>::node::node(T* const key) : key{key} {}


template <typename T>
list<T>::node::node() {}


template <typename T>
void list<T>::insert(T* const key)
{
  auto x = new node(key);
  x->next = nil->next;
  nil->next->prev = x;
  nil->next = x;
  x->prev = nil;
}


template <typename T>
void list<T>::remove(T* const key)
{
  auto x = search(key);
  x->prev->next = x->next;
  x->next->prev = x->prev;
  delete x;
}


template <typename T>
bool list<T>::is_empty()
{
  return nil->next == nil;
}


template <typename T>
typename list<T>::node* list<T>::search(T* const key)
{
  node* curr = nil->next;
  while (curr != nil && curr->key != key) {
    curr = curr->next;
  }
  return curr != nil ? curr : nullptr;
}


template <typename T>
typename list<T>::iterator list<T>::begin()
{
  return iterator(*this, nil->next);
}


template <typename T>
typename list<T>::iterator list<T>::end()
{
  return iterator(*this, nil);
}


template <typename T>
list<T>::iterator::iterator(list<T>& l) : curr{l.nil->next}, l{l} {}


template <typename T>
list<T>::iterator::iterator(list<T>& l, node* x) : curr{x}, l{l} {}


template <typename T>
typename list<T>::iterator& list<T>::iterator::operator++()
{
  curr = curr->next;
  return *this;
}


template <typename T>
typename list<T>::iterator& list<T>::iterator::operator++(int)
{
  auto it = *this;
  curr = curr->next;
  return it;
}


template <typename T>
bool list<T>::iterator::operator!=(const iterator& it) const
{
  return it.curr != curr;
}


template <typename T>
T& list<T>::iterator::operator*() const
{
  return *curr->key;
}
