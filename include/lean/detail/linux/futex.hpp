#ifndef LEAN_DETAIL_LINUX_FUTEX_HPP
#define LEAN_DETAIL_LINUX_FUTEX_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstdint> // std::uint32_t
#include <atomic>

namespace lean
{
namespace v1
{
namespace detail
{

class futex
{
public:
    using value_type = std::uint32_t;

    bool wait() const noexcept;
    void notify_one() noexcept;
    void notify_all() noexcept;

private:
    value_type load(std::memory_order = std::memory_order_seq_cst) const noexcept;
    value_type fetch_add(value_type, std::memory_order = std::memory_order_seq_cst) noexcept;

private:
    value_type value = 0;
};

} // namespace detail
} // namespace v1
} // namespace lean

#endif // LEAN_DETAIL_LINUX_FUTEX_HPP
