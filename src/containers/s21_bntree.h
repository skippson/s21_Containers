#ifndef S21_BNTREE
#define S21_BNTREE
#include <iostream>

namespace s21 {
template <typename Key, typename Value>
class tree {
 protected:
  struct Node;

 public:
  class Iterator;
  class ConstIterator;
  using key_type = Key;
  using value_type = Value;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  class Iterator {
   public:
    Iterator();
    Iterator(Node* node, Node* past_node = nullptr);
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    reference operator*();

    bool operator==(const iterator& it);
    bool operator!=(const iterator& it);
    friend class tree<Key, Value>;

   protected:
    Node* it_node;
    Node* it_past_node;
    Node* move_forward(Node* node);
    Node* move_back(Node* node);
  };
  class ConstIterator : public Iterator {
   public:
    ConstIterator() : Iterator(){};
    const_reference operator*() const { return Iterator::operator*(); };
  };
  
  tree();
  tree(const tree& other);
  tree(tree&& other);
  ~tree();
  tree& operator=(tree&& other);
  tree& operator=(const tree& other);
  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  std::pair<iterator, bool> insert(key_type key);
  std::pair<iterator, bool> insert(const key_type& key, const value_type& value) {

  std::pair<iterator, bool> return_value;
  if (t_root == nullptr) {
    Node* new_node = new Node(key, value);
    t_root = new_node;
    return_value.first = Iterator(t_root);
    return_value.second = true;
  } else {
    return_value.second = recursive_insert(t_root, key, value);
    return_value.first = find(key);
  }
  return return_value;
  }

  
  void erase(iterator pos);
  void swap(tree& other);
  void merge(tree& other);
  bool contains(const Key &key);

 protected:
  iterator find(const Key &key);
  struct Node {
    Node(key_type key, value_type value);
    Node(key_type key, value_type value, Node* parent);
    key_type n_key = nullptr;
    value_type n_value = nullptr;
    Node* n_parent = nullptr;
    int n_height = 1;
    Node* n_left = nullptr;
    Node* n_right = nullptr;
    int n_count = 0;
    friend class tree<Key, Value>;
    friend class tree<Key, Value>::Iterator;
  };
  Node *t_root;
  void free_node(Node* node);
  Node* copy_tree(Node* node, Node* parent);
  void swap_value(Node* a, Node* b);
  void right_rotate(Node* node);
  void left_rotate(Node* node);
  void balance(Node* node);
  int get_balance_factor(Node* node);
  int get_height(Node* node);
  void set_height(Node* node);
  static Node* get_min(Node* node);
  static Node* get_max(Node* node);

