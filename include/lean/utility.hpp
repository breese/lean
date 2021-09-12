#ifndef LEAN_UTILITY_HPP
#define LEAN_UTILITY_HPP

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
#include <lean/type_traits.hpp>

namespace lean
{

//-----------------------------------------------------------------------------
// Similar to decay-copy [expos.only.func]

template <typename T>
constexpr auto decay_forward(typename std::remove_reference<T>::type& value) noexcept -> decay_forward_t<T>
{
    return static_cast<decay_forward_t<T>>(value);
}

template <typename T>
constexpr auto decay_forward(typename std::remove_reference<T>::type&& value) noexcept -> decay_forward_t<T>
{
    return static_cast<decay_forward_t<T>>(value);
}

//-----------------------------------------------------------------------------
// exchange

#if __cpp_lib_exchange_function >= 201304L

template <typename T, typename U>
inline T exchange(T& target, U&& replacement)
{
    return std::exchange(target, std::forward<U>(replacement));
}

#else

template <typename T, typename U>
T exchange(T& target, U&& replacement)
{
    T result = std::move(target);
    target = std::forward<U>(replacement);
    return result;
}

#endif

//-----------------------------------------------------------------------------
// P0504

#if __cpp_lib_any >= 201606L

using in_place_t = std::in_place_t;

inline constexpr auto in_place = std::in_place;

template <typename T>
using in_place_type_t = std::in_place_type_t<T>;

template <typename T>
inline constexpr auto in_place_type = std::in_place_type;

#define LEAN_HAS_IN_PLACE 1
#define LEAN_HAS_IN_PLACE_TYPE 1

#elif __cpp_variable_templates >= 201304L

struct in_place_t
{
    explicit in_place_t() = default;
};

template <typename T>
struct in_place_type_t
{
    explicit in_place_type_t() = default;
};

static constexpr in_place_t in_place;

template <typename T>
static constexpr in_place_type_t<T> in_place_type;

#define LEAN_HAS_IN_PLACE 1
#define LEAN_HAS_IN_PLACE_TYPE 1

#else

enum in_place_t { in_place };

#define LEAN_HAS_IN_PLACE 1

#endif

} // namespace lean

#endif // LEAN_UTILITY_HPP
