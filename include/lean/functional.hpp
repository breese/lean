#ifndef LEAN_FUNCTIONAL_HPP
#define LEAN_FUNCTIONAL_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <lean/type_traits.hpp>

namespace lean
{
namespace v1
{
#if __cpp_lib_invoke >= 201411L

using std::invoke;

#if __cpp_lib_invoke_r >= 202106L

using std::invoke_r;

#else

template <typename R, typename F, typename... Args>
constexpr R invoke_r(F&& fn, Args&&... args) noexcept(is_nothrow_invocable<F, Args...>())
{
    return static_cast<R>(invoke(std::forward<F>(fn), std::forward<Args>(args)...));
}

#endif

#else

template <typename F, typename... Args>
auto invoke(F&& fn, Args&&... args) noexcept(is_nothrow_invocable<F, Args...>())
    -> invoke_result_t<F, Args...>
{
    return detail::invoke(std::forward<F>(fn), std::forward<Args>(args)...);
}

template <typename R, typename F, typename... Args>
R invoke_r(F&& fn, Args&&... args) noexcept(is_nothrow_invocable<F, Args...>())
{
    return static_cast<R>(invoke(std::forward<F>(fn), std::forward<Args>(args)...));
}

#endif

} // namespace v1

using v1::invoke;
using v1::invoke_r;

} // namespace lean

#endif // LEAN_FUNCTIONAL_HPP
