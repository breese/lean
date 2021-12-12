#ifndef LEAN_DETAIL_INVOKE_HPP
#define LEAN_DETAIL_INVOKE_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <utility>
#include <lean/detail/config.hpp>
#include <lean/detail/type_traits.hpp>

// Avoid <functional>
// constexpr invocation from C++11

namespace lean
{
namespace v1
{

//-----------------------------------------------------------------------------

namespace detail
{

// Function object

template <typename F, typename... Args>
constexpr auto call(F&& fn, Args&&... args)
    noexcept(noexcept(std::declval<F>()(std::declval<Args>()...)))
    -> decltype(std::declval<F>()(std::declval<Args>()...))
{
    return std::forward<F>(fn)(std::forward<Args>(args)...);
}

// Member function with object reference

template <typename T, typename C, typename F, typename... Args>
constexpr auto call(T C::*fn, F&& object, Args&&... args)
    noexcept(noexcept((std::declval<F>().*std::declval<T C::*>())(std::declval<Args>()...)))
    -> decltype((std::declval<F>().*std::declval<T C::*>())(std::declval<Args>()...))
{
    return (std::forward<F>(object).*fn)(std::forward<Args>(args)...);
}

// Member function with object pointer

template <typename T, typename C, typename F, typename... Args>
constexpr auto call(T C::*fn, F *object, Args&&... args)
    noexcept(noexcept(call(std::declval<T C::*>(), std::declval<F&>(), std::declval<Args>()...)))
    -> decltype(call(std::declval<T C::*>(), std::declval<F&>(), std::declval<Args>()...))
{
    return call(fn, *object, std::forward<Args>(args)...);
}

} // namespace detail

//-----------------------------------------------------------------------------
// is_invocable
//
// Checks if callable type can be invoked with given arguments.

namespace detail
{

template <typename, typename = void>
struct is_invocable : std::false_type {};

template <typename F, typename... Args>
struct is_invocable<prototype<F, Args...>,
                    void_t<decltype(detail::call(std::declval<F>(), std::declval<Args>()...))>>
    : std::true_type
{
};

} // namespace detail

template <typename F, typename... Args>
struct is_invocable
    : public detail::is_invocable<prototype<F, Args...>>
{
};

//-----------------------------------------------------------------------------
// is_nothrow_invocable
//
// Checks if callable type can be invoked without throwing exceptions.
//
// The exception specification became part of the function type in C++17.
// This check always returns false when compiled with earlier C++ standards.

namespace detail
{

template <typename, typename = void>
struct is_nothrow_invocable : std::false_type {};

template <typename F, typename... Args>
struct is_nothrow_invocable<prototype<F, Args...>,
                            enable_if_t<is_invocable<prototype<F, Args...>>::value>>
    : std::integral_constant<bool,
                             noexcept(detail::call(std::declval<F>(), std::declval<Args>()...))>
{
};

} // namespace detail

template <typename F, typename... Args>
struct is_nothrow_invocable
    : public detail::is_nothrow_invocable<prototype<F, Args...>>
{
};

//-----------------------------------------------------------------------------
// invoke_result
//
// Deduces return type of callable type with given arguments.

namespace detail
{

template <typename, typename = void>
struct invoke_result;

template <typename F, typename... Args>
struct invoke_result<prototype<F, Args...>,
                     enable_if_t<is_invocable<prototype<F, Args...>>::value>>
{
    using type = decltype(detail::call(std::declval<F>(), std::declval<Args>()...));
};

} // namespace detail

template <typename F, typename... Args>
struct invoke_result
    : detail::invoke_result<prototype<F, Args...>>
{
};

template <typename F, typename... Args>
using invoke_result_t = typename invoke_result<F, Args...>::type;

//-----------------------------------------------------------------------------
// invoke

template <typename F, typename... Args>
constexpr auto invoke(F&& fn, Args&&... args) noexcept(is_nothrow_invocable<F, Args...>())
    -> invoke_result_t<F, Args...>
{
    return detail::call(std::forward<F>(fn), std::forward<Args>(args)...);
}

template <typename R, typename F, typename... Args>
constexpr R invoke_r(F&& fn, Args&&... args) noexcept(is_nothrow_invocable<F, Args...>())
{
    return static_cast<R>(invoke(std::forward<F>(fn), std::forward<Args>(args)...));
}

} // namespace v1
} // namespace lean

#endif // LEAN_DETAIL_INVOKE_HPP
