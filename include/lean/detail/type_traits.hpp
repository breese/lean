#ifndef LEAN_DETAIL_TYPE_TRAITS_HPP
#define LEAN_DETAIL_TYPE_TRAITS_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <type_traits>

namespace lean
{

//-----------------------------------------------------------------------------
// bool_constant [N4389]

using std::integral_constant;

#if __cpp_lib_bool_constant

using std::bool_constant;

#else

template <bool B>
using bool_constant = integral_constant<bool, B>;

#endif

//-----------------------------------------------------------------------------
// Aliases [N3655]

using std::add_const;
using std::add_pointer;
using std::add_rvalue_reference;
using std::conditional;
using std::decay;
using std::enable_if;
using std::is_same;
using std::remove_const;
using std::remove_reference;

#if __cpp_lib_transformation_trait_aliases >= 201304L

using std::add_const_t;
using std::add_pointer_t;
using std::add_rvalue_reference_t;
using std::conditional_t;
using std::decay_t;
using std::enable_if_t;
using std::remove_const_t;
using std::remove_reference_t;

#else

template <typename T>
using add_const_t = typename add_const<T>::type;

template <typename T>
using add_pointer_t = typename add_pointer<T>::type;

template <typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

template <typename T>
using decay_t = typename std::decay<T>::type;

template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

template <typename T>
using remove_const_t = typename remove_const<T>::type;

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

#endif

//-----------------------------------------------------------------------------
// logical operator types [P0013]
//
// Constraint: conjunction and disjuction cannot use final types

#if __cpp_lib_logical_traits >= 201510L

using std::conjunction;
using std::disjunction;
using std::negation;

#else

template <typename T>
struct negation
    : bool_constant<!static_cast<bool>(T::value)>
{
};

template <typename...>
struct conjunction : std::true_type {};

template <typename T>
struct conjunction<T> : T {};

template <typename T, typename... Types>
struct conjunction<T, Types...>
    : conditional_t<negation<T>::value,
                    T,
                    conjunction<Types...>>
{
};

template <typename...>
struct disjunction : std::false_type {};

template <typename T>
struct disjunction<T> : T {};

template <typename T, typename... Types>
struct disjunction<T, Types...>
    : conditional_t<negation<T>::value,
                    disjunction<Types...>,
                    T>
{
};

#endif

//-----------------------------------------------------------------------------
// remove_cvref [P0550]

#if __cpp_lib_remove_cvref >= 201711L

using std::remove_cvref;
using std::remove_cvref_t;

#else

template <typename T>
struct remove_cvref : public std::remove_cv<remove_reference_t<T>> {};

template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

#endif

//-----------------------------------------------------------------------------
// type_identity [P0887]

#if __cpp_lib_type_identity >= 201806L

using std::type_identity;
using std::type_identity_t;

#else

template <typename T>
struct type_identity
{
    using type = T;
};

template <typename T>
using type_identity_t = typename type_identity<T>::type;

#endif

//-----------------------------------------------------------------------------
// type_front
//
// Type alias for the first type in a parameter pack.
//
// type_front<bool, int, float> == bool
//
// Constraint: sizeof...(Ts) > 0

template <typename T, typename...>
struct type_front { using type = T; };

template <typename... Ts>
using type_front_t = typename type_front<Ts...>::type;

//-----------------------------------------------------------------------------
// type_element
//
// Type alias for the Nth type in a parameter pack.
//
// N is zero-indexed.
//
// type_element<0, bool, int, float> == bool
// type_element<1, bool, int, float> == int
// type_element<2, bool, int, float> == float
//
// Constraint: N <= sizeof...(Ts)

#if defined(__has_builtin)
# if __has_builtin(__type_pack_element)
#  define LEAN_HAS_TYPE_PACK_ELEMENT 1
# endif
#endif

#if defined(LEAN_HAS_TYPE_PACK_ELEMENT)

template <std::size_t N, typename... Ts>
struct type_element
{
    using type = __type_pack_element<N, Ts...>;
};

#else

namespace impl
{

template <std::size_t N, typename, typename... Tail>
struct type_element
    : public type_element<N - 1, Tail...>
{
};

template <typename T, typename... Tail>
struct type_element<0, T, Tail...>
{
    using type = T;
};

template <typename U, typename T, typename... Tail>
struct type_element<1, U, T, Tail...>
{
    using type = T;
};

} // namespace impl

template <std::size_t N, typename... Ts>
struct type_element
    : public impl::type_element<N, Ts...>
{
};

#endif

template <std::size_t N, typename... Ts>
using type_element_t = typename type_element<N, Ts...>::type;

#undef LEAN_HAS_TYPE_PACK_ELEMENT

//-----------------------------------------------------------------------------
// type_sizeof

template <typename T>
struct type_sizeof
    : public std::integral_constant<std::size_t, sizeof(T)>
{
};

//-----------------------------------------------------------------------------
// type_less

template <template <typename> class F, typename Lhs, typename Rhs>
struct type_less_with
    : public bool_constant<(F<Lhs>::value < F<Rhs>::value)>
{
};

template <typename Lhs, typename Rhs>
using type_less = type_less_with<type_identity_t, Lhs, Rhs>;

//-----------------------------------------------------------------------------
// type_greater

template <template <typename> class F, typename Lhs, typename Rhs>
struct type_greater_with
    : public bool_constant<(F<Lhs>::value > F<Rhs>::value)>
{
};

template <typename Lhs, typename Rhs>
using type_greater = typename type_greater_with<type_identity_t, Lhs, Rhs>::type;

//-----------------------------------------------------------------------------
// void_t [N3911]
//
// std::void_t is defined as
//
//   template <typename...> using void_t = void
//
// This does not always work well with SFINAE (see CWG 1558)

namespace detail
{

template <typename...>
struct make_void { using type = void; };

} // namespace detail

template <typename... Ts>
using void_t = typename detail::make_void<Ts...>::type;

} // namespace lean

#endif // LEAN_DETAIL_TYPE_TRAITS_HPP
