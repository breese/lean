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

#include <lean/detail/function_traits.hpp>
#include <lean/detail/type_traits.hpp>

namespace lean
{
namespace detail
{
namespace v1
{

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

// Function object
//
// Argument types disambiguates overloaded or template call operators.

template <typename, typename, typename, typename = void>
struct function_type_operator_near;

template <typename T, typename R, typename... Args>
struct function_type_operator_near<T,
                                   R,
                                   prototype<Args...>,
                                   void_t<decltype(static_cast<R (T::*)(Args...) const>(&T::operator()))>>
{
    using type = R(Args...) const;
};

template <typename T, typename R, typename... Args>
struct function_type_operator_near<T,
                                   R,
                                   prototype<Args...>,
                                   void_t<decltype(static_cast<R (T::*)(Args..., ...) const>(&T::operator()))>>
{
    using type = R(Args..., ...) const;
};

template <typename T, typename R, typename... Args>
struct function_type_operator_near<T&,
                                   R,
                                   prototype<Args...>,
                                   void_t<decltype(static_cast<R (T::*)(Args...) &>(&T::operator()))>>
{
    using type = R(Args...) &;
};

template <typename T, typename R, typename... Args>
struct function_type_operator_near<T&,
                                   R,
                                   prototype<Args...>,
                                   void_t<decltype(static_cast<R (T::*)(Args..., ...) &>(&T::operator()))>>
{
    using type = R(Args..., ...) &;
};

template <typename T, typename R, typename... Args>
struct function_type_operator_near<T&&,
                                   R,
                                   prototype<Args...>,
                                   void_t<decltype(static_cast<R (T::*)(Args...) &&>(&T::operator()))>>
{
    using type = R(Args...) &&;
};

template <typename T, typename R, typename... Args>
struct function_type_operator_near<T&&,
                                   R,
                                   prototype<Args...>,
                                   void_t<decltype(static_cast<R (T::*)(Args..., ...) &&>(&T::operator()))>>
{
    using type = R(Args..., ...) &&;
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
    using type = R (Args...) const noexcept(noexcept(std::declval<T>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept_near<T,
                                            R,
                                            prototype<Args...>,
                                            void_t<decltype(static_cast<R (T::*)(Args..., ...) const noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) const noexcept(noexcept(std::declval<T>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept_near<T&,
                                            R,
                                            prototype<Args...>,
                                            void_t<decltype(static_cast<R (T::*)(Args...) & noexcept>(&T::operator()))>>
{
    using type = R (Args...) & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept_near<T&,
                                            R,
                                            prototype<Args...>,
                                            void_t<decltype(static_cast<R (T::*)(Args..., ...) & noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept_near<T&&,
                                            R,
                                            prototype<Args...>,
                                            void_t<decltype(static_cast<R (T::*)(Args...) && noexcept>(&T::operator()))>>
{
    using type = R (Args...) && noexcept(noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept_near<T&&,
                                            R,
                                            prototype<Args...>,
                                            void_t<decltype(static_cast<R (T::*)(Args..., ...) && noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) && noexcept(noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)));
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
                              void_t<enable_if_t<is_same<T, remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...)>(&T::operator()))>>
{
    using type = R(Args...);
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...)>(&T::operator()))>>
{
    using type = R(Args..., ...);
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const>(&T::operator()))>>
{
    using type = R(Args...) const;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) const>(&T::operator()))>>
{
    using type = R (Args..., ...) const;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const &>(&T::operator()))>>
{
    using type = R (Args...) const &;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) const &>(&T::operator()))>>
{
    using type = R (Args..., ...) const &;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T&&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const &&>(&T::operator()))>>
{
    using type = R (Args...) const &&;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T&&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) const &&>(&T::operator()))>>
{
    using type = R (Args..., ...) const &&;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const volatile>(&T::operator()))>>
{
    using type = R (Args...) const volatile;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) const volatile>(&T::operator()))>>
{
    using type = R (Args..., ...) const volatile;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const volatile &>(&T::operator()))>>
{
    using type = R (Args...) const volatile &;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) const volatile &>(&T::operator()))>>
{
    using type = R (Args..., ...) const volatile &;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T&&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const volatile &&>(&T::operator()))>>
{
    using type = R (Args...) const volatile &&;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T&&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) const volatile &&>(&T::operator()))>>
{
    using type = R (Args..., ...) const volatile &&;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) volatile>(&T::operator()))>>
{
    using type = R (Args...) volatile;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) volatile>(&T::operator()))>>
{
    using type = R (Args..., ...) volatile;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) volatile &>(&T::operator()))>>
{
    using type = R (Args...) volatile &;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) volatile &>(&T::operator()))>>
{
    using type = R (Args..., ...) volatile &;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T&&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) volatile &&>(&T::operator()))>>
{
    using type = R (Args...) volatile &&;
};

template <typename T, typename R, typename... Args>
struct function_type_operator<T&&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args..., ...) volatile &&>(&T::operator()))>>
{
    using type = R (Args..., ...) volatile &&;
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
                                       void_t<enable_if_t<is_same<T, remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) noexcept>(&T::operator()))>>
{
    using type = R (Args...) noexcept(noexcept(std::declval<T>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) noexcept(noexcept(std::declval<T>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const noexcept>(&T::operator()))>>
{
    using type = R (Args...) const noexcept(noexcept(std::declval<T>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) const noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) const noexcept(noexcept(std::declval<T>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const & noexcept>(&T::operator()))>>
{
    using type = R (Args...) const & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) const & noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) const & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T&&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const && noexcept>(&T::operator()))>>
{
    using type = R (Args...) const && noexcept(noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T&&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) const && noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) const && noexcept(noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) volatile noexcept>(&T::operator()))>>
{
    using type = R (Args...) volatile noexcept(noexcept(std::declval<T>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) volatile noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) volatile noexcept(noexcept(std::declval<T>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) volatile & noexcept>(&T::operator()))>>
{
    using type = R (Args...) volatile & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) volatile & noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) volatile & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T&&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) volatile && noexcept>(&T::operator()))>>
{
    using type = R (Args...) volatile && noexcept(noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T&&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) volatile && noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) volatile && noexcept(noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const volatile noexcept>(&T::operator()))>>
{
    using type = R (Args...) const volatile noexcept(noexcept(std::declval<T>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) const volatile noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) const volatile noexcept(noexcept(std::declval<T>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const volatile & noexcept>(&T::operator()))>>
{
    using type = R (Args...) const volatile & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) const volatile & noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) const volatile & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T&&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const volatile && noexcept>(&T::operator()))>>
{
    using type = R (Args...) const volatile && noexcept(noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)));
};

template <typename T, typename R, typename... Args>
struct function_type_operator_noexcept<T&&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args..., ...) const volatile && noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) const volatile && noexcept(noexcept(std::declval<T&&>().operator()(std::declval<Args>()...)));
};

#endif

// Deduces directly from callable type

template <typename T, typename, typename = void>
struct function_type
    : function_type_basis<remove_cv_t<T>>
{
};

// Deduces via call operator

template <typename T, typename... Args>
struct function_type<T,
                     prototype<Args...>,
                     void_t<decltype(std::declval<T>().operator()(std::declval<Args>()...))>>
    : function_type_operator_noexcept<T,
                                      decltype(std::declval<T>().operator()(std::declval<Args>()...)),
                                      prototype<Args...>>
{
};

} // namespace v1
} // namespace detail
} // namespace lean

#endif // LEAN_DETAIL_FUNCTION_TYPE_HPP
