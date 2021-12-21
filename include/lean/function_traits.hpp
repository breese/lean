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
#include <lean/detail/type_traits.hpp>
#include <lean/detail/template_traits.hpp>

namespace lean
{

//-----------------------------------------------------------------------------
// function_type

namespace impl {

// Function object
//
// Argument types disambiguates overloaded or template call operators.

template <typename, typename, typename = void>
struct function_type_invocable;

template <typename T, typename, typename A, typename = void>
struct function_type
    : function_type_invocable<T, A>
{
};

template <typename T, typename DecayT, typename A>
struct function_type<T,
                     DecayT,
                     A,
                     enable_if_t<std::is_function<DecayT>::value>>
{
    using type = DecayT;
};


// Function pointer

template <typename T, typename DecayT, typename A>
struct function_type<T, DecayT*, A>
    : function_type<T, DecayT, A>
{
};

// Member function pointer

template <typename T, typename DecayT, typename C, typename A>
struct function_type<T, DecayT C::*, A>
{
    using type = DecayT;
};

// Function object

template <typename, typename, typename, typename = void>
struct function_type_operator_near;

template <typename T, typename R, typename... Args>
struct function_type_operator_near<T,
                                   R,
                                   prototype<Args...>,
                                   void_t<decltype(static_cast<R (T::*)(Args...) const>(&T::operator()))>>
{
    using type = typename function_type<T,
                                        decltype(static_cast<R (T::*)(Args...) const>(&T::operator())),
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator_near<T&,
                                   R,
                                   prototype<Args...>,
                                   void_t<decltype(static_cast<R (T::*)(Args...) &>(&T::operator()))>>
{
    using type = typename function_type<T&,
                                        decltype(static_cast<R (T::*)(Args...) &>(&T::operator())),
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator_near<T&&,
                                   R,
                                   prototype<Args...>,
                                   void_t<decltype(static_cast<R (T::*)(Args...) &&>(&T::operator()))>>
{
    using type = typename function_type<T&&,
                                        decltype(static_cast<R (T::*)(Args...) &&>(&T::operator())),
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename A, typename = void>
struct function_type_operator_noexcept_near
    : function_type_operator_near<T, R, A>
{
};

#if __cpp_noexcept_function_type >= 201510L

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept_near<T,
                                            R,
                                            prototype<Args...>,
                                            void_t<decltype(static_cast<R (T::*)(Args...) const noexcept>(&T::operator()))>>
{
    using callable_type = conditional_t<noexcept(std::declval<T>().operator()(std::declval<Args>()...)),
                                        decltype(static_cast<R (T::*)(Args...) const noexcept>(&T::operator())),
                                        decltype(static_cast<R (T::*)(Args...) const>(&T::operator()))>;
    using type = typename function_type<T,
                                        callable_type,
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept_near<T&,
                                            R,
                                            prototype<Args...>,
                                            void_t<decltype(static_cast<R (T::*)(Args...) & noexcept>(&T::operator()))>>
{
    using callable_type = conditional_t<noexcept(std::declval<T&>().operator()(std::declval<Args>()...)),
                                        decltype(static_cast<R (T::*)(Args...) & noexcept>(&T::operator())),
                                        decltype(static_cast<R (T::*)(Args...) &>(&T::operator()))>;
    using type = typename function_type<T&,
                                        callable_type,
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept_near<T&&,
                                            R,
                                            prototype<Args...>,
                                            void_t<decltype(static_cast<R (T::*)(Args...) && noexcept>(&T::operator()))>>
{
    using callable_type = conditional_t<noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)),
                                        decltype(static_cast<R (T::*)(Args...) && noexcept>(&T::operator())),
                                        decltype(static_cast<R (T::*)(Args...) &&>(&T::operator()))>;
    using type = typename function_type<T&&,
                                        callable_type,
                                        prototype<Args...>>::type;
};

#endif

template <typename T, typename R, typename A, typename = void>
struct function_type_operator
    : function_type_operator_noexcept_near<T, R, A>
{
};

// Exact match.
//
// Uses "is_same<T, cv-qual remove_cv_t<T>>" to avoid greedy matching, where
// "const T" matches both "const A" and "const volatile A" leading to ambiguous
// template matching.

template <typename T, typename R, typename... Args>
struct function_type_operator<T,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<std::is_same<T, remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...)>(&T::operator()))>>
{
    using type = typename function_type<T,
                                        decltype(static_cast<R (T::*)(Args...)>(&T::operator())),
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<std::is_same<T, const remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const>(&T::operator()))>>
{
    using type = typename function_type<T,
                                        decltype(static_cast<R (T::*)(Args...) const>(&T::operator())),
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<std::is_same<T, const remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const &>(&T::operator()))>>
{
    using type = typename function_type<T&,
                                        decltype(static_cast<R (T::*)(Args...) const &>(&T::operator())),
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T&&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<std::is_same<T, const remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const &&>(&T::operator()))>>
{
    using type = typename function_type<T&&,
                                        decltype(static_cast<R (T::*)(Args...) const &&>(&T::operator())),
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<std::is_same<T, const volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const volatile>(&T::operator()))>>
{
    using type = typename function_type<T,
                                        decltype(static_cast<R (T::*)(Args...) const volatile>(&T::operator())),
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<std::is_same<T, const volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const volatile &>(&T::operator()))>>
{
    using type = typename function_type<T&,
                                        decltype(static_cast<R (T::*)(Args...) const volatile &>(&T::operator())),
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T&&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<std::is_same<T, const volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const volatile &&>(&T::operator()))>>
{
    using type = typename function_type<T&&,
                                        decltype(static_cast<R (T::*)(Args...) const volatile &&>(&T::operator())),
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<std::is_same<T, volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) volatile>(&T::operator()))>>
{
    using type = typename function_type<T,
                                        decltype(static_cast<R (T::*)(Args...) volatile>(&T::operator())),
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<std::is_same<T, volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) volatile &>(&T::operator()))>>
{
    using type = typename function_type<T&,
                                        decltype(static_cast<R (T::*)(Args...) volatile &>(&T::operator())),
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T&&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<std::is_same<T, volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) volatile &&>(&T::operator()))>>
{
    using type = typename function_type<T&&,
                                        decltype(static_cast<R (T::*)(Args...) volatile &&>(&T::operator())),
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename A, typename = void>
struct function_type_operator_noexcept
    : function_type_operator<T, R, A>
{
};

#if __cpp_noexcept_function_type >= 201510L

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<std::is_same<T, remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) noexcept>(&T::operator()))>>
{
    using callable_type = conditional_t<noexcept(std::declval<T>().operator()(std::declval<Args>()...)),
                                        decltype(static_cast<R (T::*)(Args...) noexcept>(&T::operator())),
                                        decltype(static_cast<R (T::*)(Args...)>(&T::operator()))>;
    using type = typename function_type<T,
                                        callable_type,
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<std::is_same<T, const remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const noexcept>(&T::operator()))>>
{
    using callable_type = conditional_t<noexcept(std::declval<T>().operator()(std::declval<Args>()...)),
                                        decltype(static_cast<R (T::*)(Args...) const noexcept>(&T::operator())),
                                        decltype(static_cast<R (T::*)(Args...) const>(&T::operator()))>;
    using type = typename function_type<T,
                                        callable_type,
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<std::is_same<T, const remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const & noexcept>(&T::operator()))>>
{
    using callable_type = conditional_t<noexcept(std::declval<T&>().operator()(std::declval<Args>()...)),
                                        decltype(static_cast<R (T::*)(Args...) const & noexcept>(&T::operator())),
                                        decltype(static_cast<R (T::*)(Args...) const &>(&T::operator()))>;
    using type = typename function_type<T&,
                                        callable_type,
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T&&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<std::is_same<T, const remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const && noexcept>(&T::operator()))>>
{
    using callable_type = conditional_t<noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)),
                                        decltype(static_cast<R (T::*)(Args...) const && noexcept>(&T::operator())),
                                        decltype(static_cast<R (T::*)(Args...) const &&>(&T::operator()))>;
    using type = typename function_type<T&&,
                                        callable_type,
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<std::is_same<T, volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) volatile noexcept>(&T::operator()))>>
{
    using callable_type = conditional_t<noexcept(std::declval<T>().operator()(std::declval<Args>()...)),
                                        decltype(static_cast<R (T::*)(Args...) volatile noexcept>(&T::operator())),
                                        decltype(static_cast<R (T::*)(Args...) volatile>(&T::operator()))>;
    using type = typename function_type<T,
                                        callable_type,
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<std::is_same<T, volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) volatile & noexcept>(&T::operator()))>>
{
    using callable_type = conditional_t<noexcept(std::declval<T&>().operator()(std::declval<Args>()...)),
                                        decltype(static_cast<R (T::*)(Args...) volatile & noexcept>(&T::operator())),
                                        decltype(static_cast<R (T::*)(Args...) volatile &>(&T::operator()))>;
    using type = typename function_type<T&,
                                        callable_type,
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T&&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<std::is_same<T, volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) volatile && noexcept>(&T::operator()))>>
{
    using callable_type = conditional_t<noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)),
                                        decltype(static_cast<R (T::*)(Args...) volatile && noexcept>(&T::operator())),
                                        decltype(static_cast<R (T::*)(Args...) volatile &&>(&T::operator()))>;
    using type = typename function_type<T&&,
                                        callable_type,
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<std::is_same<T, const volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const volatile noexcept>(&T::operator()))>>
{
    using callable_type = conditional_t<noexcept(std::declval<T>().operator()(std::declval<Args>()...)),
                                        decltype(static_cast<R (T::*)(Args...) const volatile noexcept>(&T::operator())),
                                        decltype(static_cast<R (T::*)(Args...) const volatile>(&T::operator()))>;
    using type = typename function_type<T,
                                        callable_type,
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<std::is_same<T, const volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const volatile & noexcept>(&T::operator()))>>
{
    using callable_type = conditional_t<noexcept(std::declval<T&>().operator()(std::declval<Args>()...)),
                                        decltype(static_cast<R (T::*)(Args...) const volatile & noexcept>(&T::operator())),
                                        decltype(static_cast<R (T::*)(Args...) const volatile &>(&T::operator()))>;
    using type = typename function_type<T&,
                                        callable_type,
                                        prototype<Args...>>::type;
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T&&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<std::is_same<T, const volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const volatile && noexcept>(&T::operator()))>>
{
    using callable_type = conditional_t<noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)),
                                        decltype(static_cast<R (T::*)(Args...) const volatile && noexcept>(&T::operator())),
                                        decltype(static_cast<R (T::*)(Args...) const volatile &&>(&T::operator()))>;
    using type = typename function_type<T&&,
                                        callable_type,
                                        prototype<Args...>>::type;
};

