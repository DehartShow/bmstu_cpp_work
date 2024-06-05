//
// Created by dehart on 12.03.24.
//
#include <gtest/gtest.h>

#include "bmstu_optional.h"

TEST(Optional, Init1) {
  bmstu::optional<int> first;
  ASSERT_FALSE(first.has_value());
}
TEST(Optional, Init2) {
  bmstu::optional<int> first(3);
  ASSERT_TRUE(first.has_value());
  ASSERT_EQ(first.value(), 3);
}
TEST(Optional, Init3) {
  int value = 666;
  bmstu::optional<int> first(value);
  ASSERT_TRUE(first.has_value());
  ASSERT_EQ(first.value(), 666);
}

TEST(Optional, Init4) {
  bmstu::optional<int> first(123);
  bmstu::optional<int> second(first);
  ASSERT_TRUE(first.has_value());
  ASSERT_TRUE(second.has_value());
  ASSERT_EQ(second.value(), 123);
}

TEST(Optional, Move) {
  bmstu::optional<int> first;
  bmstu::optional<int> second(std::move(first));
  ASSERT_FALSE(first.has_value());
  ASSERT_FALSE(second.has_value());
  bmstu::optional<int> third(123);
  bmstu::optional<int> fourth(third);
  ASSERT_TRUE(third.has_value());
  ASSERT_TRUE(fourth.has_value());
  ASSERT_EQ(fourth.value(), 123);
}

TEST(Optional, Assign) {
  bmstu::optional<int> first;
  ASSERT_FALSE(first.has_value());
  first = 666;
  ASSERT_TRUE(first.has_value());
  ASSERT_EQ(first.value(), 666);
  first = 777;
  ASSERT_TRUE(first.has_value());
  ASSERT_EQ(first.value(), 777);
}

TEST(Optional, MoveOptionalValue) {
  bmstu::optional<int> first;
  ASSERT_FALSE(first.has_value());
  int a = 123;
  int b = 321;
  first = std::move(a);
  ASSERT_TRUE(first.has_value());
  ASSERT_EQ(first.value(), 123);
  first = std::move(b);
  ASSERT_TRUE(first.has_value());
  ASSERT_EQ(first.value(), 321);
}

void actionInt(const bmstu::optional<int> &a) { a.value(); }
TEST(Optional, ThrowException) {
  bmstu::optional<int> first;
  ASSERT_FALSE(first.has_value());
  ASSERT_THROW(actionInt(first), bmstu::bad_optional_access);
}

/// Структура для подсчёта вызываемых методов
struct X {
  X() noexcept { ++count_def_constr; }

  X(const X &other) noexcept {
    other.update();
    ++count_copyable;
  }

  X(X &&other) noexcept {
    std::move(other).update();
    ++count_moveable;
  }

  X &operator=(const X &other) noexcept {
    if (this != &other) {
      other.update();
      ++copy_assign;
    }
    return *this;
  }

  X &operator=(X &&other) noexcept {
    if (this != &other) {
      std::move(other).update();
      ++move_assign;
    }
    return *this;
  }

  ~X() { ++count_destruct; }

  void update() & {  // NOLINT
    ++lvalue_call_count;
  }

  void update() const & {  // NOLINT
    ++const_lvalue_call_count;
  }

  void update() && {  // NOLINT
    ++rvalue_call_count;
  }

  static size_t instance_count() {
    return count_def_constr + count_copyable + count_moveable - count_destruct;
  }

  static void reset() {
    count_def_constr = 0;
    count_copyable = 0;
    count_moveable = 0;
    copy_assign = 0;
    move_assign = 0;
    count_destruct = 0;
    lvalue_call_count = 0;
    const_lvalue_call_count = 0;
    rvalue_call_count = 0;
  }

  inline static size_t count_def_constr = 0;
  inline static size_t count_copyable = 0;
  inline static size_t count_moveable = 0;
  inline static size_t copy_assign = 0;
  inline static size_t move_assign = 0;
  inline static size_t count_destruct = 0;
  inline static size_t lvalue_call_count = 0;
  inline static size_t const_lvalue_call_count = 0;
  inline static size_t rvalue_call_count = 0;
};

