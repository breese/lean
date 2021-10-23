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
// Type alias for the first type in a type list.
//
// pack_front<pack<bool, int, float>> == bool
// pack_front<std::tuple<bool, int, float>> == bool

namespace impl
{

template <typename>
struct pack_front;

template <template <typename...> class List, typename... Ts>
struct pack_front<List<Ts...>> { using type = lean::type_front<Ts...>; };

} // namespace impl

template <typename List>
using pack_front = typename impl::pack_front<List>::type;

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

//-----------------------------------------------------------------------------
// pack_fold

namespace impl
{

template <typename, template <typename, typename> class>
struct pack_fold;

template <template <typename...> class List, template <typename, typename> class Predicate>
struct pack_fold<List<>, Predicate>;

template <template <typename...> class List, typename T, template <typename, typename> class Predicate>
struct pack_fold<List<T>, Predicate>
{
    using type = T;
};

template <template <typename...> class List, typename T, typename U, template <typename, typename> class Predicate>
struct pack_fold<List<T, U>, Predicate>
{
    using type = conditional_t<Predicate<T, U>::value, T, U>;
};

template <template <typename...> class List, typename T, typename U, typename... Tail, template <typename, typename> class Predicate>
struct pack_fold<List<T, U, Tail...>, Predicate>
{
    using type = typename pack_fold<List<typename pack_fold<List<T, U>, Predicate>::type, Tail...>, Predicate>::type;
};

} // namespace impl

template <typename List, template <typename, typename> class Predicate>
using pack_fold = typename impl::pack_fold<List, Predicate>::type;

} // namespace lean

#endif // LEAN_PACK_HPP