#endif

template <typename T, typename... Args>
struct function_type_invocable<T,
                               prototype<Args...>,
                               void_t<decltype(std::declval<T>().operator()(std::declval<Args>()...))>>
    : function_type_operator_noexcept<T,
                                      decltype(std::declval<T>().operator()(std::declval<Args>()...)),
                                      prototype<Args...>>
{
};

} // namespace impl

template <typename T, typename... Args>
struct function_type
    : impl::function_type<T, remove_cvref_t<T>, prototype<Args...>>
{
};

template <typename T, typename... Args>
using function_type_t = typename function_type<T, Args...>::type;

//-----------------------------------------------------------------------------
// function_return

template <typename, typename = void>
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
    using type = template_rebind_t<typename v1::detail::function_traits<T>::arguments, Tuple>;
};

template <template <typename...> class Tuple, typename T>
using function_arguments_t = typename function_arguments<Tuple, T>::type;

//-----------------------------------------------------------------------------
// function_rebind

template <typename, typename, typename, typename = void>
struct function_rebind;

template <typename T, typename R, template <typename...> class Tuple, typename... Types>
struct function_rebind<T,
                       R,
                       Tuple<Types...>,
                       enable_if_t<std::is_function<T>::value>>
{
    using type = typename v1::detail::function_traits<T>::template rebind<R, Types...>;
};

