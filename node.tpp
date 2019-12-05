template <typename T>
node<T>::node(T* key) : key{key} {}


template <typename T>
node<T>::node() {}


template <typename T>
node<T>::~node()
{
  delete key;
}
