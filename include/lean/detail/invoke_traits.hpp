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

#include <functional> // std::mem_fn
#include <lean/detail/config.hpp>
#include <lean/detail/type_traits.hpp>

namespace lean
{
namespace v1
{
namespace detail
{

//-----------------------------------------------------------------------------

template <typename, typename = void>
struct invoke_overload;

template <typename F, typename... Args>
struct invoke_overload<proto<F, Args...>,
                       void_t<decltype(std::declval<F>()(std::declval<Args>()...))>>
{
    template <typename... CallArgs>
    static auto invoke(F fn, CallArgs&&... args)
        noexcept(noexcept(fn(std::forward<CallArgs>(args)...)))
        -> decltype(fn(std::forward<CallArgs>(args)...))
    {
        return fn(std::forward<CallArgs>(args)...);
    }
};

template <typename F, typename... Args>
struct invoke_overload<proto<F, Args...>,
                       void_t<decltype(std::mem_fn(std::declval<F>())(std::declval<Args>()...))>>
{
    template <typename... CallArgs>
    static auto invoke(F fn, CallArgs&&... args)
        noexcept(noexcept(std::mem_fn(std::move(fn))(std::forward<CallArgs>(args)...)))
        -> decltype(std::mem_fn(std::move(fn))(std::forward<CallArgs>(args)...))
    {
        return std::mem_fn(std::move(fn))(std::forward<CallArgs>(args)...);
    }
};

//-----------------------------------------------------------------------------

template <typename F, typename... Args>
auto invoke(F&& fn, Args&&... args)
    noexcept(noexcept(invoke_overload<proto<F, Args...>>::invoke(std::forward<F>(fn), std::forward<Args>(args)...)))
    -> decltype(invoke_overload<proto<F, Args...>>::invoke(std::forward<F>(fn), std::forward<Args>(args)...))
{
    return invoke_overload<proto<F, Args...>>::invoke(std::forward<F>(fn), std::forward<Args>(args)...);
}

//-----------------------------------------------------------------------------

template <typename, typename = void>
struct is_invocable : public std::false_type {};

template <typename F, typename... Args>
struct is_invocable<proto<F, Args...>,
                    void_t<decltype(invoke(std::declval<F>(), std::declval<Args>()...))>>
    : public std::true_type
{
};

//-----------------------------------------------------------------------------

template <typename, typename = void>
struct is_nothrow_invocable : public std::false_type {};

template <typename F, typename... Args>
struct is_nothrow_invocable<proto<F, Args...>,
                            enable_if_t<is_invocable<proto<F, Args...>>::value>>
    : public std::integral_constant<bool,
                                    noexcept(invoke(std::declval<F>(), std::declval<Args>()...))>
{
};

//-----------------------------------------------------------------------------

template <typename, typename = void>
struct invoke_result;

template <typename F, typename... Args>
struct invoke_result<proto<F, Args...>,
                     enable_if_t<is_invocable<proto<F, Args...>>::value>>
{
    using type = decltype(invoke_overload<proto<F, Args...>>::invoke(std::declval<F>(), std::declval<Args>()...));
};

} // namespace detail
} // namespace v1
} // namespace lean

#endif // LEAN_DETAIL_INVOKE_HPP