template <typename T, typename R, typename Args>
using function_rebind_t = typename function_rebind<T, R, Args>::type;

//-----------------------------------------------------------------------------
// is_function

using std::is_function;

//-----------------------------------------------------------------------------
// is_function_const

template <typename T, typename = void>
struct is_function_const
    : std::false_type
{
};

template <typename T>
struct is_function_const<T, enable_if_t<is_function<T>::value>>
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
struct is_function_volatile<T, enable_if_t<is_function<T>::value>>
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
struct is_function_lvalue_reference<T, enable_if_t<is_function<T>::value>>
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
struct is_function_rvalue_reference<T, enable_if_t<is_function<T>::value>>
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
// is_function_ellipsis

template <typename T, typename = void>
struct is_function_ellipsis
    : std::false_type
{
};

template <typename T>
struct is_function_ellipsis<T, enable_if_t<is_function<T>::value>>
    : v1::detail::function_traits<T>::is_ellipsis
{
};

template <typename T>
using is_function_ellipsis_t = typename is_function_ellipsis<T>::type;

//-----------------------------------------------------------------------------
// add_function_const
//
// Adds const qualifier to function type.
//
//   T                       | add_function_const_t<T>
// --------------------------+----------------------------
//  bool ()                  | bool() const
//  bool () const            | bool() const
//  bool () &                | bool() const &
//  bool () noexcept         | bool() const noexcept
//  bool () & noexcept       | bool() const & noexcept