  bool recursive_insert(Node* node, const Key& key, Value value);
  Node* recursive_delete(Node* node, Key key);
  size_t recursive_size(Node* node);
  Node* recursive_find(Node* node, const Key& key);
};

template <typename Key, typename Value>
tree<Key, Value>::tree() : t_root(nullptr) {}

template <typename Key, typename Value>
tree<Key, Value>::tree(const tree& other) {
  t_root = copy_tree(other.t_root, nullptr);
}

template <typename Key, typename Value>
typename tree<Key, Value>::Node* tree<Key, Value>::copy_tree(
    typename tree<Key, Value>::Node* node,
    typename tree<Key, Value>::Node* parent) {
  if (node == nullptr) {
    return nullptr;
  }
  Node *new_node = new Node(node->n_key, node->n_value, parent);
  new_node->n_height = node->n_height;
  new_node->n_left = copy_tree(node->n_left, new_node);
  new_node->n_right = copy_tree(node->n_right, new_node);
  return new_node;
}

template <typename Key, typename Value>
tree<Key, Value>::tree(tree&& other) {
  t_root = other.t_root;
  other.t_root = nullptr;
}

template <typename Key, typename Value>
tree<Key, Value>::~tree() {
  clear();
}

template <typename Key, typename Value>
void tree<Key, Value>::clear() {
  if (t_root != nullptr) {
    free_node(t_root);
  }
  t_root = nullptr;
}

template <typename Key, typename Value>
void tree<Key, Value>::free_node(typename tree<Key, Value>::Node* node) {
  if (node == nullptr) {
    return;
  }
  free_node(node->n_left);
  free_node(node->n_right);
  delete node;
}

template <typename Key, typename Value>
tree<Key, Value>::Iterator::Iterator()
    : it_node(nullptr), it_past_node(nullptr) {}

template <typename Key, typename Value>
tree<Key, Value>::Iterator::Iterator(tree<Key, Value>::Node* node, tree<Key, Value>::Node* past_node)
    : it_node(node), it_past_node(past_node) {}

template <typename Key, typename Value>
tree<Key, Value>& tree<Key, Value>::operator=(const tree& other) {
  if (this != other) {
    Node* temp(other);
    free_node(t_root);
    t_root = std::move(temp);
  }
}

template <typename Key, typename Value>
tree<Key, Value>& tree<Key, Value>::operator=(tree&& other) {
  if (this != other) {
    t_root = other.t_root;
    other.t_root = nullptr;
  }
}

template <typename Key, typename Value>
typename tree<Key, Value>::iterator tree<Key, Value>::begin() {
  return tree::Iterator(get_min(t_root));
}

template <typename Key, typename Value>
typename tree<Key, Value>::iterator tree<Key, Value>::end() {
  if (t_root == nullptr) return nullptr;
  Node* last_node = get_max(t_root);
  iterator res(nullptr, last_node);
  return res;
}

template <typename Key, typename Value>
typename tree<Key, Value>::iterator &tree<Key, Value>::Iterator::operator++() {
  Node* temp;
  if (it_node != nullptr) {
    temp = get_max(it_node);
  }
  it_node = move_forward(it_node);
  if (it_node == nullptr) {
    it_past_node = temp;
  }
  return *this;
}

template <typename Key, typename Value>
typename tree<Key, Value>::iterator tree<Key, Value>::Iterator::operator++(
    int) {
  Iterator temp = *this;
  operator++();
  return temp;
}

template <typename Key, typename Value>
typename tree<Key, Value>::iterator &tree<Key, Value>::Iterator::operator--() {
  if (it_node == nullptr && it_past_node != nullptr) {
    *this = it_past_node;  //// ????????
    return *this;
  }
  it_node = move_back(it_node);
  return *this;
}

template <typename Key, typename Value>
typename tree<Key, Value>::iterator tree<Key, Value>::Iterator::operator--(
    int) {
  Node* temp = *this;
  operator--();
  return temp;
}

template <typename Key, typename Value>
typename tree<Key, Value>::reference tree<Key, Value>::Iterator::operator*() {
  if (it_node == nullptr) {
    static Value fake_val{};
    return fake_val;
  }
  return it_node->n_value;
}

// template <typename Key, typename Value>
// std::pair<Key, typename tree<Key, Value>::reference> tree<Key, Value>::Iterator::operator*() {
//   std::pair<Key, reference> return_value;
//   return_value.first = it_node->n_key;
//   return_value.second = it_node->n_value;
// }

template <typename Key, typename Value>
bool tree<Key, Value>::Iterator::operator==(
    const tree<Key, Value>::iterator& it) {
  return it_node == it.it_node;
}

template <typename Key, typename Value>
bool tree<Key, Value>::Iterator::operator!=(
    const tree<Key, Value>::iterator& it) {
  return it_node != it.it_node;
}

template <typename Key, typename Value>
typename tree<Key, Value>::Node* tree<Key, Value>::get_min(
    typename tree<Key, Value>::Node* node) {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->n_left == nullptr) {
    return node;
  }
  return get_min(node->n_left);

}

template <typename Key, typename Value>
typename tree<Key, Value>::Node* tree<Key, Value>::get_max(
    typename tree<Key, Value>::Node* node) {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->n_right == nullptr) {
    return node;
  }
  return get_max(node->n_right);
}
template <typename Key, typename Value>
typename tree<Key, Value>::Node* tree<Key, Value>::Iterator::move_forward(
    typename tree<Key, Value>::Node* node) {
  if(node == nullptr){
    return nullptr;
  }
  if (node->n_right != nullptr) {
    return get_min(node->n_right);
  }
  Node* parent = node->n_parent;
  while (parent != nullptr && parent->n_right == node) {
    node = parent;
    parent = parent->n_parent;
  }
  return parent;
}

