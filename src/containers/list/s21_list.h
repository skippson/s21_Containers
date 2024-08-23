#pragma once
#ifndef S21_LIST_H
#define S21_LIST_H

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {
template <class T>
class list {
 public:
  struct Node {
    Node *next = nullptr;
    Node *prev = nullptr;
    T data;

    Node(const T &data) noexcept : next(nullptr), prev(nullptr), data(data) {}
  };

 protected:
  Node *m_head;
  Node *m_tail;
  size_t m_size;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;
  using size_type = std::size_t;

 public:
  class Const_List_Iterator {
   private:
    explicit Const_List_Iterator(const Node *ptr) noexcept : m_current{ptr} {}

    friend class list;

   public:
    using value_type = list::value_type;
    using reference = list::const_reference;
    using size_type = list::size_type;

    reference operator*() const noexcept {
      assert(m_current != nullptr);
      return m_current->data;
    }

    Const_List_Iterator &operator++() noexcept {
      assert(m_current != nullptr);
      m_current = m_current->next;
      return *this;
    }

    Const_List_Iterator &operator--() noexcept {
      assert(m_current != nullptr);
      m_current = m_current->prev;
      return *this;
    }

    Const_List_Iterator operator++(int) noexcept {
      assert(m_current != nullptr);
      auto copy = *this;

      m_current = m_current->next;
      return copy;
    }

    Const_List_Iterator operator--(int) noexcept {
      assert(m_current != nullptr);
      auto copy = *this;

      m_current = m_current->prev;
      return copy;
    }

    bool operator==(Const_List_Iterator other) const noexcept {
      return m_current == other.m_current;
    }

    bool operator!=(Const_List_Iterator other) const noexcept {
      return !(*this == other);
    }
    const Node *getNodePtr() noexcept { return m_current; }

   protected:
    const Node *m_current;
  };

  class List_Iterator : public Const_List_Iterator {
   private:
    friend class list;

    explicit List_Iterator(Node *ptr) noexcept : Const_List_Iterator{ptr} {}

   public:
    using value_type = list::value_type;
    using pointer = list::pointer;
    using reference = list::reference;

    reference operator*() noexcept {
      return const_cast<reference>(Const_List_Iterator::operator*());
    }

    List_Iterator &operator++() noexcept {
      Const_List_Iterator::operator++();
      return *this;
    }

    List_Iterator &operator--() noexcept {
      Const_List_Iterator::operator--();
      return *this;
    }

    List_Iterator operator++(int) noexcept {
      auto res = Const_List_Iterator::operator++(0);
      return List_Iterator{const_cast<Node *>(res.getNodePtr())};
    }

    List_Iterator operator--(int) noexcept {
      auto res = Const_List_Iterator::operator--(0);
      return List_Iterator{const_cast<Node *>(res.getNodePtr())};
    }
    bool operator==(List_Iterator other) noexcept {
      return Const_List_Iterator::operator==(other);
    }
    Node *getNodePtr() noexcept {
      return const_cast<Node *>(Const_List_Iterator::getNodePtr());
    }
  };

 public:
  using iterator = List_Iterator;
  using const_iterator = Const_List_Iterator;

 public:
  list() noexcept;
  explicit list(size_type n);
  list(std::initializer_list<value_type> const &items);
  explicit list(const list &v);
  list(list &&other) noexcept;
  ~list();
  list &operator=(const list &other);
  list &operator=(list &&other) noexcept;
  const_reference front();
  const_reference back();
  bool empty() const;
  size_type max_size();
  size_type size();
  void push_back(const T &v);
  void pop_back();
  void push_front(const T &v);
  void pop_front();
  void clear();
  iterator begin();
  iterator end();
  void erase(iterator pos);
  void swap(list &other);
  void sort();
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  iterator insert(iterator pos, const_reference value);
  void reverse();
  void unique();
};

template <typename T>
list<T>::list() noexcept : m_head(nullptr), m_tail(nullptr), m_size(0){};

template <typename T>
list<T>::list(size_type n) : m_head(nullptr), m_tail(nullptr), m_size(0) {
  for (size_type i = 0; i < n; i++) {
    push_back(T());
  }
};

template <typename T>
list<T>::list(list<T> &&other) noexcept
    : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size) {
  other.m_size = 0;
  other.m_head = nullptr;
  other.m_tail = nullptr;
}

