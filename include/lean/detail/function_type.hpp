#ifndef LEAN_DETAIL_FUNCTION_TYPE_HPP
#define LEAN_DETAIL_FUNCTION_TYPE_HPP

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

namespace lean
{
namespace v1
{
namespace detail
{

//-----------------------------------------------------------------------------

template <typename, typename = void>
struct function_type_basis;

template <typename T>
using function_type_basis_t = typename function_type_basis<T>::type;

// Function type

template <typename T>
struct function_type_basis<T, enable_if_t<is_function<T>::value>>
{
    using type = T;
};

// Function pointer

template <typename T>
struct function_type_basis<T*, enable_if_t<is_function<T>::value>>
{
    using type = T;
};

// Function reference

template <typename T>
struct function_type_basis<T&, enable_if_t<is_function<T>::value>>
{
    using type = T;
};

template <typename T>
struct function_type_basis<T&&, enable_if_t<is_function<T>::value>>
{
    using type = T;
};

// Member function pointer

template <typename T, typename C>
struct function_type_basis<T C::*, enable_if_t<is_function<T>::value>>
{
    using type = T;
};

//-----------------------------------------------------------------------------
// Function object
//
// Argument types disambiguates overloaded or template call operators.

template <typename T, typename R, typename A, typename = void>
struct function_object_type_r
{
};

template <typename T, typename R, typename A, typename = void>
struct function_object_type_noexcept_r
    : function_object_type_r<T, R, A>
{
};

template <typename T, typename A, typename = void>
struct function_object_type_lvalue
{
};

template <typename T, typename A, typename = void>
struct function_object_type
    : function_object_type_lvalue<T, A>
{
};

template <typename T, typename... Args>
struct function_object_type_lvalue<T,
                                   prototype<Args...>,
                                   void_t<enable_if_t<!std::is_reference<T>::value>,
                                          decltype(std::declval<T&>()(std::declval<Args>()...))>>
    : function_object_type_noexcept_r<T&,
                                      decltype(std::declval<T&>()(std::declval<Args>()...)),
                                      prototype<Args...>>
{
};

template <typename T, typename... Args>
struct function_object_type<T,
                            prototype<Args...>,
                            void_t<typename function_object_type_noexcept_r<T,
                                                                            decltype(std::declval<T>()(std::declval<Args>()...)),
                                                                            prototype<Args...>>::type>>
    : function_object_type_noexcept_r<T,
                                      decltype(std::declval<T>()(std::declval<Args>()...)),
                                      prototype<Args...>>
{
};

// Uses "is_same<T, cv-qual remove_cv_t<T>>" to avoid greedy matching, where
// "const T" matches both "const A" and "const volatile A" leading to ambiguous
// template matching.

template <typename T, typename R, typename... Args>
struct function_object_type_r<T,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...)>(&T::operator()))>>
{
    using type = R(Args...);
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...)>(&T::operator()))>>
{
    using type = R(Args..., ...);
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) &>(&T::operator()))>>
{
    using type = R(Args...) &;
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) &>(&T::operator()))>>
{
    using type = R(Args..., ...) &;
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T&&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) &&>(&T::operator()))>>
{
    using type = R(Args...) &&;
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T&&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) &&>(&T::operator()))>>
{
    using type = R(Args..., ...) &&;
};

// const

template <typename T, typename R, typename... Args>
struct function_object_type_r<T,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const>(&T::operator()))>>
{
    using type = R(Args...) const;
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) const>(&T::operator()))>>
{
    using type = R (Args..., ...) const;
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const &>(&T::operator()))>>
{
    using type = R (Args...) const &;
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) const &>(&T::operator()))>>
{
    using type = R (Args..., ...) const &;
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T&&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const &&>(&T::operator()))>>
{
    using type = R (Args...) const &&;
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T&&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) const &&>(&T::operator()))>>
{
    using type = R (Args..., ...) const &&;
};

// volatile

template <typename T, typename R, typename... Args>
struct function_object_type_r<T,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) volatile>(&T::operator()))>>
{
    using type = R (Args...) volatile;
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) volatile>(&T::operator()))>>
{
    using type = R (Args..., ...) volatile;
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) volatile &>(&T::operator()))>>
{
    using type = R (Args...) volatile &;
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) volatile &>(&T::operator()))>>
{
    using type = R (Args..., ...) volatile &;
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T&&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) volatile &&>(&T::operator()))>>
{
    using type = R (Args...) volatile &&;
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T&&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) volatile &&>(&T::operator()))>>
{
    using type = R (Args..., ...) volatile &&;
};

