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
// add_rvalue_reference

using std::add_rvalue_reference;

#if __cpp_lib_transformation_trait_aliases >= 201304L

using std::add_rvalue_reference_t;

#else

template <typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

#endif

//-----------------------------------------------------------------------------
// decay

using std::decay;

#if __cpp_lib_transformation_trait_aliases >= 201304L

using std::decay_t;

#else

template <typename T>
using decay_t = typename std::decay<T>::type;

#endif

//-----------------------------------------------------------------------------
// enable_if

using std::enable_if;

#if __cpp_lib_transformation_trait_aliases >= 201304L

using std::enable_if_t;

#else

template <bool B, typename T = void>
using enable_if_t = typename std::enable_if<B, T>::type;

#endif

//-----------------------------------------------------------------------------
// remove_reference

using std::remove_reference;

#if __cpp_lib_transformation_trait_aliases >= 201304L

using std::remove_reference_t;

#else

template <typename T>
using remove_reference_t = typename std::remove_reference<T>::type;

#endif

//-----------------------------------------------------------------------------
// is_mutable_reference

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
    std::is_trivial<decay_t<T>>::value && !is_mutable_reference<T>::value,
    decay_t<T>,
    add_rvalue_reference_t<T>
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