template <typename T, typename = void>
struct add_function_const
{
    using type = T;
};

template <typename T>
struct add_function_const<T, enable_if_t<is_function<T>::value>>
{
    using type = typename v1::detail::function_traits<T>::add_const;
};

template <typename T>
using add_function_const_t = typename add_function_const<T>::type;

//-----------------------------------------------------------------------------
// add_function_volatile

template <typename T, typename = void>
struct add_function_volatile
{
    using type = T;
};

template <typename T>
struct add_function_volatile<T, enable_if_t<is_function<T>::value>>
{
    using type = typename v1::detail::function_traits<T>::add_volatile;
};

template <typename T>
using add_function_volatile_t = typename add_function_volatile<T>::type;

//-----------------------------------------------------------------------------
// add_function_cv

template <typename T, typename = void>
struct add_function_cv
{
    using type = T;
};

template <typename T>
struct add_function_cv<T, enable_if_t<is_function<T>::value>>
    : add_function_volatile<add_function_const_t<T>>
{
};

template <typename T>
using add_function_cv_t = typename add_function_cv<T>::type;

//-----------------------------------------------------------------------------
// add_function_lvalue_reference

template <typename T, typename = void>
struct add_function_lvalue_reference
{
    using type = T;
};

template <typename T>
struct add_function_lvalue_reference<T, enable_if_t<is_function<T>::value>>
{
    using type = typename v1::detail::function_traits<T>::add_lvalue_reference;
};

template <typename T>
using add_function_lvalue_reference_t = typename add_function_lvalue_reference<T>::type;

//-----------------------------------------------------------------------------
// add_function_rvalue_reference

template <typename T, typename = void>
struct add_function_rvalue_reference
{
    using type = T;
};

template <typename T>
struct add_function_rvalue_reference<T, enable_if_t<is_function<T>::value>>
{
    using type = typename v1::detail::function_traits<T>::add_rvalue_reference;
};

template <typename T>
using add_function_rvalue_reference_t = typename add_function_rvalue_reference<T>::type;

//-----------------------------------------------------------------------------
// add_function_ellipsis

template <typename T, typename = void>
struct add_function_ellipsis
{
    using type = T;
};

template <typename T>
struct add_function_ellipsis<T, enable_if_t<is_function<T>::value>>
{
    using type = typename v1::detail::function_traits<T>::add_ellipsis;
};

template <typename T>
using add_function_ellipsis_t = typename add_function_ellipsis<T>::type;

//-----------------------------------------------------------------------------
// remove_function_const
//
// Removes const qualifier from function type.
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
struct remove_function_const<T, enable_if_t<is_function<T>::value>>
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
struct remove_function_volatile<T, enable_if_t<is_function<T>::value>>
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
struct remove_function_reference<T, enable_if_t<is_function<T>::value>>
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

//-----------------------------------------------------------------------------
// remove_function_ellipsis

template <typename T, typename = void>
struct remove_function_ellipsis
{
    using type = T;
};

template <typename T>
struct remove_function_ellipsis<T, enable_if_t<is_function<T>::value>>
{
    using type = typename v1::detail::function_traits<T>::remove_ellipsis;
};

template <typename T>
using remove_function_ellipsis_t = typename remove_function_ellipsis<T>::type;


} // namespace lean

#endif // LEAN_FUNCTION_TRAITS_HPP
