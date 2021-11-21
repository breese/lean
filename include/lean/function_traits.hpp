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

#include <lean/detail/function_traits.hpp>

namespace lean
{

//-----------------------------------------------------------------------------
// function_return

template <typename T, typename = void>
struct function_return;

template <typename T>
struct function_return<T, enable_if_t<std::is_function<T>::value>> {
    using type = typename v1::detail::function_traits<T>::return_type;
};

template <typename T>
using function_return_t = typename function_return<T>::type;

//-----------------------------------------------------------------------------
// function_arguments

template <template <typename...> class, typename, typename = void>
struct function_arguments;

template <template <typename...> class Tuple, typename T>
struct function_arguments<Tuple, T, enable_if_t<std::is_function<T>::value>>
{
    using type = proto_rebind_t<Tuple<>, typename v1::detail::function_traits<T>::arguments>;
};

template <template <typename...> class Tuple, typename T>
using function_arguments_t = typename function_arguments<Tuple, T>::type;

//-----------------------------------------------------------------------------
// is_function_const

template <typename T, typename = void>
struct is_function_const
    : std::false_type
{
};

template <typename T>
struct is_function_const<T, enable_if_t<std::is_function<T>::value>>
    : v1::detail::function_traits<T>::is_const
{
};

template <typename T>
using is_function_const_t = typename is_function_const<T>::type;

//-----------------------------------------------------------------------------
// is_function_volatile

template <typename T, typename = void>
struct is_function_volatile
    : std::false_type
{
};

template <typename T>
struct is_function_volatile<T, enable_if_t<std::is_function<T>::value>>
    : v1::detail::function_traits<T>::is_volatile
{
};

template <typename T>
using is_function_volatile_t = typename is_function_volatile<T>::type;

//-----------------------------------------------------------------------------
// is_function_lvalue_reference

template <typename T, typename = void>
struct is_function_lvalue_reference
    : std::false_type
{
};

template <typename T>
struct is_function_lvalue_reference<T, enable_if_t<std::is_function<T>::value>>
    : v1::detail::function_traits<T>::is_lvalue_reference
{
};

template <typename T>
using is_function_lvalue_reference_t = typename is_function_lvalue_reference<T>::type;

//-----------------------------------------------------------------------------
// is_function_rvalue_reference

template <typename T, typename = void>
struct is_function_rvalue_reference
    : std::false_type
{
};

template <typename T>
struct is_function_rvalue_reference<T, enable_if_t<std::is_function<T>::value>>
    : v1::detail::function_traits<T>::is_rvalue_reference
{
};

template <typename T>
using is_function_rvalue_reference_t = typename is_function_rvalue_reference<T>::type;

//-----------------------------------------------------------------------------
// is_function_reference

template <typename T>
struct is_function_reference
    : bool_constant<is_function_lvalue_reference<T>::value ||
                    is_function_rvalue_reference<T>::value>
{
};

template <typename T>
using is_function_reference_t = typename is_function_reference<T>::type;

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
