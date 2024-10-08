//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// UNSUPPORTED: c++03, c++11, c++14, c++17

// <chrono>
// class month;

// constexpr month& operator+=(const month& d) noexcept;
// constexpr month& operator-=(const month& d) noexcept;

#include <chrono>
#include <cassert>
#include <type_traits>
#include <utility>

#include "test_macros.h"

constexpr bool test() {
  using month  = std::chrono::month;
  using months = std::chrono::months;

  for (unsigned i = 1; i <= 10; ++i) {
    month m(i);
    int exp = i + 10;
    while (exp > 12)
      exp -= 12;
    assert(static_cast<unsigned>(m += months{10}) == static_cast<unsigned>(exp));
    assert(static_cast<unsigned>(m) == static_cast<unsigned>(exp));
    assert(m.ok());
  }

  for (unsigned i = 1; i <= 10; ++i) {
    month m(i);
    int exp = i - 9;
    while (exp < 1)
      exp += 12;
    assert(static_cast<unsigned>(m -= months{9}) == static_cast<unsigned>(exp));
    assert(static_cast<unsigned>(m) == static_cast<unsigned>(exp));
    assert(m.ok());
  }
  return true;
}

int main(int, char**) {
  using month  = std::chrono::month;
  using months = std::chrono::months;

  ASSERT_NOEXCEPT(std::declval<month&>() += std::declval<months&>());
  ASSERT_NOEXCEPT(std::declval<month&>() -= std::declval<months&>());
  ASSERT_SAME_TYPE(month&, decltype(std::declval<month&>() += std::declval<months&>()));
  ASSERT_SAME_TYPE(month&, decltype(std::declval<month&>() -= std::declval<months&>()));

  test();
  static_assert(test());

  return 0;
}
