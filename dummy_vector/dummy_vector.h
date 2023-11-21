//
// Created by dehart on 11/16/23.
//
#include <iostream>

#include "array_bundle.h"
#ifndef EXAMPLE_DUMMY_VECTOR_H
#define EXAMPLE_DUMMY_VECTOR_H

namespace bmstu {
template <typename Type>
class vector {
 public:
  struct iterator {
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Type;
    using pointer = Type *;
    using reference = Type &;
    iterator(pointer ptr) : m_ptr(ptr) {}
    reference operator*() const { return *m_ptr; }
    pointer operator->() { return m_ptr; }
    iterator &operator++() {
      ++m_ptr;
      return *this;
    }
    iterator &operator--() {
      --m_ptr;
      return *this;
    }
    iterator &operator=(const iterator &other) {
      m_ptr = other.m_ptr;
      return *this;
    }
    iterator operator++(int) {
      iterator old = *this;
      ++m_ptr;
      return old;
    }
    iterator operator--(int) {
      iterator old = *this;
      --m_ptr;
      return old;
    }
    friend bool operator==(const iterator &a, const iterator &b) {
      return a.m_ptr = b.m_ptr;
    }
    friend bool operator!=(const iterator &a, const iterator &b) {
      return (a.m_ptr != b.m_ptr);
    }
    friend ptrdiff_t operator-(const iterator &a, const iterator &b) {
      ptrdiff_t result = b.m_ptr - a.m_ptr;
      return result;
    }
    iterator &operator+(size_t n) noexcept {
      m_ptr += n;
      return *this;
    }
    iterator &operator-(size_t n) noexcept {
      m_ptr -= n;
      return *this;
    }

   private:
    pointer m_ptr;
  };
  using const_iterator = const iterator;
  vector() noexcept = default;
  vector(size_t size, const Type &value = Type{}) {
    size_ = size;
    for (size_t i = 0; i < size_; ++i) data_[i] = value[i];
  }
  vector(const vector<Type> &other) {
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = other[i];
    }
  }
  vector(vector<Type> &&other) {
    size_ = other.size();
    capacity_ = other.capacity();
    data_ = std::move(other.data_);
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
  }
  vector(std::initializer_list<Type> ilist) {
    auto j = ilist.begin();
    for (size_t i = 0; i < ilist.size(); ++i, ++j) {
      data_[i] = *j;
    }
  }
  void clear() noexcept {
    size_ = 0;
    capacity_ = 0;
    delete[] data_;
  }
  vector &operator=(const vector<Type> &other) {
    if (this != &other) {
      delete[] data_;
      data_ = new Type[other.capacity_];
      for (size_t i = 0; i < other.size_; ++i) data_[i] = other.data_[i];
      size_ = other.size_;
      capacity_ = other.capacity_;
    }
    return *this;
  }
  vector &operator=(vector<Type> &&other) {
    if (this != &other) {
      delete[] data_;
      data_ = other.data_;
      size_ = other.size_;
      capacity_ = other.capacity_;
      other.data_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }
    return *this;
  }
  iterator begin() noexcept { return iterator(data_.Get()); }
  iterator end() noexcept { return iterator(data_.Get()) + size_; }
  const_iterator begin() const noexcept { return &data_[0]; }
  const_iterator end() const noexcept { return &data_[size_]; }
  const_iterator cbegin() const noexcept { return &data_[0]; }
  const_iterator cend() const noexcept { return &data_[size_]; }

  typename iterator::reference operator[](size_t index) noexcept {
    return data_[index];
  }
  typename const_iterator::reference operator[](size_t index) const noexcept {
    return const_cast<const const_iterator>(data_[index]);
  }
  typename iterator::reference at(size_t index) { return data_[index]; }
  typename const_iterator::reference at(size_t index) const {
    return const_cast<const const_iterator>(data_[index]);
  }
  size_t size() const noexcept { return size_; }
  size_t capacity() const noexcept { return capacity_; }
  bool empty() const noexcept { return size_ == 0; }
  void swap(vector &other) noexcept {}
  friend void swap(vector<Type> &lhs, vector<Type> &rhs) {
    vector<Type> rvalue = std::move(rhs);
    rhs = std::move(lhs);
    lhs = std::move(rvalue);
  }
  void resize(size_t new_size) {
    size_ = new_size;
    while (size_ > capacity_) capacity_ *= 2;
  }
  void reserve(size_t new_capacity) {
    array_bundle<Type> new_data(new_capacity);
    for (size_t i = 0; i < capacity_; ++i) {
      new_data[i] = data_[i];
    }
    capacity_ = new_capacity;
    size_ = new_data;
  }
  iterator insert(const_iterator pos, Type &&value) {
    auto j = begin();
    size_t posi = 0;
    while (j != pos) {
      ++posi;
      ++j;
    }
    push_back(value);
    for (size_t i = size_ - 1; i > posi; --i) {
      swap((*this)[i], (*this)[i - 1]);
    }
    return begin() + posi;
  }
  iterator insert(const_iterator pos, const Type &value) {
    auto j = begin();
    size_t posi = 0;
    while (j != pos) {
      ++posi;
      ++j;
    }
    push_back(value);
    for (size_t i = size_ - 1; i > posi; --i) {
      swap((*this)[i], (*this)[i - 1]);
    }
    return begin() + posi;
  }
  void push_back(const Type &value) {
    if (size_ >= capacity_) {
      capacity_ *= 2;
      Type *tmp = data_;
      data_ = new Type[capacity_];
      for (size_t i = 0; i < size_; ++i) data_[i] = tmp[i];
      delete[] tmp;
    }
    data_[size_++] = value;
  }
  void push_back(Type &&value) {
    if (size_ >= capacity_) {
      capacity_ *= 2;
      Type *tmp = data_;
      data_ = new Type[capacity_];
      for (size_t i = 0; i < size_; ++i) data_[i] = tmp[i];
      delete[] tmp;
    }
    data_[size_++] = value;
  }
  void pop_back() noexcept {
    if (size_ > 0) {
      --size_;
    }
    return *this;
  }
  friend bool operator==(const vector<Type> &l, const vector<Type> &r) {
    if (l.size() != r.size()) {
      return false;
    }
    for (size_t i = 0; i < l.size(); ++i) {
      if (l[i] != r[i]) {
        return false;
      }
    }
    return true;
  }
  friend bool operator!=(const vector<Type> &l, const vector<Type> &r) {
    return l != r;
  }
  friend bool operator<(const vector<Type> &l, const vector<Type> &r) {
    return lexicographical_compare_(l, r);
  }
  friend bool operator>(const vector<Type> &l, const vector<Type> &r) {
    return !(l <= r);
  }
  friend bool operator<=(const vector<Type> &l, const vector<Type> &r) {
    return l < r && l == r;
  }
  friend bool operator>=(const vector<Type> &l, const vector<Type> &r) {
    return l > r && l == r;
  }
  friend std::ostream &operator<<(std::ostream &os, const vector<Type> &other) {
    for (size_t i = 0; i < &other.size_; ++i) {
      os << other[i] << " ";
    }
    return os;
  }

 private:
  static bool lexicographical_compare_(const vector<Type> &l,
                                       const vector<Type> &r) {
    for (size_t i = 0; i < std::min(l.size(), r.size()); ++i) {
      if (l[i] < r[i]) {
        return true;
      }
    }
    return l.size() > r.size();
  }
  size_t size_ = 0;
  size_t capacity_ = 0;
  array_bundle<Type> data_;
};
}  // namespace bmstu

#endif  // EXAMPLE_DUMMY_VECTOR_H
