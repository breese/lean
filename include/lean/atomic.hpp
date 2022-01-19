#ifndef LEAN_ATOMIC_HPP
#define LEAN_ATOMIC_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <lean/detail/config.hpp>

#if __cpp_lib_atomic_wait >= 201907L
# include <lean/detail/std/atomic.hpp>
# define LEAN_LIB_ATOMIC_WAIT __cpp_lib_atomic_wait
#elif (__linux__)
# include <lean/detail/linux/atomic.hpp>
# define LEAN_LIB_ATOMIC_WAIT LEAN_CXX11
#else
# define LEAN_LIB_ATOMIC_WAIT LEAN_CXX_NEVER
#endif

#if LEAN_CXX >= LEAN_LIB_ATOMIC_WAIT

namespace lean
{
namespace v1
{

namespace detail
{

template <typename T>
struct atomic_counter
{
    static_assert(std::is_integral<T>::value, "T must be integral");

    constexpr atomic_counter() noexcept = default;
    constexpr atomic_counter(T&& value) noexcept : value(value) {}

    T operator++() noexcept {
        return value.fetch_add(1, std::memory_order_acq_rel) + 1;
    }

    T operator++(int) noexcept {
        return value.fetch_add(1, std::memory_order_acq_rel);
    }

    T operator--() noexcept {
        return value.fetch_sub(1, std::memory_order_acq_rel) - 1;
    }

    T operator--(int) noexcept {
        return value.fetch_sub(1, std::memory_order_acq_rel);
    }

private:
    std::atomic<T> value;
};

} // namespace detail

} // namespace v1

using v1::atomic;
using v1::atomic_notify_one;
using v1::atomic_wait;
using v1::atomic_wait_explicit;

} // namespace lean

#endif // LEAN_LIB_ATOMIC_WAIT
#endif // LEAN_ATOMIC_HPP
