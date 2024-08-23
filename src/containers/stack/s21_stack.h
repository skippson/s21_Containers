#ifndef S21_STACK
#define S21_STACK

#include "../vector/s21_vector.h"

namespace s21 {
template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  stack() : data_() {}
  stack(std::initializer_list<value_type> const &items) : data_(items) {}
  stack(const stack &s) : data_(s.data_) {}
  stack(stack &&s) : data_(std::move(s.data_)) {}
  ~stack() { data_.~vector(); }

  stack operator=(stack &&s) {
    data_ = std::move(s.data_);
    return *this;
  }

  void pop() { data_.pop_back(); }
  void swap(stack &other) { data_.swap(other.data_); }

  void push(const_reference value) { data_.push_back(value); }

  bool empty() { return data_.empty(); }

  size_type size() { return data_.size(); }

  const_reference top() { return data_.back(); }

 private:
  s21::vector<value_type> data_;
};
}  // namespace s21

#endif