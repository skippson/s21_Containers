#ifndef S21_SET_H
#define S21_SET_H

#include <iostream>
#include <limits>

#include "../s21_bntree.h"

namespace s21 {
template <class Key>
class set : public tree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename tree<Key, Key>::iterator;
  using const_iterator = typename tree<Key, Key>::const_iterator;
  using size_type = size_t;

  set() : tree<Key, Key>(){};
  set(std::initializer_list<value_type> const &items) {
    for (auto i = items.begin(); i != items.end(); ++i) {
      tree<Key, Key>::insert(*i);
    }
  }
  set(const set &other) : tree<Key, Key>(other){};
  set(set &&other) noexcept : tree<Key, Key>(std::move(other)){};
  set &operator=(const set &other) {
    if (this != &other) {
      tree<Key, Key>::operator=(other);
    }
    return *this;
  }
  set &operator=(set &&other) noexcept {
    if (this != &other) {
      tree<Key, Key>::operator=(std::move(other));
    }
    return *this;
  }
  ~set() = default;

  iterator find(const Key &key) { return tree<Key, Key>::find(key); }
};
}  // namespace s21

#endif