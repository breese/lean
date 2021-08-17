#ifndef LEAN_DETAIL_STD_ATOMIC_HPP
#define LEAN_DETAIL_STD_ATOMIC_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

namespace lean
{
namespace v1
{

static_assert(__cpp_lib_atomic_wait >= 201907L, "<atomic> not included");

template <typename T>
class atomic : public std::atomic<T>
{
    using base = std::atomic<T>;
public:
    using value_type = T;
    using base::base;
};

template <typename T>
void atomic_notify_one(std::atomic<T>* object)
{
    std::atomic_notify_one(object);
}

template <typename T>
void atomic_wait(const std::atomic<T>* object,
                 typename std::atomic<T>::value_type old) noexcept
{
    std::atomic_wait(object, std::move(old));
}

template <typename T>
void atomic_wait_explicit(const std::atomic<T>* object,
                          typename std::atomic<T>::value_type old,
                          std::memory_order order) noexcept
{
    std::atomic_wait_explicit(object, std::move(old), order);
}

} // namespace v1
} // namespace lean

#endif // LEAN_DETAIL_STD_ATOMIC_HPP
