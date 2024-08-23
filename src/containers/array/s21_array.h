#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <iostream>

namespace s21 {
template <typename T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array() : size_(N) {}

  array(const std::initializer_list<value_type> &items) {
    size_ = N;
    std::copy(items.begin(), items.end(), data_);
  }

  array(const array &a) {
    size_ = a.size_;
    std::copy(a.data_, a.data_ + a.size_, data_);
  }

  array(array &&a) {
    size_ = a.size_;
    std::move(a.data_, a.data_ + N, data_);
  }

  ~array() = default;

  array &operator=(const array &a) {
    if (this != &a) {
      size_ = a.size_;
      if (size_ > 0) {
        for (size_type i = 0; i < size_; i++) {
          data_[i] = a.data_[i];
        }
      }
    }

    return *this;
  }

  array &operator=(array &&a) {
    correct();
    a.correct();
    if (this != &a) {
      size_ = a.size_;
      for (size_type i = 0; i < size_; i++) {
        data_[i] = std::move(a.data_[i]);
      }
    }

    return *this;
  }

  inline reference at(size_type pos) {
    correct();
    if (pos >= size_) {
      throw std::out_of_range("Error: invalid index");
    }

    return data_[pos];
  }

  inline reference operator[](size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("Error: invalid index");
    }
    return data_[pos];
  }

  inline const_reference front() {
    correct();
    return data_[0];
  }

  inline const_reference back() {
    correct();
    return data_[N - 1];
  }

  inline iterator data() { return data_; }

  inline iterator begin() { return data_ + size_; }

  inline iterator end() { return data_ + size_; }

  inline bool empty() { return size_ == 0 ? true : false; }

  inline size_type size() { return size_; }

  inline size_type max_size() { return size(); }

  void swap(array &other) {
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
  }

  void fill(const_reference value) {
    correct();
    if (empty()) {
      throw std::logic_error("Error: Array is empty");
    }
    for (size_type i = 0; i < size_; i++) {
      data_[i] = value;
    }
  }

 private:
  value_type data_[N];
  size_type size_;

  inline void correct() {
    if (size_ < 0) {
      throw std::length_error("Error: empty array");
    }
  }
};
}  // namespace s21

#endif