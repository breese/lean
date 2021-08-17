#ifndef LEAN_DETAIL_LINUX_ATOMIC_HPP
#define LEAN_DETAIL_LINUX_ATOMIC_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <lean/detail/linux/futex.hpp>

namespace lean
{
namespace v1
{

template <typename T>
class atomic : public std::atomic<T>
{
    using base = std::atomic<T>;

public:
    using value_type = T;
    using base::base;

    void wait(value_type old,
              std::memory_order order = std::memory_order_seq_cst) const noexcept
    {
        while (base::load(order) == old)
        {
            if (!futex.wait())
                break;
        }
    }

    void notify_one() noexcept
    {
        futex.notify_one();
    }

    void notify_all() noexcept
    {
        futex.notify_all();
    }

private:
    detail::futex futex;
};

template <typename T>
void atomic_notify_one(atomic<T>* object)
{
    object->notify_one();
}

template <typename T>
void atomic_wait(const atomic<T>* object,
                 typename atomic<T>::value_type old) noexcept
{
    object->wait(std::move(old));
}

template <typename T>
void atomic_wait_explicit(const atomic<T>* object,
                          typename atomic<T>::value_type old,
                          std::memory_order order) noexcept
{
    object->wait(std::move(old), order);
}

} // namespace v1
} // namespace lean

#endif // LEAN_DETAIL_LINUX_ATOMIC_HPP
