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
// Type-list

template <typename...>
struct pack;

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
using std::add_lvalue_reference;
using std::add_rvalue_reference;
using std::add_volatile;
using std::conditional;
using std::decay;
using std::enable_if;
using std::is_same;
using std::remove_const;
using std::remove_cv;
using std::remove_pointer;
using std::remove_reference;

#if __cpp_lib_transformation_trait_aliases >= 201304L

using std::add_const_t;
using std::add_pointer_t;
using std::add_lvalue_reference_t;
using std::add_rvalue_reference_t;
using std::add_volatile_t;
using std::conditional_t;
using std::decay_t;
using std::enable_if_t;
using std::remove_const_t;
using std::remove_cv_t;
using std::remove_pointer_t;
using std::remove_reference_t;

#else

template <typename T>
using add_const_t = typename add_const<T>::type;

template <typename T>
using add_pointer_t = typename add_pointer<T>::type;

template <typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

template <typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

template <typename T>
using add_volatile_t = typename add_volatile<T>::type;

template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

template <typename T>
using decay_t = typename std::decay<T>::type;

template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

template <typename T>
using remove_const_t = typename remove_const<T>::type;

template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

template <typename T>
using remove_pointer_t = typename remove_pointer<T>::type;

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
// remove_member_pointer
//
// If T has type "(possibly cv-qualified) pointer to data member T1" then the
// member type alias names T1, otherwise T.
//
//   T                | remove_member_pointer_t<T>
// -------------------+----------------------------
//  bool *            | bool *
//  bool cls::*       | bool
//  bool cls::* const | bool
//  const bool cls::* | const bool
//  bool (*)()        | bool (*)()

namespace impl
{

template <typename T>
struct remove_member_object_pointer
{
    using type = T;
};

template <typename Class, typename T>
struct remove_member_object_pointer<T Class::*>
{
    using type = T;
};

template <typename Class, typename T>
struct remove_member_object_pointer<T Class::* const>
{
    using type = T;
};

template <typename Class, typename T>
struct remove_member_object_pointer<T Class::* volatile>
{
    using type = T;
};

template <typename Class, typename T>
struct remove_member_object_pointer<T Class::* const volatile>
{
    using type = T;
};

} // namespace impl

template <typename T, typename = void>
struct remove_member_pointer
{
    using type = T;
};

template <typename T>
struct remove_member_pointer<T, enable_if_t<std::is_member_object_pointer<T>::value>>
    : impl::remove_member_object_pointer<T>
{
};


template <typename T>
using remove_member_pointer_t = typename remove_member_pointer<T>::type;

//-----------------------------------------------------------------------------
// copy_const [P1450]
//
// Let Rhs be const if Lhs is const

template <typename Lhs, typename Rhs>
struct copy_const
    : conditional<std::is_const<Lhs>::value,
                  add_const_t<Rhs>,
                  Rhs>
{
};

template <typename Lhs, typename Rhs>
using copy_const_t = typename copy_const<Lhs, Rhs>::type;

//-----------------------------------------------------------------------------
// copy_volatile [P1450]
//
// Let Rhs be volatile if Rhs is volatile

template <typename Lhs, typename Rhs>
struct copy_volatile
    : conditional<std::is_volatile<Lhs>::value,
                  add_volatile_t<Rhs>,
                  Rhs>
{
};

template <typename Lhs, typename Rhs>
using copy_volatile_t = typename copy_volatile<Lhs, Rhs>::type;

//-----------------------------------------------------------------------------
// copy_cv [P1450]

template <typename Lhs, typename Rhs>
struct copy_cv
    : copy_volatile<Lhs, copy_const_t<Lhs, Rhs>>
{
};

template <typename Lhs, typename Rhs>
using copy_cv_t = typename copy_cv<Lhs, Rhs>::type;

//-----------------------------------------------------------------------------
// copy_reference [P1450]

