#ifndef S21_VECTOR
#define S21_VECTOR

#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  vector() : arr_(nullptr), size_(0), capacity_(0) {}

  explicit vector(size_type n) : vector() {
    size_ = n;
    capacity_ = n;
    n > 0 ? arr_ = new value_type[n] : arr_ = nullptr;
  }

  vector(std::initializer_list<value_type> const &baza) : vector() {
    size_ = baza.size();
    capacity_ = baza.size();
    arr_ = new value_type[capacity_];
    std::copy(baza.begin(), baza.end(), arr_);
  }

  vector(const vector &v) : vector() { operator=(v); }

  vector(vector &&v) : vector() { operator=(std::move(v)); }

  ~vector() { delV(); }

  vector &operator=(const vector &v) {
    if (this != &v) {
      delV();
      size_ = v.size_;
      capacity_ = v.capacity_;
      if (size_ > 0) {
        arr_ = new value_type[capacity_];
        for (size_type i = 0; i < size_; i++) {
          arr_[i] = v.arr_[i];
        }
      }
    }
    return *this;
  }

  vector &operator=(vector &&v) {
    if (this != &v) {
      delV();
      size_ = v.size_;
      capacity_ = v.capacity_;
      arr_ = v.arr_;
      v.arr_ = nullptr;
      v.size_ = 0;
      v.capacity_ = 0;
    }
    return *this;
  }

  reference at(const size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("Error: invalid index");
    }
    return arr_[pos];
  }

  inline reference operator[](const size_type pos) { return at(pos); }

  const_reference front() const {
    if (empty()) {
      throw std::logic_error("Error: Vector is epmty");
    }
    return arr_[0];
  }

  const_reference back() const {
    if (empty()) {
      throw std::logic_error("Error: Vector is epmty");
    }
    return arr_[size_ - 1];
  }

  inline iterator data() { return &arr_[0]; }

  inline iterator begin() { return &arr_[0]; }

  inline const_iterator begin() const { return &arr_[0]; }

  inline iterator end() { return &arr_[size_]; }

  inline const_iterator end() const { return &arr_[size_]; }

  inline bool empty() const { return begin() == end(); }

  inline size_type size() { return std::distance(begin(), end()); }

  inline size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(size_type);
  }

  void reserve(size_type size) {
    if (size > max_size()) {
      throw std::length_error("Error: out of range memory");
    }
    if (size > capacity_) {
      iterator temp = arr_;
      arr_ = new value_type[size];
      for (size_type i = 0; i < size_; i++) {
        arr_[i] = temp[i];
      }
      delete[] temp;
      capacity_ = size;
    }
  }

  void reasize(size_type size) {
    if (size > max_size()) {
      throw std::length_error("Error: out of range memory");
    }
    if (size > capacity_) {
      reserve(size);
      size_ = size;
    }

    if (size < capacity_) {
      iterator temp = arr_;
      arr_ = new value_type[size];
      for (size_type i = 0; i < size; i++) {
        arr_[i] = temp[i];
      }
      delete[] temp;
      size_ = size;
    }
  }

  size_type capacity() { return capacity_; }

  void reduce() {
    capacity_ = size_;
    reserve(capacity_);
  }

  inline void clear() { size_ = 0; }

  void pop_back() {
    if (size_ == 0) {
      throw std::length_error("Error: empty size");
    }
    size_ -= 1;
  }

  void push_back(const_reference value) {
    if (size_ >= capacity_) {
      if (capacity_ == 0) {
        reserve(1);
      } else {
        reserve(capacity_ + 2);
      }
    }
    arr_[size_] = value;
    size_++;
  }

  void swap(vector &other) {
    std::swap(arr_, other.arr_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  void sort() { std::sort(begin(), end()); }

  iterator insert(iterator pos, const_reference value) {
    if (pos < begin() || pos > end()) {
      throw std::length_error("Error: invalid area of memory");
    }

    if (pos == end()) {
      push_back(value);
      return arr_ + size_ - 1;
    }
    size_type newPos = std::distance(begin(), pos);
    push_back(value);

    value_type temp = arr_[newPos];
    arr_[newPos] = value;
    for (size_type i = newPos + 1; i < size() - 1; i++) {
      std::swap(temp, arr_[i]);
    }
    arr_[size() - 1] = temp;
    return arr_ + newPos;
  }

  void erase(iterator pos) {
    if (pos < begin() || pos > end()) {
      throw std::length_error("Error: invalid area of memory");
    }
    for (size_t i = std::distance(begin(), pos); i < size() - 1; i++) {
      arr_[i] = arr_[i + 1];
    }
    size_ -= 1;
  }

 private:
  iterator arr_;
  size_type size_;
  size_type capacity_;

  void delV() {
    if (arr_ != nullptr) {
      delete[] arr_;
      arr_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    }
  }
};
}  // namespace s21

#endif