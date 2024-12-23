//
// Created by dehart on 12.03.24.
//

#pragma once
#include <cassert>
#include <memory>
#include <utility>

namespace bmstu {
template <typename Z>
class raw_memory {
 public:
  raw_memory() = default;

  explicit raw_memory(size_t size) : capacity_(size), buffer_(allocate_(size)) {}

  ~raw_memory() {
    deallocate_(buffer_);
    capacity_ = 0;
  }

  raw_memory(const raw_memory &other) = delete;
  raw_memory &operator=(const raw_memory &other) = delete;

  raw_memory(raw_memory &&other) noexcept
      : capacity_(std::exchange(other.capacity_, 0)),
        buffer_(std::exchange(other.buffer_, nullptr)) {}

  raw_memory &operator=(raw_memory &&other) noexcept {
    if (buffer_) {
      deallocate_(buffer_);
    }
    buffer_ = std::exchange(other.buffer_, nullptr);
    capacity_ = std::exchange(other.capacity_, 0);
    return *this;
  }

  Z &operator[](size_t index) noexcept {
    assert(index < capacity_);
    return buffer_[index];
  }
  const Z &operator[](size_t index) const noexcept {
    return const_cast<raw_memory &>(*this)[index];
  }

  size_t GetCapacity() const { return capacity_; }
  Z *GetBuffer() { return buffer_; }
  const Z *GetBuffer() const { return buffer_; }

  void swap(raw_memory other) noexcept {
    std::swap(buffer_, other.buffer_);
    std::swap(capacity_, other.capacity_);
  }

 private:
  // Методы которые аллоцируют память
  static Z *allocate_(size_t size) {
    return size != 0 ? static_cast<Z *>(operator new(size * sizeof(Z)))
                     : nullptr;
  }

  static void deallocate_(Z *ptr) { operator delete(ptr); }

  // И деаллоцируют сыraрую память
  size_t capacity_ = 0;
  Z *buffer_ = nullptr;
};
}  // namespace bmstu
