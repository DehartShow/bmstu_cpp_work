//
// Created by dehart on 11/16/23.
//
#include <iostream>
#ifndef EXAMPLE_ARRAY_BUNDLE_H
#define EXAMPLE_ARRAY_BUNDLE_H
template <typename T>
class array_bundle {
 public:
  array_bundle() = default;
  explicit array_bundle(size_t size) {
    size_ = size;
    raw_ptr_ = new T[size];
  }

  explicit array_bundle(T *ptr) noexcept { raw_ptr_ = ptr; }

  array_bundle(const array_bundle &other_bundle) {
    raw_ptr_ = new T[other_bundle.size_];
    for (size_t i = 0; i < other_bundle.size_; i++) {
      raw_ptr_[i] = other_bundle[i];
    }
  };

  array_bundle &operator=(const array_bundle &other_bundle) {
    delete[] raw_ptr_;
    size_ = other_bundle.size_;
    raw_ptr_ = new T[other_bundle.size_];
    for (size_t i = 0; i < other_bundle.size_; i++) {
      raw_ptr_[i] = other_bundle[i];
    }
    return *this;
  };

  T &operator[](size_t index) noexcept {
    return index > sizeof(raw_ptr_) ? raw_ptr_[0] : raw_ptr_[index];
  }

  const T &operator[](size_t index) const noexcept {
    return index > sizeof(raw_ptr_) ? raw_ptr_[0] : raw_ptr_[index];
  }
  explicit operator bool() const { return raw_ptr_ != nullptr; }

  T *Release() noexcept {
    auto release = raw_ptr_;
    raw_ptr_ = nullptr;
    return release;
  }

  T *Get() const noexcept { return raw_ptr_; }

  ~array_bundle() {
    delete[] raw_ptr_;
    size_ = 0;
  }

  void swap(array_bundle &other) noexcept {
    array_bundle rvalue = std::move(other);
    other = std::move(*this);
    *this = std::move(rvalue);
  }

 private:
  T *raw_ptr_ = nullptr;
  size_t size_ = 0;
};

#endif  // EXAMPLE_ARRAY_BUNDLE_H