TEST(Optional, X_Init1) {
  X::reset();
  ASSERT_EQ(X::instance_count(), 0);
  {
    bmstu::optional<X> first;
    ASSERT_FALSE(first.has_value());
    ASSERT_EQ(X::instance_count(), 0);
    ASSERT_EQ(X::count_def_constr, 0);
    ASSERT_EQ(X::count_copyable, 0);
    ASSERT_EQ(X::count_moveable, 0);
    ASSERT_EQ(X::copy_assign, 0);
    ASSERT_EQ(X::move_assign, 0);
    ASSERT_EQ(X::count_destruct, 0);
    ASSERT_EQ(X::lvalue_call_count, 0);
    ASSERT_EQ(X::const_lvalue_call_count, 0);
    ASSERT_EQ(X::rvalue_call_count, 0);
  }
}

TEST(Optional, X_Init2) {
  X::reset();
  ASSERT_EQ(X::instance_count(), 0);
  {
    X x_1;
    bmstu::optional<X> first(x_1);
    ASSERT_TRUE(first.has_value());
    ASSERT_EQ(X::instance_count(), 2);
    ASSERT_EQ(X::count_def_constr, 1);
    ASSERT_EQ(X::count_copyable, 1);
    ASSERT_EQ(X::count_moveable, 0);
    ASSERT_EQ(X::copy_assign, 0);
    ASSERT_EQ(X::move_assign, 0);
    ASSERT_EQ(X::count_destruct, 0);
    ASSERT_EQ(X::lvalue_call_count, 0);
    ASSERT_EQ(X::const_lvalue_call_count, 1);
    ASSERT_EQ(X::rvalue_call_count, 0);
  }
  ASSERT_EQ(X::count_def_constr, 1);
  ASSERT_EQ(X::count_copyable, 1);
  ASSERT_EQ(X::count_destruct, 2);
  ASSERT_EQ(X::instance_count(), 0);
}

TEST(Optional, X_Init3) {
  X::reset();
  ASSERT_EQ(X::instance_count(), 0);
  {
    bmstu::optional<X> first;
    bmstu::optional<X> second(first);
    ASSERT_FALSE(first.has_value());
    ASSERT_FALSE(second.has_value());
    ASSERT_EQ(X::instance_count(), 0);
    ASSERT_EQ(X::count_def_constr, 0);
    ASSERT_EQ(X::count_copyable, 0);
    ASSERT_EQ(X::count_moveable, 0);
    ASSERT_EQ(X::copy_assign, 0);
    ASSERT_EQ(X::move_assign, 0);
    ASSERT_EQ(X::count_destruct, 0);
    ASSERT_EQ(X::lvalue_call_count, 0);
    ASSERT_EQ(X::const_lvalue_call_count, 0);
    ASSERT_EQ(X::rvalue_call_count, 0);
  }
}

TEST(Optional, X_Assigment1) {
  X::reset();
  ASSERT_EQ(X::instance_count(), 0);
  {
    X x_1;
    bmstu::optional<X> first;
    first = x_1;
    ASSERT_TRUE(first.has_value());
    ASSERT_EQ(X::instance_count(), 2);
    ASSERT_EQ(X::count_def_constr, 1);
    ASSERT_EQ(X::count_copyable, 1);
    ASSERT_EQ(X::count_moveable, 0);
    ASSERT_EQ(X::copy_assign, 0);
    ASSERT_EQ(X::move_assign, 0);
    ASSERT_EQ(X::count_destruct, 0);
    ASSERT_EQ(X::lvalue_call_count, 0);
    ASSERT_EQ(X::const_lvalue_call_count, 1);
    ASSERT_EQ(X::rvalue_call_count, 0);
  }
  ASSERT_EQ(X::count_def_constr, 1);
  ASSERT_EQ(X::count_copyable, 1);
  ASSERT_EQ(X::count_destruct, 2);
  ASSERT_EQ(X::instance_count(), 0);
}

