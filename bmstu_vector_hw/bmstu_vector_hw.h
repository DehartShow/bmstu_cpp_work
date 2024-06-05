//
// Created by dehart on 12.03.24.
//

#pragma once
#include <algorithm>
#include <iostream>
#include <memory>

#include "raw_memory.h"
namespace bmstu {
template <typename Type>
class vector {
 public:
  struct iterator {
    using difference_type = std::ptrdiff_t;
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
      ++(*this);
      return old;
    }
    iterator operator--(int) {
      iterator old = *this;
      --(*this);
      return old;
    }
    friend bool operator==(const iterator &a, const iterator &b) {
      return a.m_ptr == b.m_ptr;
    }
    friend bool operator!=(const iterator &a, const iterator &b) {
      return !(b == a);
    }
    friend ptrdiff_t operator-(const iterator &a, const iterator &b) {
      ptrdiff_t result = a.m_ptr - b.m_ptr;
      return result;
    }
    iterator operator+(size_t n) noexcept {
      iterator copy(*this);
      copy.m_ptr += n;
      return copy;
    }
    iterator operator-(size_t n) noexcept {
      iterator copy(*this);
      copy.m_ptr += n;
      return copy;
    }

   private:
    pointer m_ptr;
  };
  using const_iterator = const iterator;

  vector() noexcept = default;

  /// явное конcтруирование
  explicit vector(size_t size) : data_(size), size_(size) {
    if constexpr (std::is_default_constructible_v<Type>) {
      std::uninitialized_value_construct_n(data_.GetBuffer(), size_);
    }
  }

  vector(const vector<Type> &other) : data_(other.size_), size_(other.size_) {
    std::uninitialized_copy_n(other.data_.GetBuffer(), other.size_,
                              this->data_.GetBuffer());
  }

  vector(vector &&dying)
      : data_(std::move(dying.data_)), size_(std::move(dying.size_)) {
    dying.size_ = 0;
  }
  vector(std::initializer_list<Type> ilist)
      : size_(ilist.size()), data_(ilist.size()) {
    if constexpr (std::is_nothrow_move_constructible_v<Type> ||
                  !std::is_copy_constructible_v<Type>) {
      std::uninitialized_move_n(ilist.begin(), ilist.size(), data_.GetBuffer());

    } else {
      std::uninitialized_copy_n(ilist.begin(), ilist.size(), data_.GetBuffer());
    }
  }

  ~vector() { std::destroy_n(data_.GetBuffer(), size_); }

  void clear() noexcept { size_ = 0; }

  vector &operator=(const vector &other) {
    if (&other != this) {
      if (other.size_ > data_.GetCapacity()) {
        vector copy(other);
        this->swap_(copy);
      } else {
        if (size_ >= other.size_) {
          std::copy_n(other.data_.GetBuffer(), other.size_, data_.GetBuffer());
          std::destroy_n(data_.GetBuffer() + other.size_, size_ - other.size_);
          size_ = other.size_;
        } else {
          std::copy_n(other.data_.GetBuffer(), other.size_, data_.GetBuffer());
          std::uninitialized_copy_n(other.data_.GetBuffer() + size_,
                                    other.size_ - size_,
                                    data_.GetBuffer() + size_);
        }
      }
    }
    return *this;
  }

  vector &operator=(vector<Type> &&other) noexcept {
    if (this != &other) {
      data_ = std::move(other.data_);
      size_ = other.size_;
      other.size_ = 0;
    }
    return *this;
  }

  iterator begin() { return iterator(data_.GetBuffer()); }
  iterator end() { return iterator(data_.GetBuffer() + size_); }
  const_iterator begin() const { return const_iterator(data_.GetBuffer()); }
  const_iterator end() const {
    return const_iterator(data_.GetBuffer() + size_);
  }
  const_iterator cbegin() const { return const_iterator(data_.GetBuffer()); }
  const_iterator cend() const {
    return const_iterator(const_cast<Type *>(data_.GetBuffer() + size_));
  }
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
  [[nodiscard]] size_t size() const noexcept { return size_; }

  [[nodiscard]] size_t capacity() const noexcept { return data_.GetCapacity(); }

  [[nodiscard]] bool empty() const noexcept { return size_ == 0; }

  void swap(vector &other) noexcept {
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
    data_.swap(other.data_);
  }

  friend void swap(vector<Type> &lhs, vector<Type> &rhs) { lhs.swap(rhs); }

