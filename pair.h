#ifndef PAIR_H
#define PAIR_H

template <typename T, typename U>
struct pair {
  pair(T, U);
  T fst;
  U snd;
};

#include "pair.tpp"
#endif /* ifndef PAIR_H */
