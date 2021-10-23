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
// bool_constant [N4389]

using std::integral_constant;

#if __cpp_lib_bool_constant

using std::bool_constant;

#else

template <bool B>
using bool_constant = integral_constant<bool, B>;

#endif

//-----------------------------------------------------------------------------
// Aliases [N3655]

using std::add_const;
using std::add_pointer;
using std::add_rvalue_reference;
using std::conditional;
using std::decay;
using std::enable_if;
using std::is_same;
using std::remove_const;
using std::remove_reference;

#if __cpp_lib_transformation_trait_aliases >= 201304L

using std::add_const_t;
using std::add_pointer_t;
using std::add_rvalue_reference_t;
using std::conditional_t;
using std::decay_t;
using std::enable_if_t;
using std::remove_const_t;
using std::remove_reference_t;

#else

template <typename T>
using add_const_t = typename add_const<T>::type;

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
using remove_const_t = typename remove_const<T>::type;

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

#endif

//-----------------------------------------------------------------------------
// remove_cvref [P0550]

#if __cpp_lib_remove_cvref >= 201711L

using std::remove_cvref;
using std::remove_cvref_t;

#else

template <typename T>
struct remove_cvref : public std::remove_cv<remove_reference_t<T>> {};

template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

#endif

//-----------------------------------------------------------------------------
// type_identity [P0887]

#if __cpp_lib_type_identity >= 201806L

using std::type_identity;
using std::type_identity_t;

#else

template <typename T>
struct type_identity
{
    using type = T;
};

template <typename T>
using type_identity_t = typename type_identity<T>::type;

#endif

//-----------------------------------------------------------------------------
// void_t [N3911]
//
// std::void_t is defined as
//
//   template <typename...> using void_t = void
//
// This does not always work well with SFINAE (see CWG 1558)

namespace detail
{

template <typename...>
struct make_void { using type = void; };

} // namespace detail

template <typename... Ts>
using void_t = typename detail::make_void<Ts...>::type;

} // namespace lean

#endif // LEAN_DETAIL_TYPE_TRAITS_HPP