template <typename T>
list<T>::list(const list<T> &copy)
    : m_head(nullptr), m_tail(nullptr), m_size(0) {
  Node *temp = copy.m_head;
  while (temp) {
    push_back(temp->data);
    temp = temp->next;
  }
}

template <typename T>
list<T>::list(std::initializer_list<T> const &initList) {
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
  for (const T &value : initList) {
    push_back(value);
  }
  m_size = initList.size();
};

template <typename T>
void list<T>::clear() {
  Node *current = m_head;
  while (current != nullptr) {
    Node *next = current->next;

    delete current;
    current = nullptr;
    current = next;
  }
  m_head = m_tail = nullptr;
  m_size = 0;
}

template <typename T>
list<T>::~list() {
  list<T>::clear();
}

template <typename T>
list<T> &list<T>::operator=(const list<T> &other) {
  list copy(other);
  *this = std::move(copy);
  return *this;
}

template <typename T>
list<T> &list<T>::operator=(list &&other) noexcept {
  if (this != &other) {
    clear();

    std::swap(m_size, other.m_size);
    std::swap(m_head, other.m_head);
    std::swap(m_tail, other.m_tail);
  }

  return *this;
}

template <typename T>
const T &list<T>::front() {
  return m_head->data;
}

template <typename T>
const T &list<T>::back() {
  Node *temp = m_head;
  while (temp->next != nullptr) {
    temp = temp->next;
  }
  return temp->data;
}

template <typename T>
void list<T>::push_back(const T &v) {
  Node *el = new Node(v);
  el->data = v;
  el->next = nullptr;
  el->prev = nullptr;
  if (m_tail == nullptr) {
    m_head = el;
    m_tail = el;
  } else {
    m_tail->next = el;
    el->prev = m_tail;
    m_tail = m_tail->next;
  }
  m_size++;
}

template <typename T>
void list<T>::pop_back() {
  if (m_size == 0) return;

  Node *ptr = m_tail;
  if (m_size == 1) {
    m_head = m_tail = nullptr;
  } else {
    m_tail = m_tail->prev;
    m_tail->next = nullptr;
  }
  delete ptr;
  m_size--;
}

template <typename T>
void list<T>::push_front(const T &v) {
  Node *el = new Node(v);
  if (m_head == nullptr) {
    m_tail = el;
  } else {
    el->next = m_head;
    m_head->prev = el;
  }
  m_head = el;
  m_size++;
}

template <typename T>
void list<T>::pop_front() {
  if (m_head == nullptr) return;

  Node *ptr = m_head;
  if (m_head == m_tail) {
    m_head = nullptr;
    m_tail = nullptr;

  } else {
    m_head = ptr->next;
    m_head->prev = nullptr;
  }
  delete ptr;
  --m_size;
}

template <typename T>
bool list<T>::empty() const {
  return m_head == nullptr;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return iterator(m_head);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(nullptr);
}

template <typename T>
void list<T>::erase(iterator pos) {
  Node *pos_Node = pos.getNodePtr();

  if (pos_Node == nullptr) return;
  if (pos_Node == m_head)
    pop_front();
  else if (pos_Node == m_tail)
    pop_back();
  else {
    iterator it = iterator(m_head);
    Node *erase_el = m_head;
    while (pos != it) {
      erase_el = erase_el->next;
      it++;
    }
    Node *prev_el = erase_el->prev;
    Node *next_el = erase_el->next;
    prev_el->next = next_el;
    next_el->prev = prev_el;
    erase_el->next = nullptr;
    erase_el->prev = nullptr;
    delete erase_el;
    m_size--;
  }
}

