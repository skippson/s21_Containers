#ifndef S21_MAP_H
#define S21_MAP_H

#include <iostream>
#include <limits>

#include "../s21_bntree.h"

namespace s21 {
template <class Key, class Value>
class map : public tree<Key, Value> {
 public:
  class MapIterator;
  class ConstMapIterator;
  using key_type = Key;
  using value_type = Value;
  using mapped_type = std::pair<key_type, value_type>;
  using reference = mapped_type &;
  using const_reference = const mapped_type &;
  using iterator = MapIterator;
  using const_iterator = ConstMapIterator;
  using size_type = size_t;

  class MapIterator : public tree<Key, Value>::Iterator {
   protected:
    value_type &return_value();

   public:
    MapIterator() : tree<Key, Value>::Iterator(){};
    MapIterator(typename tree<Key, Value>::Node *node,
                typename tree<Key, Value>::Node *past_node = nullptr)
        : tree<Key, Value>::Iterator(node, past_node = nullptr){};
    reference &operator*();

    friend class map;
  };
  class ConstMapIterator : public MapIterator {
   public:
    friend class map;
    ConstMapIterator() : MapIterator(){};
    ConstMapIterator(typename tree<Key, Value>::Node *node,
                     typename tree<Key, Value>::Node *past_node)
        : MapIterator(node, past_node = nullptr){};
    const_reference operator*() const { return MapIterator::operator*(); }
  };

  map() : tree<Key, Value>(){};
  map(std::initializer_list<mapped_type> const &items) noexcept;
  map(const map &other) : tree<Key, Value>(other){};
  map(map &&other) noexcept : tree<Key, Value>(std::move(other)){};
  map &operator=(const map &other);
  map &operator=(map &&other) noexcept;
  ~map() = default;

  std::pair<iterator, bool> insert(const mapped_type &value) {
    std::pair<typename tree<Key, Value>::iterator, bool> tr =
        tree<Key, Value>::insert(value.first, value.second);
    std::pair<typename map<Key, Value>::iterator, bool> map_pair;
    map_pair.first = MapIterator(find(value.first));
    map_pair.second = tr.second;
    return map_pair;
  }
  std::pair<iterator, bool> insert(const Key &key, const Value &value) {
    std::pair<typename tree<Key, Value>::iterator, bool> tr =
        tree<Key, Value>::insert(key, value);
    std::pair<typename map<Key, Value>::iterator, bool> map_pair;
    map_pair.first = MapIterator(find(key));
    map_pair.second = tr.second;
    return map_pair;
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key,
                                             const Value &value) {
    if (find(key) != nullptr) {
      map<Key, Value>::erase(find(key));
      return map<Key, Value>::insert(key, value);
    }
    return map<Key, Value>::insert(key, value);
  }
  bool contains(const Key &key);
  void erase(iterator pos);
  iterator begin();
  iterator end();
  iterator find(const Key &key);
  Value &at(const Key &key);
  Value &operator[](const Key &key);

 protected:
  static inline std::pair<key_type, value_type> pr{};
};

template <typename Key, typename Value>
bool map<Key, Value>::contains(const Key &key) {
  return find(key) != nullptr;
}

template <typename Key, typename Value>
void map<Key, Value>::erase(typename map<Key, Value>::MapIterator pos) {
  if (pos.it_node == nullptr || tree<Key, Value>::t_root == nullptr) return;
  tree<Key, Value>::t_root = tree<Key, Value>::recursive_delete(
      tree<Key, Value>::t_root, (*pos).first);
}

template <typename Key, typename Value>
typename map<Key, Value>::MapIterator map<Key, Value>::find(const Key &key) {
  typename tree<Key, Value>::Node *node =
      tree<Key, Value>::recursive_find(tree<Key, Value>::t_root, key);
  return MapIterator(node);
}

template <typename Key, typename Value>
typename map<Key, Value>::iterator map<Key, Value>::begin() {
  return map<Key, Value>::MapIterator(
      tree<Key, Value>::get_min(tree<Key, Value>::t_root));
}

template <typename Key, typename Value>
typename map<Key, Value>::iterator map<Key, Value>::end() {
  if (tree<Key, Value>::t_root == nullptr) {
    return map<Key, Value>::begin();
  }

  typename tree<Key, Value>::Node *last_node =
      tree<Key, Value>::get_max(tree<Key, Value>::t_root);
  MapIterator test(nullptr, last_node);
  return test;
}

template <typename Key, typename Value>
typename map<Key, Value>::reference map<Key, Value>::MapIterator::operator*() {
  if (tree<Key, Value>::Iterator::it_node == nullptr) {
    static mapped_type fake{};
    return fake;
  }
  pr.first = tree<Key, Value>::Iterator::it_node->n_key;
  pr.second = tree<Key, Value>::Iterator::it_node->n_value;
  std::pair<key_type, value_type> &ref = pr;
  return ref;
}

template <typename Key, typename Value>
Value &map<Key, Value>::at(const Key &key) {
  iterator a = find(key);
  if (a == nullptr) {
    throw std::out_of_range("there is no such key in the map");
  }
  return a.return_value();
}

template <typename Key, typename Value>
Value &map<Key, Value>::operator[](const Key &key) {
  auto it = find(key);
  if (it == nullptr) {
    static const Value fake{};
    auto n = insert(key, fake);
    it = n.first;
  }
  return it.return_value();
}

template <typename Key, typename Value>
Value &map<Key, Value>::MapIterator::return_value() {
  if (tree<Key, Value>::Iterator::it_node == nullptr) {
    static Value fake{};
    return fake;
  }
  return tree<Key, Value>::Iterator::it_node->n_value;
}

template <typename Key, typename Value>
map<Key, Value> &map<Key, Value>::operator=(const map &other) {
  if (this != &other) {
    tree<Key, Value>::operator=(other);
  }
  return *this;
}

template <typename Key, typename Value>
map<Key, Value> &map<Key, Value>::operator=(map &&other) noexcept {
  if (this != &other) {
    tree<Key, Value>::operator=(std::move(other));
  }
  return *this;
}

template <typename Key, typename Value>
map<Key, Value>::map(std::initializer_list<mapped_type> const &items) noexcept {
  for (auto i = items.begin(); i != items.end(); ++i) {
    tree<Key, Value>::insert(i->first, i->second);
  }
};
}  // namespace s21

#endif