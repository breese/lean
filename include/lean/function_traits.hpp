#ifndef LEAN_FUNCTION_TRAITS_HPP
#define LEAN_FUNCTION_TRAITS_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <lean/detail/type_traits.hpp>
#include <lean/detail/function_traits.hpp>

namespace lean
{

//-----------------------------------------------------------------------------
// remove_function_const
//
// Removes const from function type.
//
//   T                       | remove_function_const_t<T>
// --------------------------+----------------------------
//  bool ()                  | bool()
//  bool () const            | bool()
//  bool () const &          | bool() &
//  bool () const noexcept   | bool() noexcept
//  bool () const & noexcept | bool() & noexcept

template <typename T, typename = void>
struct remove_function_const
{
    using type = T;
};

template <typename T>
struct remove_function_const<T, enable_if_t<std::is_function<T>::value>>
{
    using type = typename v1::detail::function_traits<T>::remove_const;
};

template <typename T>
using remove_function_const_t = typename remove_function_const<T>::type;


//-----------------------------------------------------------------------------
// remove_function_volatile

template <typename T, typename = void>
struct remove_function_volatile
{
    using type = T;
};

template <typename T>
struct remove_function_volatile<T, enable_if_t<std::is_function<T>::value>>
{
    using type = typename v1::detail::function_traits<T>::remove_volatile;
};

template <typename T>
using remove_function_volatile_t = typename remove_function_volatile<T>::type;

//-----------------------------------------------------------------------------
// remove_function_cv

template <typename T>
struct remove_function_cv
    : remove_function_volatile<remove_function_const_t<T>>
{
};

template <typename T>
using remove_function_cv_t = typename remove_function_cv<T>::type;

//-----------------------------------------------------------------------------
// remove_function_reference

template <typename T, typename = void>
struct remove_function_reference
{
    using type = T;
};

template <typename T>
struct remove_function_reference<T, enable_if_t<std::is_function<T>::value>>
{
    using type = typename v1::detail::function_traits<T>::remove_reference;
};

template <typename T>
using remove_function_reference_t = typename remove_function_reference<T>::type;

//-----------------------------------------------------------------------------
// remove_function_cvref

template <typename T>
struct remove_function_cvref
    : remove_function_cv<remove_function_reference_t<T>>
{
};

template <typename T>
using remove_function_cvref_t = typename remove_function_cvref<T>::type;

} // namespace lean

#endif // LEAN_FUNCTION_TRAITS_HPP
