#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include <iostream>
#include <limits>

#include "../list/s21_list.h"
#include "../s21_bntree.h"

namespace s21 {
template <typename T>
class multiset : public list<T> {
 public:
  using key_type = T;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = typename list<T>::List_Iterator;
  using const_iterator = typename list<T>::Const_List_Iterator;
  using size_type = size_t;

  multiset() : list<T>(){};
  multiset(std::initializer_list<value_type> const &items) {
    for (auto i = items.begin(); i != items.end(); ++i) {
      insert(*i);
    }
  }
  multiset(const multiset &other) : list<T>(other){};
  multiset(multiset &&other) noexcept : list<T>(std::move(other)){};
  multiset &operator=(const multiset &other) {
    if (this != &other) {
      list<T>::operator=(other);
    }
    return *this;
  }
  multiset &operator=(multiset &&other) noexcept {
    if (this != &other) {
      list<T>::operator=(std::move(other));
    }
    return *this;
  }
  ~multiset() = default;

  iterator find(const T &key) {
    auto it = list<T>::begin();
    for (; it != list<T>::end(); it++) {
      if (it.list<T>::List_Iterator::getNodePtr() != nullptr && *it == key) {
        return it;
      }
    }
    return list<T>::end();
  }
  iterator insert(const value_type &value) {
    iterator it = find(value);
    iterator it1 = find(value);
    int count = 0;
    while (it.list<T>::List_Iterator::getNodePtr() != nullptr && *it1 == *it) {
      ++it1;
      count++;
    }
    if (count) {
      --it1;
      count--;
    }

    list<T>::insert(list<T>::begin(), value);
    list<T>::sort();
    iterator it2 = find(value);
    for (int i = 0; i < count; i++) {
      ++it2;
    }
    return it2;
  }

  void merge(multiset<T> &other) {
    typename list<T>::Node *temp_other = other.m_head;
    for (std::size_t j = 0; j < other.size(); j++) {
      list<T>::push_back(temp_other->data);
      temp_other = temp_other->next;
    }
    other.clear();
    list<T>::sort();
  }
  size_type count(const T &key);

  typename list<T>::Node *getNodePtr() {
    return list<T>::Const_List_Iterator::getNodePtr();
  }
  bool contains(const T &key);
  std::pair<iterator, iterator> equal_range(const T &key);
  iterator lower_bound(const T &key);
  iterator upper_bound(const T &key);
};

template <typename T>
typename multiset<T>::iterator multiset<T>::lower_bound(const T &key) {
  iterator it = list<T>::begin();
  while (it.getNodePtr() != nullptr && *it < key) {
    ++it;
  }
  return it;
}

template <typename T>
typename multiset<T>::iterator multiset<T>::upper_bound(const T &key) {
  iterator it = list<T>::begin();
  while (it.getNodePtr() != nullptr && *it <= key) {
    ++it;
  }
  return it;
}

template <typename T>
std::pair<typename multiset<T>::iterator, typename multiset<T>::iterator>
multiset<T>::equal_range(const T &key) {
  iterator it = find(key);
  iterator it1 = find(key);
  while (it.getNodePtr() != nullptr && it1.getNodePtr() != nullptr &&
         *it1 == *it) {
    ++it1;
  }

  return std::make_pair(it, it1);
}

template <typename T>
bool multiset<T>::contains(const T &key) {
  return find(key) != list<T>::end();
}

template <typename T>
size_t multiset<T>::count(const T &key) {
  iterator it = find(key);
  iterator it1 = find(key);
  size_t count = 0;
  while (it.getNodePtr() != nullptr && it1.getNodePtr() != nullptr &&
         *it1 == *it) {
    ++it1;
    count++;
  }
  return count;
}
}  // namespace s21

#endif