// const volatile

template <typename T, typename R, typename... Args>
struct function_object_type_r<T,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const volatile>(&T::operator()))>>
{
    using type = R (Args...) const volatile;
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) const volatile>(&T::operator()))>>
{
    using type = R (Args..., ...) const volatile;
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const volatile &>(&T::operator()))>>
{
    using type = R (Args...) const volatile &;
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) const volatile &>(&T::operator()))>>
{
    using type = R (Args..., ...) const volatile &;
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T&&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const volatile &&>(&T::operator()))>>
{
    using type = R (Args...) const volatile &&;
};

template <typename T, typename R, typename... Args>
struct function_object_type_r<T&&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) const volatile &&>(&T::operator()))>>
{
    using type = R (Args..., ...) const volatile &&;
};

#if __cpp_noexcept_function_type >= 201510L

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) noexcept>(&T::operator()))>>
{
    using type = R (Args...) noexcept(noexcept(std::declval<T>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) noexcept(noexcept(std::declval<T>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) & noexcept>(&T::operator()))>>
{
    using type = R (Args...) & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) & noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T&&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) && noexcept>(&T::operator()))>>
{
    using type = R (Args...) && noexcept(noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T&&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) && noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) && noexcept(noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const noexcept>(&T::operator()))>>
{
    using type = R (Args...) const noexcept(noexcept(std::declval<T>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) const noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) const noexcept(noexcept(std::declval<T>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const & noexcept>(&T::operator()))>>
{
    using type = R (Args...) const & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) const & noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) const & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T&&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const && noexcept>(&T::operator()))>>
{
    using type = R (Args...) const && noexcept(noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T&&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) const && noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) const && noexcept(noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) volatile noexcept>(&T::operator()))>>
{
    using type = R (Args...) volatile noexcept(noexcept(std::declval<T>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) volatile noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) volatile noexcept(noexcept(std::declval<T>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) volatile & noexcept>(&T::operator()))>>
{
    using type = R (Args...) volatile & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) volatile & noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) volatile & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T&&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) volatile && noexcept>(&T::operator()))>>
{
    using type = R (Args...) volatile && noexcept(noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T&&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) volatile && noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) volatile && noexcept(noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const volatile noexcept>(&T::operator()))>>
{
    using type = R (Args...) const volatile noexcept(noexcept(std::declval<T>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) const volatile noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) const volatile noexcept(noexcept(std::declval<T>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const volatile & noexcept>(&T::operator()))>>
{
    using type = R (Args...) const volatile & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) const volatile & noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) const volatile & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T&&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const volatile && noexcept>(&T::operator()))>>
{
    using type = R (Args...) const volatile && noexcept(noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_object_type_noexcept_r<T&&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) const volatile && noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) const volatile && noexcept(noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)));
};

#endif

// Resolves cv-qualified overloaded call operators

template <typename T, typename F1, typename F2, typename F3, typename F4>
struct function_object_select_cvqual
{
    using type = F1;
};

template <typename T, typename F1, typename F2, typename F3, typename F4>
struct function_object_select_cvqual<const T, F1, F2, F3, F4>
{
    using type = F2;
};

template <typename T, typename F1, typename F2, typename F3, typename F4>
struct function_object_select_cvqual<volatile T, F1, F2, F3, F4>
{
    using type = F3;
};

template <typename T, typename F1, typename F2, typename F3, typename F4>
struct function_object_select_cvqual<const volatile T, F1, F2, F3, F4>
{
    using type = F4;
};

template <typename T, typename F2, typename F3, typename F4>
struct function_object_select_cvqual<T, void, F2, F3, F4>
{
};

template <typename T, typename F2, typename F3, typename F4>
struct function_object_select_cvqual<const T, void, F2, F3, F4>
{
    using type = F2;
};

template <typename T, typename F2, typename F3, typename F4>
struct function_object_select_cvqual<volatile T, void, F2, F3, F4>
{
    using type = F3;
};

