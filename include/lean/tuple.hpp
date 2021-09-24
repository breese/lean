#ifndef LEAN_TUPLE_HPP
#define LEAN_TUPLE_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <tuple>
#include <lean/detail/config.hpp>
#include <lean/utility.hpp> // integer_sequence

namespace lean
{

//-----------------------------------------------------------------------------
// apply

#if __cpp_lib_apply >= 201603L

template <typename R, typename F, typename... Args>
constexpr R apply_r(F&& fn, Args&&... args)
{
    return static_cast<R>(std::apply(std::forward<F>(fn), std::forward<Args>(args)...));
}

#else

namespace detail
{

template <typename R, typename F, typename Tuple, std::size_t... Ints>
LEAN_CONSTEXPR_CXX14
R apply_r(F&& fn, Tuple&& tuple, lean::index_sequence<Ints...>)
{
    return std::forward<F>(fn)(std::get<Ints>(tuple)...);
}

} // namespace detail

template <typename R, typename F, template<typename...> class Tuple, typename... Args>
LEAN_CONSTEXPR_CXX14
R apply_r(F&& fn, Tuple<Args...>&& tuple)
{
    return detail::apply_r<R>(std::forward<F>(fn),
                              std::forward<Tuple<Args...>>(tuple),
                              lean::make_index_sequence<sizeof...(Args)>{});
}

#endif

} // namespace lean

#endif // LEAN_TUPLE_HPP
