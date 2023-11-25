////
//// Created by dehart on 11/18/23.
////
//#include <iostream>
//#ifndef EXAMPLE_BMSTU_LIST_H
//#define EXAMPLE_BMSTU_LIST_H
//#pragma once
//
//namespace bmstu {
//template <typename T>
//class list {
//  struct node;
//
// public:
//  list() : head_(new node), tail_(new node) {
//    head_->next_node_ = tail_;
//    tail_->prev_node_ = head_;
//  }
//
//  template <typename value_t>
//  struct iterator {
//    friend class list;
//    using inerator_category = std::bidirectional_iterator_tag;
//    using reference = value_t &;
//    using pointer = value_t *;
//    using difference_type = std::ptrdiff_t;
//
//
//   private:
//    iterator() = default;
//
//    explicit iterator(node *node) : node_(node) {}
//    explicit iterator(const iterator<T> &other) {}
//
//    reference operator*() const {
//      assert(node != nullptr);
//      return static_cast<T *>(node_->value);
//    }
//  };
//
// private:
//  // узел листа
//  struct node {
//    node() = default;
//    node(node *prev, const T &value, node *next) : prev_node_(prev), value(value), next_node_(next);
//
//    T value;
//    node *next_node_;
//    node *prev_node_;
//  };
//  size_t size = 0;
//  node *head_ = nullptr;
//  node *tail_ = nullptr;
//};
//}  // namespace bmstu
//
//#endif  // EXAMPLE_BMSTU_LIST_H