template <typename T, typename F2, typename F3, typename F4>
struct function_object_select_cvqual<const volatile T, void, F2, F3, F4>
{
    using type = F4;
};

template <typename T, typename F1, typename F3, typename F4>
struct function_object_select_cvqual<T, F1, void, F3, F4>
{
    using type = F1;
};

template <typename T, typename F1, typename F3, typename F4>
struct function_object_select_cvqual<const T, F1, void, F3, F4>
{
    using type = F4;
};

template <typename T, typename F1, typename F3, typename F4>
struct function_object_select_cvqual<volatile T, F1, void, F3, F4>
{
    using type = F3;
};

template <typename T, typename F1, typename F3, typename F4>
struct function_object_select_cvqual<const volatile T, F1, void, F3, F4>
{
    using type = F4;
};

template <typename T, typename F3, typename F4>
struct function_object_select_cvqual<T, void, void, F3, F4>
{
    using type = F3;
};

template <typename T, typename F3, typename F4>
struct function_object_select_cvqual<const T, void, void, F3, F4>
{
    using type = F4;
};

template <typename T, typename F3, typename F4>
struct function_object_select_cvqual<volatile T, void, void, F3, F4>
{
    using type = F3;
};

template <typename T, typename F3, typename F4>
struct function_object_select_cvqual<const volatile T, void, void, F3, F4>
{
    using type = F4;
};

template <typename T, typename F1, typename F2, typename F4>
struct function_object_select_cvqual<T, F1, F2, void, F4>
{
    using type = F1;
};

template <typename T, typename F1, typename F2, typename F4>
struct function_object_select_cvqual<const T, F1, F2, void, F4>
{
    using type = F2;
};

template <typename T, typename F1, typename F2, typename F4>
struct function_object_select_cvqual<volatile T, F1, F2, void, F4>
{
    using type = F4;
};

template <typename T, typename F1, typename F2, typename F4>
struct function_object_select_cvqual<const volatile T, F1, F2, void, F4>
{
    using type = F4;
};

template <typename T, typename F2, typename F4>
struct function_object_select_cvqual<T, void, F2, void, F4>
{
    using type = F2;
};

template <typename T, typename F2, typename F4>
struct function_object_select_cvqual<const T, void, F2, void, F4>
{
    using type = F2;
};

template <typename T, typename F2, typename F4>
struct function_object_select_cvqual<volatile T, void, F2, void, F4>
{
    using type = F4;
};

template <typename T, typename F2, typename F4>
struct function_object_select_cvqual<const volatile T, void, F2, void, F4>
{
    using type = F4;
};

template <typename T, typename F1, typename F4>
struct function_object_select_cvqual<T, F1, void, void, F4>
{
    using type = F1;
};

template <typename T, typename F1, typename F4>
struct function_object_select_cvqual<const T, F1, void, void, F4>
{
    using type = F4;
};

template <typename T, typename F1, typename F4>
struct function_object_select_cvqual<volatile T, F1, void, void, F4>
{
    using type = F4;
};

template <typename T, typename F1, typename F4>
struct function_object_select_cvqual<const volatile T, F1, void, void, F4>
{
    using type = F4;
};

template <typename T, typename F4>
struct function_object_select_cvqual<T, void, void, void, F4>
{
    using type = F4;
};

template <typename T, typename F4>
struct function_object_select_cvqual<const T, void, void, void, F4>
{
    using type = F4;
};

template <typename T, typename F4>
struct function_object_select_cvqual<volatile T, void, void, void, F4>
{
    using type = F4;
};

template <typename T, typename F4>
struct function_object_select_cvqual<const volatile T, void, void, void, F4>
{
    using type = F4;
};

template <typename T, typename F1, typename F2, typename F3>
struct function_object_select_cvqual<T, F1, F2, F3, void>
{
    using type = F1;
};

template <typename T, typename F1, typename F2, typename F3>
struct function_object_select_cvqual<const T, F1, F2, F3, void>
{
    using type = F2;
};

template <typename T, typename F1, typename F2, typename F3>
struct function_object_select_cvqual<volatile T, F1, F2, F3, void>
{
    using type = F3;
};

template <typename T, typename F1, typename F2, typename F3>
struct function_object_select_cvqual<const volatile T, F1, F2, F3, void>
{
};

template <typename T, typename F2, typename F3>
struct function_object_select_cvqual<T, void, F2, F3, void>
{
};