TEST(Optional, X_Assigmnet2) {
  X::reset();
  ASSERT_EQ(X::instance_count(), 0);
  {
    X x_1;
    X x_2;
    bmstu::optional<X> first(x_1);
    first = x_2;
    ASSERT_TRUE(first.has_value());
    ASSERT_EQ(X::instance_count(), 3);
    ASSERT_EQ(X::count_def_constr, 2);
    ASSERT_EQ(X::count_copyable, 1);
    ASSERT_EQ(X::count_moveable, 0);
    ASSERT_EQ(X::copy_assign, 1);
    ASSERT_EQ(X::move_assign, 0);
    ASSERT_EQ(X::count_destruct, 0);
    ASSERT_EQ(X::lvalue_call_count, 0);
    ASSERT_EQ(X::const_lvalue_call_count, 2);
    ASSERT_EQ(X::rvalue_call_count, 0);
  }
  ASSERT_EQ(X::count_def_constr, 2);
  ASSERT_EQ(X::count_copyable, 1);
  ASSERT_EQ(X::copy_assign, 1);
  ASSERT_EQ(X::count_destruct, 3);
  ASSERT_EQ(X::instance_count(), 0);
}

TEST(Optional, X_move1Value) {
  X::reset();
  ASSERT_EQ(X::instance_count(), 0);
  {
    X x_1;
    bmstu::optional<X> first(std::move(x_1));
    ASSERT_TRUE(first.has_value());
    ASSERT_EQ(X::instance_count(), 2);
    ASSERT_EQ(X::count_def_constr, 1);
    ASSERT_EQ(X::count_copyable, 0);
    ASSERT_EQ(X::count_moveable, 1);
    ASSERT_EQ(X::copy_assign, 0);
    ASSERT_EQ(X::move_assign, 0);
    ASSERT_EQ(X::count_destruct, 0);
    ASSERT_EQ(X::lvalue_call_count, 0);
    ASSERT_EQ(X::const_lvalue_call_count, 0);
    ASSERT_EQ(X::rvalue_call_count, 1);
  }
  ASSERT_EQ(X::count_def_constr, 1);
  ASSERT_EQ(X::count_moveable, 1);
  ASSERT_EQ(X::count_destruct, 2);
  ASSERT_EQ(X::instance_count(), 0);
}

TEST(Optional, X_MoveValueInstedEmpty1) {
  X::reset();
  ASSERT_EQ(X::instance_count(), 0);
  {
    X x_1;
    bmstu::optional<X> first;
    first = std::move(x_1);
    ASSERT_TRUE(first.has_value());
    ASSERT_EQ(X::instance_count(), 2);
    ASSERT_EQ(X::count_def_constr, 1);
    ASSERT_EQ(X::count_copyable, 0);
    ASSERT_EQ(X::count_moveable, 1);
    ASSERT_EQ(X::copy_assign, 0);
    ASSERT_EQ(X::move_assign, 0);
    ASSERT_EQ(X::count_destruct, 0);
    ASSERT_EQ(X::lvalue_call_count, 0);
    ASSERT_EQ(X::const_lvalue_call_count, 0);
    ASSERT_EQ(X::rvalue_call_count, 1);
  }
  ASSERT_EQ(X::count_def_constr, 1);
  ASSERT_EQ(X::count_moveable, 1);
  ASSERT_EQ(X::count_destruct, 2);
  ASSERT_EQ(X::instance_count(), 0);
}

TEST(Optional, X_MoveValueInstedValue) {
  X::reset();
  ASSERT_EQ(X::instance_count(), 0);
  {
    X x_1;
    X x_2;
    bmstu::optional<X> first(x_1);
    first = std::move(x_2);
    ASSERT_TRUE(first.has_value());
    ASSERT_EQ(X::instance_count(), 3);
    ASSERT_EQ(X::count_def_constr, 2);
    ASSERT_EQ(X::count_copyable, 1);
    ASSERT_EQ(X::count_moveable, 0);
    ASSERT_EQ(X::copy_assign, 0);
    ASSERT_EQ(X::move_assign, 1);
    ASSERT_EQ(X::count_destruct, 0);
    ASSERT_EQ(X::lvalue_call_count, 0);
    ASSERT_EQ(X::const_lvalue_call_count, 1);
    ASSERT_EQ(X::rvalue_call_count, 1);
  }
  ASSERT_EQ(X::count_def_constr, 2);
  ASSERT_EQ(X::count_copyable, 1);
  ASSERT_EQ(X::move_assign, 1);
  ASSERT_EQ(X::count_destruct, 3);
  ASSERT_EQ(X::instance_count(), 0);
}

