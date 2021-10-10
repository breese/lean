#ifndef LEAN_DETAIL_TYPE_TRAITS_HPP
#define LEAN_DETAIL_TYPE_TRAITS_HPP

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
// Aliases [N3655]

using std::add_pointer;
using std::add_rvalue_reference;
using std::conditional;
using std::decay;
using std::enable_if;
using std::is_same;
using std::remove_reference;

#if __cpp_lib_transformation_trait_aliases >= 201304L

using std::add_pointer_t;
using std::add_rvalue_reference_t;
using std::conditional_t;
using std::decay_t;
using std::enable_if_t;
using std::remove_reference_t;

#else

template <typename T>
using add_pointer_t = typename add_pointer<T>::type;

template <typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

template <typename T>
using decay_t = typename std::decay<T>::type;

template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

#endif

//-----------------------------------------------------------------------------
// void_t

#if __cpp_lib_void_t >= 201411L

using std::void_t;

#else

template <typename...>
using void_t = void;

#endif

//-----------------------------------------------------------------------------
// Extension: Parameter pack

template <typename...>
struct pack;

} // namespace lean

#endif // LEAN_DETAIL_TYPE_TRAITS_HPP
