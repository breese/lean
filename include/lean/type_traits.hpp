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

// Workaround for GCC "forming reference to void" error message

template <typename T>
struct is_trivially_move_constructible
    : public std::is_trivially_move_constructible<T> {};

template <>
struct is_trivially_move_constructible<void>
    : public std::false_type {};


} // namespace lean

#endif // LEAN_TYPE_TRAITS_HPP