  void resize(size_t new_size) {
    if (new_size > data_.GetCapacity()) {
      size_t new_capacity = std::max(new_size, data_.GetCapacity() * 2);
      reserve(new_capacity);
    }
    if (size_ > new_size) {
      std::destroy_n(data_.GetBuffer() + new_size, size_ - new_size);
      size_ = new_size;
    }
    if constexpr (std::is_default_constructible_v<Type>) {
      std::uninitialized_value_construct_n(data_.GetBuffer() + size_,
                                           new_size - size_);
    }
    size_ = new_size;
  }
  void reserve(size_t new_capacity) {
    if (new_capacity <= data_.GetCapacity()) {
      return;
    } else if (new_capacity > data_.GetCapacity()) {
      new_capacity = std::max(new_capacity, data_.GetCapacity() * 2);
      raw_memory<Type> new_data(new_capacity);
      if constexpr (std::is_nothrow_move_constructible_v<Type> ||
                    !std::is_copy_constructible_v<Type>) {
        std::uninitialized_move_n(data_.GetBuffer(), size_,
                                  new_data.GetBuffer());
      } else {
        std::uninitialized_copy_n(data_.GetBuffer(), size_,
                                  new_data.GetBuffer());
      }

      std::destroy_n(data_.GetBuffer(), size_);
      data_.swap(std::move(new_data));
    }
  }

  void pop_back() noexcept {
    assert(size_ != 0);
    std::destroy_at(data_.GetBuffer() + (size_ - 1));
    --size_;
  }

  template <typename... Args>
  Type &emplace_back(Args &&...args) {
    if (size_ == data_.GetCapacity()) {
      auto new_capacity = (size_ == 0) ? 1 : size_ * 2;
      this->reserve(new_capacity);
    }
    new (data_.GetBuffer() + size_) Type(std::forward<Args>(args)...);
    ++size_;
    return data_[size_ - 1];
  }

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    iterator tmp_pos = begin();
    if (pos == cend()) {
      emplace_back(std::forward<Args>(args)...);
      return tmp_pos = end() - 1;
    } else if (size_ == data_.GetCapacity()) {
      size_t new_capacity = (size_ == 0) ? 1 : size_ * 2;
      raw_memory<Type> new_data(new_capacity);
      size_t destination_pos = pos - begin();
      new (new_data.GetBuffer() + destination_pos)
          Type(std::forward<Args>(args)...);
      if constexpr (std::is_nothrow_move_constructible_v<Type> ||
                    !std::is_copy_constructible_v<Type>) {
        std::uninitialized_move_n(data_.GetBuffer(), destination_pos,
                                  new_data.GetBuffer());
      } else {
        try {
          std::uninitialized_copy_n(data_.GetBuffer(), destination_pos,
                                    new_data.GetBuffer());
        } catch (...) {
          std::destroy_n(new_data.GetBuffer() + destination_pos, 1);
          throw;
        }
      }
      if constexpr (std::is_nothrow_move_constructible_v<Type> ||
                    !std::is_copy_constructible_v<Type>) {
        std::uninitialized_move_n(data_.GetBuffer() + destination_pos,
                                  size_ - destination_pos,
                                  new_data.GetBuffer() + destination_pos + 1);
      } else {
        try {
          std::uninitialized_copy_n(data_.GetBuffer() + destination_pos,
                                    size_ - destination_pos,
                                    new_data.GetBuffer() + destination_pos + 1);
        } catch (...) {
          std::destroy_n(new_data.GetBuffer() + destination_pos, 1);
          throw;
        }
      }
      std::destroy_n(data_.GetBuffer(), size_);
      data_.swap(std::move(new_data));
      tmp_pos = begin() + destination_pos;
      ++size_;
    }
    return tmp_pos;
  }

  iterator erase(const_iterator pos) {
    assert(size_ != 0);
    size_t index = pos - begin();
    if (index >= size_) {
      throw std::out_of_range("Index out of range");
    }
    Type *element = data_.GetBuffer() + index;
    std::move(element + 1, end(), element);
    std::destroy_at(data_.GetBuffer() + index);
    --size_;
    return begin() + index;
  }

  void insert(const_iterator pos, Type &&value) {
    emplace(pos, std::forward<Type>(value));
  }

  void push_back(Type &&value) { emplace(end(), std::forward<Type>(value)); }

  bool operator==(const vector<Type> &other) const noexcept {
    if (size_ != other.size_) {
      return false;
    }
    for (size_t i = 0; i < size_; ++i) {
      if (data_[i] != other.data_[i]) {
        return false;
      }
    }
    return true;
  }

  friend std::ostream &operator<<(std::ostream &os, const vector<Type> &other) {
    os << "[ ";
    for (size_t i = 0; i < other.size(); ++i) {
      os << other[i];
      if (i < other.size() - 1) {
        os << ", ";
      }
    }
    os << " ]";
    return os;
  }
  friend bool operator!=(const vector<Type> &l, const vector<Type> &r) {
    return !(l == r);
  }
  friend bool operator<(const vector<Type> &l, const vector<Type> &r) {
    return std::lexicographical_compare(l, r);
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

 private:
  void swap_(vector<Type> &other) { std::swap(*this, other); }

  size_t size_ = 0;
  raw_memory<Type> data_;
};
}  // namespace bmstu
