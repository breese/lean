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

} // namespace lean

#endif // LEAN_PACK_HPP