template <typename Lhs, typename Rhs>
struct copy_reference
    : conditional<std::is_lvalue_reference<Lhs>::value,
                  add_lvalue_reference_t<Rhs>,
                  conditional_t<std::is_rvalue_reference<Lhs>::value,
                                add_rvalue_reference_t<Rhs>,
                                Rhs>>
{
};

template <typename Lhs, typename Rhs>
using copy_reference_t = typename copy_reference<Lhs, Rhs>::type;

//-----------------------------------------------------------------------------
// copy_cvref [P1450]

template <typename Lhs, typename Rhs>
struct copy_cvref
    : copy_reference<Lhs,
                     copy_reference_t<Rhs,
                                      copy_cv_t<remove_reference_t<Lhs>,
                                                remove_reference_t<Rhs>>>>
{
};

template <typename Lhs, typename Rhs>
using copy_cvref_t = typename copy_cvref<Lhs, Rhs>::type;

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

//-----------------------------------------------------------------------------
// is_complete

template <typename T, typename = void>
struct is_complete : std::false_type {};

template <typename T>
struct is_complete<T, void_t<decltype(sizeof(T))>> : std::true_type {};

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
// Helper to bind a projection to a predicate

template <template <template <typename> class, typename, typename> class Predicate,
          template <typename> class Projection>
struct type_bind_projection
{
    template <typename Lhs, typename Rhs>
    using with = Predicate<Projection, Lhs, Rhs>;
};

//-----------------------------------------------------------------------------
// type_contains
//
// Checks if the first type appears later in the parameter pack.

template <typename, typename...>
struct type_contains;

template <typename T>
struct type_contains<T>
    : public std::false_type
{
};

template <typename T, typename... Tail>
struct type_contains<T, T, Tail...>
    : public std::true_type
{
};

template <typename T, typename Head, typename... Tail>
struct type_contains<T, Head, Tail...>
    : public type_contains<T, Tail...>
{
};

//-----------------------------------------------------------------------------
// type_fold_left
//
// F(F(F(T0, T1), T2), T3)...
//
// type = Ti
// value = i

namespace impl
{

template <std::size_t N, std::size_t M, template <typename, typename> class, typename...>
struct type_fold_left;

template <std::size_t N, std::size_t M, template <typename, typename> class F>
struct type_fold_left<N, M, F>;

template <std::size_t N, std::size_t M, template <typename, typename> class F, typename T>
struct type_fold_left<N, M, F, T>
{
    using type = T;
    static constexpr std::size_t value = N;
    constexpr operator std::size_t() const noexcept { return value; }
};

template <std::size_t N, std::size_t M, template <typename, typename> class F, typename Lhs, typename Rhs>
struct type_fold_left<N, M, F, Lhs, Rhs>
{
    using type = typename F<Lhs, Rhs>::type;
    static constexpr std::size_t value = std::is_same<type, Lhs>::value ? N : M;
    constexpr operator std::size_t() const noexcept { return value; }
};

template <std::size_t N, std::size_t M, template <typename, typename> class F, typename Lhs, typename Rhs, typename... Tail>
struct type_fold_left<N, M, F, Lhs, Rhs, Tail...>
{
private:
    using head_type = type_fold_left<N, N + 1, F, Lhs, Rhs>;
    using recursive_type = type_fold_left<head_type::value, N + 2, F, typename head_type::type, Tail...>;

public:
    using type = typename recursive_type::type;
    static constexpr std::size_t value = recursive_type::value;
    constexpr operator std::size_t() const noexcept { return value; }
};

} // namespace impl

template <template <typename, typename> class F, typename... Types>
struct type_fold_left
    : impl::type_fold_left<0, 0, F, Types...>
{
};

template <template <typename, typename> class F, typename... Types>
using type_fold_left_t = typename type_fold_left<F, Types...>::type;

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
// type_predicate_min
//
// Type alias for the type with the lowest Projection<T>::value