template <typename T>
void list<T>::swap(list<T> &other) {
  std::swap(m_head, other.m_head);
  std::swap(m_tail, other.m_tail);
  std::swap(m_size, other.m_size);
}

template <typename T>
void list<T>::sort() {
  if (m_size > 1) {
    for (std::size_t i = 0; i < m_size; i++) {
      Node *ptr = m_head;
      for (std::size_t j = 0; j < m_size - i; j++) {
        if (ptr->next != nullptr && ptr->next->data < ptr->data) {
          T tmp = ptr->next->data;
          ptr->next->data = ptr->data;
          ptr->data = tmp;
        }
        ptr = ptr->next;
      }
    }
  }
}

template <typename T>
void list<T>::merge(list<T> &other) {
  Node *temp_other = other.m_head;
  for (std::size_t j = 0; j < other.m_size; j++) {
    push_back(temp_other->data);
    temp_other = temp_other->next;
  }
  sort();
}

template <typename T>
void list<T>::splice(const_iterator pos, list<T> &other) {
  Node *pos_Node = const_cast<Node *>(pos.getNodePtr());

  Node *pos_Node_next = const_cast<Node *>(pos.getNodePtr());
  Node *temp_other = other.m_head;

  if (pos_Node == m_head) {
    for (std::size_t i = 0; i < other.m_size - 1; i++) {
      temp_other = temp_other->next;
    }
    temp_other->next = m_head;
    m_head = other.m_head;
  } else {
    pos_Node = pos_Node->prev;
    for (std::size_t i = 0; i < other.m_size; i++) {
      pos_Node->next = temp_other;
      pos_Node->next->prev = pos_Node;
      temp_other = temp_other->next;
      pos_Node = pos_Node->next;
    }
    pos_Node->next = pos_Node_next;
  }
  other.m_head = nullptr;
  other.m_tail = nullptr;
  m_size += other.m_size;
  other.m_size = 0;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() {
  return std::numeric_limits<std::size_t>::max() / sizeof(T);
}

template <typename T>
typename list<T>::size_type list<T>::size() {
  return m_size;
}

template <typename T>
typename list<T>::iterator list<T>::insert(list<T>::iterator pos,
                                           list<T>::const_reference value) {
  Node *ptr = pos.getNodePtr();
  if (ptr == m_head) {
    Node *newNode = new Node(value);
    newNode->next = m_head;
    if (m_head != nullptr) {
      m_head->prev = newNode;
    }
    m_head = newNode;
    if (m_tail == nullptr) {
      m_tail = newNode;
    }
  } else {
    Node *current = m_head;
    while (current != nullptr && current->next != ptr) {
      current = current->next;
    }
    if (current != nullptr) {
      Node *newNode = new Node(value);
      newNode->next = current->next;
      if (current->next != nullptr) {
        current->next->prev = newNode;
      }
      current->next = newNode;
      if (newNode->next == nullptr) {
        m_tail = newNode;
      }
    }
  }
  m_size++;
  return iterator(ptr);
}

template <typename T>
void list<T>::reverse() {
  Node *temp_head = m_head;
  Node *temp_tail = m_tail;
  value_type val = m_head->data;
  if (temp_head == m_tail) {
    return;
  } else {
    for (size_type i = 0; i < m_size / 2; i++) {
      val = temp_head->data;
      temp_head->data = temp_tail->data;
      temp_tail->data = val;
      temp_head = temp_head->next;
      temp_tail = temp_tail->prev;
    }
  }
}

template <typename T>
void list<T>::unique() {
  auto it1 = begin();
  ++it1;
  if (m_head == nullptr || m_head == m_tail) return;
  for (auto it = it1; it != end(); ++it) {
    auto it2 = it;
    --it2;
    if (*it == *it2) {
      // --it2;
      erase(it2);
    }
  }
}
}  // namespace s21

#endif
