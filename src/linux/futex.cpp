///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <linux/futex.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <thread> // std::this_thread::yield
#include <lean/detail/linux/atomic.hpp>

namespace
{

constexpr int convert(std::memory_order order)
{
    // Ignores consume memory order
    return (order == std::memory_order_seq_cst
            ? __ATOMIC_SEQ_CST
            : (order == std::memory_order_acq_rel
               ? __ATOMIC_ACQ_REL
               : (order == std::memory_order_acquire
                  ? __ATOMIC_ACQUIRE
                  : (order == std::memory_order_release
                     ? __ATOMIC_RELEASE
                     : __ATOMIC_RELAXED))));
}

} // anonymous namespace

namespace lean
{
namespace v1
{
namespace detail
{

auto futex::load(std::memory_order order) const noexcept -> futex::value_type
{
    return __atomic_load_n(&value, convert(order));
}

auto futex::fetch_add(value_type arg, std::memory_order order) noexcept -> futex::value_type
{
    return __atomic_fetch_add(&value, arg, convert(order));
}

bool futex::wait() const noexcept
{
    value_type old = load(std::memory_order_acquire);
    do
    {
        auto rc = ::syscall(SYS_futex,
                            static_cast<const void *>(&value),
                            FUTEX_WAIT_PRIVATE,
                            old,
                            /* timeout */ nullptr);
        if ((rc == 0) || (errno == EAGAIN))
        {
            // Spurious wake-up
            std::this_thread::yield();
        }
        else
        {
            return false;
        }
    }
    while (__atomic_load_n(&value, __ATOMIC_ACQUIRE) == old);
    return true;
}

void futex::notify_one() noexcept
{
    fetch_add(1, std::memory_order_acq_rel);
    ::syscall(SYS_futex,
              static_cast<const void *>(&value),
              FUTEX_WAKE_PRIVATE,
              1);
}

void futex::notify_all() noexcept
{
    fetch_add(1, std::memory_order_acq_rel);
    ::syscall(SYS_futex,
              static_cast<const void *>(&value),
              FUTEX_WAKE_PRIVATE,
              ~0);
}

} // namespace detail
} // namespace v1
} // namespace lean
