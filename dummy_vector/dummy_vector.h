//
// Created by dehart on 11/16/23.
//
#include <algorithm>
#include <iostream>

#include "array_bundle.h"
#ifndef DUMMY_VECTOR_DUMMY_VECTOR_H_
#define DUMMY_VECTOR_DUMMY_VECTOR_H_

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
    explicit iterator(pointer ptr) : m_ptr(ptr) {}
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
      return a.m_ptr == b.m_ptr;
    }
    friend bool operator!=(const iterator &a, const iterator &b) {
      return !(a == b);
    }
    friend difference_type operator-(const iterator &end,
                                     const iterator &begin) {
      difference_type result = end.m_ptr - begin.m_ptr;
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
  explicit vector(size_t size, const Type &value = Type{})
      : size_(size), capacity_(size), data_(size) {
    auto first = begin();
    auto last = end();
    for (; first != last; ++first) {
      *first = value;
    }
  }
  vector(const vector<Type> &other)
      : size_(other.size_), capacity_(other.capacity_), data_(other.size_) {
    auto first = begin();
    auto ofirst = other.begin();
    auto olast = other.end();
    for (; ofirst != olast; ++ofirst, ++first) {
      *first = *ofirst;
    }
  }
  vector(vector<Type> &&other) { this->swap(other); }

  vector(std::initializer_list<Type> ilist)
      : size_(ilist.size()), capacity_(ilist.size()), data_(ilist.size()) {
    iterator vit = begin();
    for (auto it = ilist.begin(); it != ilist.end(); ++it, ++vit) {
      *vit = *it;
    }
  }
  void clear() noexcept { *this = {}; }
  vector &operator=(const vector<Type> &other) {
    this = {other};
    return *this;
  }
  vector &operator=(vector<Type> &&other) {
    this->swap(other);
    return *this;
  }
  iterator begin() noexcept { return iterator(data_.Get()); }
  iterator end() noexcept { return iterator(data_.Get()) + size_; }
  const_iterator begin() const noexcept { return iterator(data_.Get()); }
  const_iterator end() const noexcept { return iterator(data_.Get() + size_); }
  const_iterator cbegin() const noexcept { return iterator(data_.Get()); }
  const_iterator cend() const noexcept { return iterator(data_.Get() + size_); }

  typename iterator::reference operator[](size_t index) noexcept {
    return data_[index];
  }
  typename const_iterator::reference operator[](size_t index) const noexcept {
    return const_cast<typename const_iterator::reference>(data_[index]);
  }
  typename iterator::reference at(size_t index) { return data_[index]; }
  typename const_iterator::reference at(size_t index) const {
    return const_cast<typename const_iterator::reference>(data_[index]);
  }
  size_t size() const noexcept { return size_; }
  size_t capacity() const noexcept { return capacity_; }
  bool empty() const noexcept { return size_ == 0; }
  void swap(vector &other) noexcept {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    data_.swap(other.data_);
  }
  friend void swap(vector<Type> &lhs, vector<Type> &rhs) { lhs.swap(rhs); }
  void resize(size_t new_size) {
    if (new_size > capacity_) {
      size_t new_capacity = std::max(new_size, capacity_ * 2);
      reserve(new_capacity);
    }
    if (size_ > new_size) {
      size_ = new_size;
      return;
    }
    for (auto it = end(); it != begin() + new_size; ++it) {
      *it = Type{};
    }
    size_ = new_size;
  }
  void reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
      new_capacity = std::max(new_capacity, capacity_ * 2);
      array_bundle<Type> new_data(new_capacity);
      for (auto it = begin(), nit = iterator(new_data.Get()); it != end();
           ++it, ++nit) {
        *nit = std::move(*it);
      }
      data_.swap(new_data);
      capacity_ = new_capacity;
    }
  }
  iterator insert(const_iterator pos, Type &&value) {
    auto n = pos - begin();
    if (capacity_ == 0) {
      reserve(1);
    }
    if (size_ == capacity_) {
      capacity_ *= 2;
    }
    array_bundle<Type> temp(capacity_);
    Type *temp_ptr = temp.Get();
    for (auto first = begin(); first != begin() + n; ++first, ++temp_ptr) {
      *temp_ptr = std::move(*first);
    }
    temp[n] = std::move(value);
    temp_ptr = temp.Get() + n + 1;
    if (++n < size_) {
      for (auto first = begin() + n; first != end(); ++first, ++temp_ptr) {
        *temp_ptr = std::move(*first);
      }
    }
    data_.swap(temp);
    ++size_;
    return begin() + n;
  }
  iterator insert(const_iterator pos, const Type &value) {
    auto n = pos - begin();
    if (capacity_ == 0) {
      reserve(1);
    }
    if (size_ == capacity_) {
      capacity_ *= 2;
    }
    array_bundle<Type> temp(capacity_);
    Type *temp_ptr = temp.Get();
    for (auto first = begin(); first != begin() + n; ++first, ++temp_ptr) {
      *temp_ptr = std::move(*first);
    }
    temp[n] = std::move(value);
    temp_ptr = temp.Get() + n + 1;
    if (++n < size_) {
      for (auto first = begin() + n; first != end(); ++first, ++temp_ptr) {
        *temp_ptr = std::move(*first);
      }
    }
    data_.swap(temp);
    ++size_;
    return begin() + n;
  }
  void push_back(const Type &value) { insert(end(), value); }
  void push_back(Type &&value) { insert(end(), value); }
  void pop_back() noexcept { (*this)[--size_] = {}; }
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
    return !(l == r);
  }
  friend bool operator<(const vector<Type> &l, const vector<Type> &r) {
    return lexicographical_compare_(l, r);
  }
  friend bool operator>(const vector<Type> &l, const vector<Type> &r) {
    return !(l <= r);
  }
  friend bool operator<=(const vector<Type> &l, const vector<Type> &r) {
    return (l < r || l == r);
  }
  friend bool operator>=(const vector<Type> &l, const vector<Type> &r) {
    return !(l < r);
  }
  friend std::ostream &operator<<(std::ostream &os, const vector<Type> &other) {
    for (auto i = other.begin(); i != other.end(); ++i) {
      os << *i << " ";
    }
    return os;
  }

 private:
  static bool lexicographical_compare_(const vector<Type> &l,
                                       const vector<Type> &r) {
    auto lb = l.begin();
    auto rb = r.begin();
    auto le = l.end();
    auto re = r.end();
    for (; (lb != le) && (rb != re); ++lb, ++rb) {
      if (*lb < *rb) {
        return true;
      }
      if (*lb > *rb) {
        return false;
      }
    }
    return (lb == le) && (rb != re);
  }
  size_t size_ = 0;
  size_t capacity_ = 0;
  array_bundle<Type> data_;
};
}  // namespace bmstu

#endif  // DUMMY_VECTOR_DUMMY_VECTOR_H_