template <typename Key, typename Value>
typename tree<Key, Value>::Node* tree<Key, Value>::Iterator::move_back(
    typename tree<Key, Value>::Node* node) {
  if (node->n_left != nullptr) {
    return get_max(node->n_left);
  }
  Node* parent = node->n_parent;
  while (parent != nullptr && parent->n_left == node) {
    node = parent;
    parent = parent->n_parent;
  }
  return parent;
}

template <typename Key, typename Value>
bool tree<Key, Value>::empty() {
  return (t_root == nullptr);
}

template <typename Key, typename Value>
typename tree<Key, Value>::size_type tree<Key, Value>::size() {
  return recursive_size(t_root);
}

template <typename Key, typename Value>
typename tree<Key, Value>::size_type tree<Key, Value>::max_size() {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename tree<Key, Value>::Node);
}

template <typename Key, typename Value>
typename tree<Key, Value>::size_type tree<Key, Value>::recursive_size(
    tree<Key, Value>::Node* node) {
  if (node == nullptr) return 0;
  size_type left_size = recursive_size(node->n_left);
  size_type right_size = recursive_size(node->n_right);
  return 1 + left_size + right_size;
}

template <typename Key, typename Value>
tree<Key, Value>::Node::Node(tree<Key, Value>::key_type key, tree<Key, Value>::value_type value)
    : n_key(key), n_value(value), n_height(1) {}

template <typename Key, typename Value>
tree<Key, Value>::Node::Node(key_type key, value_type value, Node* parent)
    : n_key(key), n_value(value), n_parent(parent), n_height(1) {}

template <typename Key, typename Value>
void tree<Key, Value>::swap_value(tree<Key, Value>::Node* a,
                                  tree<Key, Value>::Node* b) {
  std::swap(a->n_value, b->n_value);
  std::swap(a->n_key, b->n_key);
}

template <typename Key, typename Value>
int tree<Key, Value>::get_height(tree<Key, Value>::Node* node) {
  return node == nullptr ? 0 : node->n_height;
}

template <typename Key, typename Value>
int tree<Key, Value>::get_balance_factor(tree<Key, Value>::Node* node) {
  return node == nullptr ? 0
                         : get_height(node->n_right) - get_height(node->n_left);
}

template <typename Key, typename Value>
std::pair<typename tree<Key, Value>::iterator, bool> tree<Key, Value>::insert(
    tree<Key, Value>::key_type key) {

  std::pair<iterator, bool> return_value;
  if (t_root == nullptr) {
    Node* new_node = new Node(key, key);
    t_root = new_node;
    return_value.first = Iterator(t_root);
    return_value.second = true;
  } else {
    return_value.second = recursive_insert(t_root, key, key);
    return_value.first = find(key);
  }
  return return_value;
}

// template <typename Key, typename Value>
// std::pair<typename tree<Key, Value>::iterator, bool> tree<Key, Value>::insert(const 
  //   Key& key, const Value& value) {

  // std::pair<iterator, bool> return_value;
  // if (t_root == nullptr) {
  //   Node* new_node = new Node(key, value);
  //   t_root = new_node;
  //   return_value.first = Iterator(t_root);
  //   return_value.second = true;
  // } else {
  //   return_value.second = recursive_insert(t_root, key, value);
  //   return_value.first = find(key);
  // }
  // return return_value;
// }

template <typename Key, typename Value>
typename tree<Key, Value>::iterator tree<Key, Value>::find(const Key& key) {
  Node* search_node = recursive_find(t_root, key);
  return Iterator(search_node);
}

template <typename Key, typename Value>
typename tree<Key, Value>::Node* tree<Key, Value>::recursive_find(
    tree<Key, Value>::Node* node, const Key& key) {
  if (node == nullptr || key == node->n_key) return node;
  if (key > node->n_key) {
    return recursive_find(node->n_right, key);
  }
  else {
    return recursive_find(node->n_left, key);
  }
}

