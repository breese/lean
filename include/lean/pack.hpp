#ifndef LEAN_PACK_HPP
#define LEAN_PACK_HPP

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

//-----------------------------------------------------------------------------
// Parameter pack

template <typename...>
struct pack;

//-----------------------------------------------------------------------------
// pack_front
//
// Type alias for the first type in a parameter pack or a type list.
//
// pack_front<bool, int, float> == bool
// pack_front<std::tuple<bool, int, float>> == bool

namespace impl
{

template <typename...>
struct pack_front;

template <typename T, typename... Tail>
struct pack_front<T, Tail...> { using type = T; };

template <template <typename...> class List, typename T, typename... Tail>
struct pack_front<List<T, Tail...>> { using type = T; };

} // namespace impl

template <typename... Ts>
using pack_front = typename impl::pack_front<Ts...>::type;

//-----------------------------------------------------------------------------
// pack_contains

template <typename List, typename T>
struct pack_contains
    : public std::false_type
{
};

template <template <typename...> class List, typename... Tail, typename T>
struct pack_contains<List<T, Tail...>, T>
    : public std::true_type
{
};

template <template <typename...> class List, typename Head, typename... Tail, typename T>
struct pack_contains<List<Head, Tail...>, T>
    : public pack_contains<List<Tail...>, T>
{
};

} // namespace lean

#endif // LEAN_PACK_HPP