TEST(Optional, X_Move4Empty) {
  X::reset();
  ASSERT_EQ(X::instance_count(), 0);
  {
    bmstu::optional<X> first;
    bmstu::optional<X> second(std::move(first));
    ASSERT_FALSE(first.has_value());
    ASSERT_FALSE(second.has_value());
    ASSERT_EQ(X::instance_count(), 0);
    ASSERT_EQ(X::count_def_constr, 0);
    ASSERT_EQ(X::count_copyable, 0);
    ASSERT_EQ(X::count_moveable, 0);
    ASSERT_EQ(X::copy_assign, 0);
    ASSERT_EQ(X::move_assign, 0);
    ASSERT_EQ(X::count_destruct, 0);
    ASSERT_EQ(X::lvalue_call_count, 0);
    ASSERT_EQ(X::const_lvalue_call_count, 0);
    ASSERT_EQ(X::rvalue_call_count, 0);
  }
}

TEST(Optional, X_Copy) {
  X::reset();
  ASSERT_EQ(X::instance_count(), 0);
  {
    X x_1;
    X x_2;
    bmstu::optional<X> first(x_1);
    bmstu::optional<X> second(x_2);
    second = first;
    ASSERT_TRUE(first.has_value());
    ASSERT_TRUE(second.has_value());
    ASSERT_EQ(X::instance_count(), 4);
    ASSERT_EQ(X::count_def_constr, 2);
    ASSERT_EQ(X::count_copyable, 2);
    ASSERT_EQ(X::count_moveable, 0);
    ASSERT_EQ(X::copy_assign, 1);
    ASSERT_EQ(X::move_assign, 0);
    ASSERT_EQ(X::count_destruct, 0);
    ASSERT_EQ(X::lvalue_call_count, 0);
    ASSERT_EQ(X::const_lvalue_call_count, 3);
    ASSERT_EQ(X::rvalue_call_count, 0);
  }
  ASSERT_EQ(X::count_def_constr, 2);
  ASSERT_EQ(X::count_copyable, 2);
  ASSERT_EQ(X::copy_assign, 1);
  ASSERT_EQ(X::count_destruct, 4);
  ASSERT_EQ(X::instance_count(), 0);
}

TEST(Optional, X_Move) {
  X::reset();
  ASSERT_EQ(X::instance_count(), 0);
  {
    X x_1;
    X x_2;
    bmstu::optional<X> first(x_1);
    bmstu::optional<X> second(x_2);
    second = std::move(first);
    ASSERT_TRUE(second.has_value());
    ASSERT_EQ(X::instance_count(), 4);
    ASSERT_EQ(X::count_def_constr, 2);
    ASSERT_EQ(X::count_copyable, 2);
    ASSERT_EQ(X::count_moveable, 0);
    ASSERT_EQ(X::copy_assign, 0);
    ASSERT_EQ(X::move_assign, 1);
    ASSERT_EQ(X::count_destruct, 0);
    ASSERT_EQ(X::lvalue_call_count, 0);
    ASSERT_EQ(X::const_lvalue_call_count, 2);
    ASSERT_EQ(X::rvalue_call_count, 1);
  }
  ASSERT_EQ(X::count_def_constr, 2);
  ASSERT_EQ(X::count_copyable, 2);
  ASSERT_EQ(X::move_assign, 1);
  ASSERT_EQ(X::count_destruct, 4);
  ASSERT_EQ(X::instance_count(), 0);
}

TEST(Optional, X_Move2) {
  X::reset();
  ASSERT_EQ(X::instance_count(), 0);
  {
    X x_1;
    bmstu::optional<X> first(x_1);
    bmstu::optional<X> second;
    first = std::move(second);
    ASSERT_FALSE(first.has_value());
    ASSERT_FALSE(second.has_value());
    ASSERT_EQ(X::instance_count(), 1);
    ASSERT_EQ(X::count_def_constr, 1);
    ASSERT_EQ(X::count_copyable, 1);
    ASSERT_EQ(X::count_moveable, 0);
    ASSERT_EQ(X::copy_assign, 0);
    ASSERT_EQ(X::move_assign, 0);
    ASSERT_EQ(X::count_destruct, 1);
    ASSERT_EQ(X::lvalue_call_count, 0);
    ASSERT_EQ(X::const_lvalue_call_count, 1);
    ASSERT_EQ(X::rvalue_call_count, 0);
  }
  ASSERT_EQ(X::count_def_constr, 1);
  ASSERT_EQ(X::count_copyable, 1);
  ASSERT_EQ(X::count_destruct, 2);
  ASSERT_EQ(X::instance_count(), 0);
}