template <typename Key, typename Value>
bool tree<Key, Value>::recursive_insert(tree<Key, Value>::Node* node,
                                        const Key& key, Value value) {
  bool res = false;
  if (key < node->n_key) {
    if (node->n_left == nullptr) {
      node->n_left = new Node(key, value, node);
      res = true;
    } else {
      res = recursive_insert(node->n_left, key, value);
    }
  }
  if (key > node->n_key) {
    if (node->n_right == nullptr) {
      node->n_right = new Node(key, value, node);
      res = true;
    } else {
      res = recursive_insert(node->n_right, key, value);
    }
  }
  if (key == node->n_key) {
    return res;
  }
  set_height(node);
  balance(node);
  return res;
}

template <typename Key, typename Value>
void tree<Key, Value>::erase(tree<Key, Value>::iterator pos) {
  if(pos.it_node ==  nullptr) return;
  t_root = recursive_delete(t_root, *pos);
}

template <typename Key, typename Value>
typename tree<Key, Value>::Node* tree<Key, Value>::recursive_delete(
    tree<Key, Value>::Node* node, Key key) {
  if (node == nullptr) return nullptr;
  if (key < node->n_key) {
      node->n_left = recursive_delete(node->n_left, key);
  }
  if (key > node->n_key) {
      node->n_right = recursive_delete(node->n_right, key);
  }
  if (key == node->n_key) {
    if (node->n_left == nullptr || node->n_right == nullptr) {
      Node* right = node->n_right;
      Node* left = node->n_left;
      Node* parent = node->n_parent;
      delete node;
      if (right == nullptr) {
        node = left;
      }
      if (left == nullptr) {
        node = right;
      }
      if (node != nullptr) node->n_parent = parent;
    } else {
      Node* min = get_min(node->n_right);
      node->n_key = min->n_key;
      node->n_value = min->n_value;
      node->n_right = recursive_delete(node->n_right, min->n_key);
    }
  }
  if (node != nullptr) {
    set_height(node);
    balance(node);
  }
  return node;
}


template <typename Key, typename Value>
void tree<Key, Value>::swap(tree<Key, Value> &other){
    std::swap(t_root, other.t_root);
}

template <typename Key, typename Value>
void tree<Key, Value>::merge(tree<Key, Value> &other){
    tree const_other(other);
    iterator it_const = const_other.begin();
    for(;it_const != const_other.end(); it_const++){
        insert(*it_const);
        other.erase(it_const);
    }

}

template <typename Key, typename Value>
bool tree<Key, Value>::contains(const Key &key){
    return find(key) != nullptr;
}

template <typename Key, typename Value>
void tree<Key, Value>::set_height(tree<Key, Value>::Node *node) {
  node->n_height = get_height(node->n_left) +  get_height(node->n_right) +
                  1;  
}


template <typename Key, typename Value>
void tree<Key, Value>::balance(tree<Key, Value>::Node* node){
    int balance_fac = get_balance_factor(node);
    if(balance_fac < -1){
        right_rotate(node);
    }if(balance_fac > 1){
        left_rotate(node);
    }
}


template <typename Key, typename Value>
void tree<Key, Value>::right_rotate(tree<Key, Value>::Node* node){
    Node *right = node->n_right;
    swap_value(node, node->n_left);
    node->n_right = node->n_left;
    
    node->n_left = node->n_right->n_left;
    if(node->n_left){
        node->n_left->n_parent = node;
    }
    node->n_right->n_left = node->n_right->n_right;
    node->n_right->n_right = right;
    if(node->n_right->n_right){
        node->n_right->n_right->n_parent = node->n_right;
    }
    set_height(node->n_right);
    set_height(node);

}

template <typename Key, typename Value>
void tree<Key, Value>::left_rotate(tree<Key, Value>::Node* node){

    Node *left = node->n_left;
    swap_value(node, node->n_right);
    node->n_left = node->n_right;

    node->n_right = node->n_left->n_right;
    if(node->n_right){
        node->n_right->n_parent = node;
    }
    node->n_left->n_right = node->n_left->n_left;
    node->n_left->n_left = left;
    if(node->n_left->n_left){
        node->n_left->n_left->n_parent = node->n_left;
    }
    set_height(node->n_left);
    set_height(node);

}

};  // namespace s21

#endif  //