template <template <typename> class Projection, typename Lhs, typename Rhs>
struct type_predicate_min_with
    : conditional<(Projection<Lhs>::value < Projection<Rhs>::value), Lhs, Rhs>
{
};

template <typename Lhs, typename Rhs>
struct type_predicate_min
    : type_predicate_min_with<type_identity_t, Lhs, Rhs>
{
};

template <template <typename> class Projection, typename Lhs, typename Rhs>
using type_predicate_min_with_t = typename type_predicate_min_with<Projection, Lhs, Rhs>::type;

template <typename Lhs, typename Rhs>
using type_predicate_min_t = typename type_predicate_min<Lhs, Rhs>::type;

//-----------------------------------------------------------------------------
// type_predicate_max
//
// Type alias for the type with the highest Projection<T>::value

template <template <typename> class Projection, typename Lhs, typename Rhs>
struct type_predicate_max_with
    : conditional<(Projection<Lhs>::value > Projection<Rhs>::value), Lhs, Rhs>
{
};

template <typename Lhs, typename Rhs>
struct type_predicate_max
    : type_predicate_max_with<type_identity_t, Lhs, Rhs>
{
};

template <template <typename> class Projection, typename Lhs, typename Rhs>
using type_predicate_max_with_t = typename type_predicate_max_with<Projection, Lhs, Rhs>::type;

template <typename Lhs, typename Rhs>
using type_predicate_max_t = typename type_predicate_max<Lhs, Rhs>::type;

//-----------------------------------------------------------------------------
// type_min
//
// Type alias for the type with the lowest Projection<T>::value.

template <template <typename> class Projection, typename... Types>
struct type_min_with
    : type_fold_left<type_bind_projection<type_predicate_min_with, Projection>::template with, Types...>
{
};

template <template <typename> class Projection, typename... Types>
using type_min_with_t = typename type_min_with<Projection, Types...>::type;

template <typename... Types>
using type_min_t = typename type_min_with<type_identity, Types...>::type;

//-----------------------------------------------------------------------------
// type_find_min

template <template <typename> class Projection, typename... Types>
struct type_find_min_with
    : std::integral_constant<std::size_t,
                             type_min_with<Projection, Types...>::value>
{
};

template <typename... Types>
using type_find_min = type_find_min_with<type_identity_t, Types...>;

//-----------------------------------------------------------------------------
// type_max
//
// Type alias for the type with the lowest Projection<T>::value.

template <template <typename> class Projection, typename... Types>
struct type_max_with
    : type_fold_left<type_bind_projection<type_predicate_max_with, Projection>::template with, Types...>
{
};

template <template <typename> class Projection, typename... Types>
using type_max_with_t = typename type_max_with<Projection, Types...>::type;

template <typename... Types>
using type_max_t = typename type_max_with<type_identity, Types...>::type;

//-----------------------------------------------------------------------------
// type_find_max

template <template <typename> class Projection, typename... Types>
struct type_find_max_with
    : std::integral_constant<std::size_t,
                             type_max_with<Projection, Types...>::value>
{
};

template <typename... Types>
using type_find_max = type_find_max_with<type_identity_t, Types...>;

//-----------------------------------------------------------------------------
// pack_rebind
//
// Type alias for Lhs<RhsTypes...> given Lhs<LhsTypes...> and Rhs<RhsTypes...>.

template <typename, typename>
struct pack_rebind;

template <template <typename...> class Lhs, typename... LhsTypes,
          template <typename...> class Rhs, typename... RhsTypes>
struct pack_rebind<Lhs<LhsTypes...>,
                   Rhs<RhsTypes...>>
{
    using type = Lhs<RhsTypes...>;
};

template <typename Lhs, typename Rhs>
using pack_rebind_t = typename pack_rebind<Lhs, Rhs>::type;

} // namespace lean

#endif // LEAN_DETAIL_TYPE_TRAITS_HPP
