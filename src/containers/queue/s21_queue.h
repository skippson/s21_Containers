#ifndef S21_QUEUE
#define S21_QUEUE

#include "../list/s21_list.h"

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue() : data_(){};
  queue(std::initializer_list<value_type> const &items) : data_(items) {}
  queue(const queue &q) : data_(q.data_){};
  queue(queue &&q) : data_(std::move(q.data_)) {}
  ~queue() { data_.clear(); }

  queue operator=(queue &&q) {
    data_ = std::move(q.data_);
    return *this;
  }

  const_reference front() { return data_.front(); }

  const_reference back() { return data_.back(); }

  bool empty() { return data_.empty(); }

  size_type size() { return data_.size(); }

  void push(const_reference value) { return data_.push_back(value); }

  void pop() { return data_.pop_front(); }

  void swap(queue &q) { data_.swap(q.data_); }

 private:
  s21::list<value_type> data_;
};
}  // namespace s21

#endif