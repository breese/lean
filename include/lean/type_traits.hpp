#ifndef LEAN_TYPE_TRAITS_HPP
#define LEAN_TYPE_TRAITS_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <type_traits>

namespace lean
{

//-----------------------------------------------------------------------------

template <typename T>
struct is_mutable_reference : std::false_type {};

template <typename T>
struct is_mutable_reference<T&> : std::true_type {};

template <typename T>
struct is_mutable_reference<const T&> : std::false_type {};

template <typename T>
struct is_mutable_reference<T&&> : std::false_type {};

template <typename T>
struct is_mutable_reference<const T&&> : std::false_type {};

//-----------------------------------------------------------------------------
// Perfect forwarding with trivial type decay

template <typename T>
using decay_forward_t = typename std::conditional<
    std::is_trivial<typename std::decay<T>::type>::value && !is_mutable_reference<T>::value,
    typename std::decay<T>::type,
    typename std::add_rvalue_reference<T>::type
    >::type;

//-----------------------------------------------------------------------------
// Workaround for GCC "forming reference to void" error message

template <typename T>
struct is_trivially_move_constructible
    : public std::is_trivially_move_constructible<T> {};

template <>
struct is_trivially_move_constructible<void>
    : public std::false_type {};


} // namespace lean

#endif // LEAN_TYPE_TRAITS_HPP