template <typename T, typename F2, typename F3>
struct function_object_select_cvqual<const T, void, F2, F3, void>
{
    using type = F2;
};

template <typename T, typename F2, typename F3>
struct function_object_select_cvqual<volatile T, void, F2, F3, void>
{
    using type = F3;
};

template <typename T, typename F2, typename F3>
struct function_object_select_cvqual<const volatile T, void, F2, F3, void>
{
};

template <typename T, typename F1, typename F3>
struct function_object_select_cvqual<T, F1, void, F3, void>
{
    using type = F1;
};

template <typename T, typename F1, typename F3>
struct function_object_select_cvqual<const T, F1, void, F3, void>
{
};

template <typename T, typename F1, typename F3>
struct function_object_select_cvqual<volatile T, F1, void, F3, void>
{
    using type = F3;
};

template <typename T, typename F1, typename F3>
struct function_object_select_cvqual<const volatile T, F1, void, F3, void>
{
};

template <typename T, typename F3>
struct function_object_select_cvqual<T, void, void, F3, void>
{
    using type = F3;
};

template <typename T, typename F3>
struct function_object_select_cvqual<const T, void, void, F3, void>
{
};

template <typename T, typename F3>
struct function_object_select_cvqual<volatile T, void, void, F3, void>
{
    using type = F3;
};

template <typename T, typename F3>
struct function_object_select_cvqual<const volatile T, void, void, F3, void>
{
};

template <typename T, typename F1, typename F2>
struct function_object_select_cvqual<T, F1, F2, void, void>
{
    using type = F1;
};

template <typename T, typename F1, typename F2>
struct function_object_select_cvqual<const T, F1, F2, void, void>
{
    using type = F2;
};

template <typename T, typename F1, typename F2>
struct function_object_select_cvqual<volatile T, F1, F2, void, void>
{
};

template <typename T, typename F1, typename F2>
struct function_object_select_cvqual<const volatile T, F1, F2, void, void>
{
};

template <typename T, typename F2>
struct function_object_select_cvqual<T, void, F2, void, void>
{
    using type = F2;
};

template <typename T, typename F2>
struct function_object_select_cvqual<const T, void, F2, void, void>
{
    using type = F2;
};

template <typename T, typename F2>
struct function_object_select_cvqual<volatile T, void, F2, void, void>
{
};

template <typename T, typename F2>
struct function_object_select_cvqual<const volatile T, void, F2, void, void>
{
};

template <typename T, typename F1>
struct function_object_select_cvqual<T, F1, void, void, void>
{
    using type = F1;
};

template <typename T, typename F1>
struct function_object_select_cvqual<const T, F1, void, void, void>
{
};

template <typename T, typename F1>
struct function_object_select_cvqual<volatile T, F1, void, void, void>
{
};

template <typename T, typename F1>
struct function_object_select_cvqual<const volatile T, F1, void, void, void>
{
};

template <typename T>
struct function_object_select_cvqual<T, void, void, void, void>
{
};

template <typename T>
struct function_object_select_cvqual<const T, void, void, void, void>
{
};

template <typename T>
struct function_object_select_cvqual<volatile T, void, void, void, void>
{
};

template <typename T>
struct function_object_select_cvqual<const volatile T, void, void, void, void>
{
};

template <typename T, typename A, typename = void>
struct function_object_call
    : function_object_select_cvqual<T,
                                    type_eval_t<function_object_type<remove_cv_t<T>, A>>,
                                    type_eval_t<function_object_type<const remove_cv_t<T>, A>>,
                                    type_eval_t<function_object_type<volatile remove_cv_t<T>, A>>,
                                    type_eval_t<function_object_type<const volatile remove_cv_t<T>, A>>>
{
};

//-----------------------------------------------------------------------------

// Deduces directly from callable type

template <typename T, typename, typename = void>
struct function_type
    : function_type_basis<remove_cv_t<T>>
{
};

// Deduces via call operator

template <typename T, typename A>
struct function_type<T, A, enable_if_t<std::is_class<remove_cvref_t<T>>::value>>
    : function_object_call<T, A>
{
};

} // namespace detail
} // namespace v1
} // namespace lean

#endif // LEAN_DETAIL_FUNCTION_TYPE_HPP
