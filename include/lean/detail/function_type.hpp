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

// Uses "is_same<T, cv-qual remove_cv_t<T>>" to avoid greedy matching, where
// "const T" matches both "const A" and "const volatile A" leading to ambiguous
// template matching.

// mutable

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
struct function_object_type_r<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) &>(&T::operator()))>>
{
    using type = R(Args...) &;
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
struct function_object_type_r<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const &>(&T::operator()))>>
{
    using type = R (Args...) const &;
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
struct function_object_type_r<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) volatile &>(&T::operator()))>>
{
    using type = R (Args...) volatile &;
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
struct function_object_type_r<T&,
                              R,
                              prototype<Args...>,
                              void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                     decltype(static_cast<R (T::*)(Args...) const volatile &>(&T::operator()))>>
{
    using type = R (Args...) const volatile &;
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

// mutable ellipsis

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
                                     decltype(static_cast<R (T::*)(Args..., ...) &>(&T::operator()))>>
{
    using type = R(Args..., ...) &;
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

// const ellipsis

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
                                     decltype(static_cast<R (T::*)(Args..., ...) const &>(&T::operator()))>>
{
    using type = R (Args..., ...) const &;
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

// volatile ellipsis

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
                                     decltype(static_cast<R (T::*)(Args..., ...) volatile &>(&T::operator()))>>
{
    using type = R (Args..., ...) volatile &;
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

// const volatile ellipsis

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
                                     decltype(static_cast<R (T::*)(Args..., ...) const volatile &>(&T::operator()))>>
{
    using type = R (Args..., ...) const volatile &;
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

// mutable noexcept

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
struct function_object_type_noexcept_r<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) & noexcept>(&T::operator()))>>
{
    using type = R (Args...) & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
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

// const noexcept

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
struct function_object_type_noexcept_r<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const & noexcept>(&T::operator()))>>
{
    using type = R (Args...) const & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
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

// volatile noexcept

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
struct function_object_type_noexcept_r<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) volatile & noexcept>(&T::operator()))>>
{
    using type = R (Args...) volatile & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
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

// const volatile noexcept

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
struct function_object_type_noexcept_r<T&,
                                       R,
                                       prototype<Args...>,
                                       void_t<enable_if_t<is_same<T, const volatile remove_cv_t<T>>::value>,
                                              decltype(static_cast<R (T::*)(Args...) const volatile & noexcept>(&T::operator()))>>
{
    using type = R (Args...) const volatile & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
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

// mutable noexcept ellipsis

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
                                              decltype(static_cast<R (T::*)(Args..., ...) & noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
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

// const noexcept ellipsis

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
                                              decltype(static_cast<R (T::*)(Args..., ...) const & noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) const & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
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

// volatile noexcept ellipsis

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
                                              decltype(static_cast<R (T::*)(Args..., ...) volatile & noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) volatile & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
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

// const volatile noexcept ellipsis

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
                                              decltype(static_cast<R (T::*)(Args..., ...) const volatile & noexcept>(&T::operator()))>>
{
    using type = R (Args..., ...) const volatile & noexcept(noexcept(std::declval<T&>().operator()(std::declval<Args>()...)));
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

// Deduces return type and queries exact function type

template <typename T, typename A, typename = void>
struct function_object_type
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

// Detects ambiguous overloads

template <typename T, typename A, typename = void>
struct is_function_object_ambiguous_1 : std::false_type {};

template <typename T, typename A>
struct is_function_object_ambiguous_1<T,
                                      A,
                                      void_t<type_t<function_object_type<type_t<add_type_const<T>>, A>>,
                                             type_t<function_object_type<type_t<add_type_volatile<T>>, A>>>>
    : std::true_type
{
};

template <typename T, typename A, typename = void>
struct is_function_object_ambiguous
    : is_function_object_ambiguous_1<T, A>
{
};

template <typename T, typename A>
struct is_function_object_ambiguous<T,
                                    A,
                                    void_t<type_t<function_object_type<T, A>>>>
    : std::false_type
{
};

// Prioritized selection of overload with nearly matching cv-qualifiers

template <typename T, typename A, typename = void>
struct function_object_near_cv
{
};

template <typename T, typename A>
struct function_object_near_cv<T,
                               A,
                               void_t<type_t<function_object_type<type_t<add_type_cv<T>>, A>>>>
    : function_object_type<type_t<add_type_cv<T>>, A>
{
};

template <typename T, typename A, typename = void>
struct function_object_near_volatile
    : function_object_near_cv<T, A>
{
};

template <typename T, typename A>
struct function_object_near_volatile<T,
                                     A,
                                     void_t<enable_if_t<!std::is_const<remove_reference_t<T>>::value>,
                                            type_t<function_object_type<type_t<add_type_volatile<T>>, A>>>>
    : function_object_type<type_t<add_type_volatile<T>>, A>
{
};

template <typename T, typename A, typename = void>
struct function_object_near_const
    : function_object_near_volatile<T, A>
{
};

template <typename T, typename A>
struct function_object_near_const<T,
                                  A,
                                  void_t<enable_if_t<!std::is_volatile<remove_reference_t<T>>::value>,
                                         type_t<function_object_type<type_t<add_type_const<T>>, A>>>>
    : function_object_type<type_t<add_type_const<T>>, A>
{
};

template <typename T, typename A, typename = void>
struct function_object_near
    : function_object_near_const<T, A>
{
};

template <typename T, typename A>
struct function_object_near<T,
                            A,
                            void_t<type_t<function_object_type<T, A>>>>
    : function_object_type<T, A>
{
};

// lvalue-referenced object

template <typename T, typename A, typename = void>
struct function_object_lvalue_near
{
};

template <typename T, typename A>
struct function_object_lvalue_near<T,
                                   A,
                                   void_t<type_t<function_object_near<T, A>>>>
    : function_object_near<T, A>
{
};

template <typename T, typename A>
struct function_object_lvalue_near<T,
                                   A,
                                   void_t<type_t<function_object_near<T&, A>>>>
    : function_object_near<T&, A>
{
};

template <typename T, typename A, typename = void>
struct function_object_lvalue_ambiguity_guard
    : function_object_lvalue_near<T, A>
{
};

template <typename T, typename A>
struct function_object_lvalue_ambiguity_guard<T,
                                              A,
                                              enable_if_t<is_function_object_ambiguous<T, A>::value ||
                                                          is_function_object_ambiguous<T&, A>::value>>
{
};

template <typename T, typename A, typename = void>
struct function_object_lvalue
    : function_object_lvalue_ambiguity_guard<T, A>
{
};

template <typename T, typename A>
struct function_object_lvalue<T,
                              A,
                              void_t<type_t<function_object_type<T&, A>>>>
    : function_object_type<T&, A>
{
    // Exact match
};

// rvalue-referenced object

template <typename T, typename A, typename = void>
struct function_object_rvalue_exact_const_ref
    : function_object_near<T, A>
{
};

// Special case for life-time extension
template <typename T, typename A>
struct function_object_rvalue_exact_const_ref<T,
                                              A,
                                              void_t<enable_if_t<!std::is_volatile<remove_reference_t<T>>::value>,
                                                     type_t<function_object_type<const T&, A>>>>
    : function_object_type<const T&, A>
{
};

template <typename T, typename A, typename = void>
struct function_object_rvalue_exact_value
    : function_object_rvalue_exact_const_ref<T, A>
{
};

template <typename T, typename A>
struct function_object_rvalue_exact_value<T,
                                          A,
                                          void_t<type_t<function_object_type<T, A>>>>
    : function_object_type<T, A>
{
};

template <typename T, typename A, typename = void>
struct function_object_rvalue_near
    : function_object_rvalue_exact_value<T, A>
{
};

template <typename T, typename A>
struct function_object_rvalue_near<T,
                                   A,
                                   void_t<type_t<function_object_near<T&&, A>>>>
    : function_object_near<T&&, A>
{
};

template <typename T, typename A, typename = void>
struct function_object_rvalue_ambiguity_guard
    : function_object_rvalue_near<T, A>
{
};

template <typename T, typename A>
struct function_object_rvalue_ambiguity_guard<T,
                                              A,
                                              enable_if_t<is_function_object_ambiguous<T, A>::value ||
                                                          is_function_object_ambiguous<T&&, A>::value>>
{
};

template <typename T, typename A, typename = void>
struct function_object_rvalue
    : function_object_rvalue_ambiguity_guard<T, A>
{
};

template <typename T, typename A>
struct function_object_rvalue<T,
                              A,
                              void_t<type_t<function_object_type<T&&, A>>>>
    : function_object_type<T&&, A>
{
    // Exact match
};

// object

template <typename T, typename A, typename = void>
struct function_object_value_exact_lvalue
    : function_object_near<T, A>
{
};

template <typename T, typename A>
struct function_object_value_exact_lvalue<T,
                                          A,
                                          void_t<type_t<function_object_lvalue<T, A>>>>
    : function_object_lvalue<T, A>
{
};

template <typename T, typename A, typename = void>
struct function_object_value_ambiguity_guard
    : function_object_value_exact_lvalue<T, A>
{
};

template <typename T, typename A>
struct function_object_value_ambiguity_guard<T,
                                             A,
                                             enable_if_t<is_function_object_ambiguous<T, A>::value>>
{
};

template <typename T, typename A, typename = void>
struct function_object_value
    : function_object_value_ambiguity_guard<T, A>
{
};

template <typename T, typename A>
struct function_object_value<T,
                             A,
                             void_t<type_t<function_object_type<T, A>>>>
    : function_object_type<T, A>
{
    // Exact match
};

template <typename T, typename A, typename = void>
struct function_object_call
    : function_object_value<T, A>
{
};

template <typename T, typename A>
struct function_object_call<T&, A>
    : function_object_lvalue<T, A>
{
};

template <typename T, typename A>
struct function_object_call<T&&, A>
    : function_object_rvalue<T, A>
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
