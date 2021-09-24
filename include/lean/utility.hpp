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
#include <lean/detail/config.hpp>
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

using std::exchange;

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

#if __cplusplus >= LEAN_CXX17

using std::in_place_t;
using std::in_place;
using std::in_place_type_t;
using std::in_place_type;

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

//-----------------------------------------------------------------------------
// integer_sequence

#if __cpp_lib_integer_sequence >= 201304L

using std::integer_sequence;
using std::index_sequence;

using std::make_integer_sequence;
using std::make_index_sequence;

using std::index_sequence_for;

#else

// Partly inspired by Boost::Mpl11

template <typename T, T... Ints>
struct integer_sequence
{
    using value_type = T;
    static constexpr std::size_t size() noexcept { return sizeof...(Ints); }
};

template <std::size_t... Ints>
using index_sequence = integer_sequence<std::size_t, Ints...>;

namespace detail
{

template <typename, typename...>
struct append_integer_sequence;

template <typename T, T... Lhs, T... Rhs>
struct append_integer_sequence<T, integer_sequence<T, Lhs...>, integer_sequence<T, Rhs...>>
{
    using type = integer_sequence<T, Lhs..., (Rhs + sizeof...(Lhs))...>;
};

template <typename>
struct make_integer_sequence;

template <typename T, T N>
struct make_integer_sequence_helper
{
private:
    using sequence = typename make_integer_sequence<std::integral_constant<T, N / 2>>::type;
    using lhs_sequence = typename append_integer_sequence<T, sequence, sequence>::type;
    using rhs_sequence = typename make_integer_sequence<std::integral_constant<T, N % 2>>::type;

public:
    using type = typename append_integer_sequence<T, lhs_sequence, rhs_sequence>::type;
};

template <typename C>
struct make_integer_sequence
{
    static_assert(C::value >= 0, "N cannot be negative");

    using type = typename detail::make_integer_sequence_helper<typename C::value_type, C::value>::type;
};

template <typename T>
struct make_integer_sequence<std::integral_constant<T, 0>>
{
    using type = integer_sequence<T>;
};

template <typename T>
struct make_integer_sequence<std::integral_constant<T, 1>>
{
    using type = integer_sequence<T, 0>;
};

} // namespace detail

template <typename T, T N>
using make_integer_sequence = typename detail::make_integer_sequence<std::integral_constant<T, N>>::type;

template <std::size_t N>
using make_index_sequence = make_integer_sequence<std::size_t, N>;

template <typename... T>
using index_sequence_for = make_index_sequence<sizeof...(T)>;

#endif

} // namespace lean

#endif // LEAN_UTILITY_HPP
