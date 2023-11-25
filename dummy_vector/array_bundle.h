//
// Created by dehart on 11/16/23.
//
#pragma once
#include <iostream>
#ifndef DUMMY_VECTOR_ARRAY_BUNDLE_H_
#define DUMMY_VECTOR_ARRAY_BUNDLE_H_
template <typename T>
class array_bundle {
 public:
  array_bundle() = default;
  explicit array_bundle(size_t size) { raw_ptr_ = new T[size]; }

  explicit array_bundle(T *ptr) noexcept { raw_ptr_ = ptr; }

  array_bundle(const array_bundle &other_bundle) = delete;

  array_bundle &operator=(const array_bundle &other_bundle) = delete;

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

  ~array_bundle() { delete[] raw_ptr_; }

  void swap(array_bundle &other) noexcept {
    std::swap(raw_ptr_, other.raw_ptr_);
  }

 private:
  T *raw_ptr_ = nullptr;
};

#endif  // DUMMY_VECTOR_ARRAY_BUNDLE_H_
