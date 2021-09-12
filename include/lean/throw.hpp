#ifndef LEAN_THROW_HPP
#define LEAN_THROW_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <lean/detail/config.hpp>
#include <lean/type_traits.hpp>
#include <lean/utility.hpp>

namespace lean
{
namespace v1
{

template <typename E>
struct throw_abi
{
private:
    // Only accessible from throw_traits
    template <typename, typename>
    friend struct throw_traits;

    // Throws exception
    template <typename... Args>
    [[noreturn]] LEAN_ATTRIBUTE_NOINLINE
    static void invoke(Args... args)
    {
        throw E{args...};
    }
};

//! @brief Override throw invocation.
//!
//! Decays trivial types so they can be passed in registers.
//!
//! Decays array references to pointers so they can share implementation
//! independent on array size.
//!
//! Specialize this template to change the default behavior.
//!
//! For example, std::logic_error exceptions can be banned by creating an
//! undefined specialization to provoke a compiler error when used.
//!
//!   namespace lean { namespace v1 {
//!
//!   template <typename E>
//!   struct throw_traits<E, std::enable_if_t<std::is_base_of_v<std::logic_error, E>>>;
//!
//!   }}

template <typename E, typename = void>
struct throw_traits
{
    using result_type = void;

    template <typename... Args>
    [[noreturn]]
    static void invoke(Args&&... args)
    {
        throw_abi<E>::template invoke<decay_forward_t<Args>...>(decay_forward<Args>(args)...);
    }
};

//! @brief Throws exception.
//!
//! Prevents inlining of exception construction at the call-site to reduce
//! binary size.
//!
//! Replace
//!
//!   throw std::runtime_error("warp core failure");
//!
//! with
//!
//!   throw_exception<std::runtime_error>("warp core failure");

LEAN_WARNING_SCOPE_BEGIN
LEAN_WARNING_IGNORE_NORETURN

template <typename E, typename... Args>
auto throw_exception(Args&&... args) -> typename throw_traits<E>::result_type
{
    return throw_traits<E>::invoke(decay_forward<Args>(args)...);
}

LEAN_WARNING_SCOPE_END

} // namespace v1

using v1::throw_traits;
using v1::throw_exception;

} // namespace lean

#endif // LEAN_THROW_HPP
