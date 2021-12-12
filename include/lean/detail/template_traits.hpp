#ifndef LEAN_DETAIL_TEMPLATE_TRAITS_HPP
#define LEAN_DETAIL_TEMPLATE_TRAITS_HPP

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
// template_size

template <typename>
struct template_size;

template <template <typename...> class Template, typename... Types>
struct template_size<Template<Types...>>
    : integral_constant<std::size_t, sizeof...(Types)>
{
};

template <typename T>
struct template_size<const T> : template_size<T>
{
};

//-----------------------------------------------------------------------------
// template_element

template <std::size_t, typename>
struct template_element;

template <std::size_t I, template <typename...> class Tuple, typename... Types>
struct template_element<I, Tuple<Types...>> : type_element<I, Types...> {};

template <std::size_t I, typename T>
using template_element_t = typename template_element<I, T>::type;

template <std::size_t I, typename T>
struct template_element<I, const T> {
private:
    using mutable_type = template_element_t<I, T>;
public:
    using type = copy_reference_t<mutable_type, add_const_t<remove_reference_t<mutable_type>>>;
};

//-----------------------------------------------------------------------------
// template_rebind
//
// Type alias for Rhs<LhsTypes...> given template Lhs<LhsTypes...> and
// template template Rhs.

template <typename, template <typename...> class>
struct template_rebind;

template <template <typename...> class Lhs, typename... LhsTypes,
          template <typename...> class Rhs>
struct template_rebind<Lhs<LhsTypes...>, Rhs>
{
    using type = Rhs<LhsTypes...>;
};

template <typename Lhs, template <typename...> class Rhs>
using template_rebind_t = typename template_rebind<Lhs, Rhs>::type;

} // namespace lean

#endif // LEAN_DETAIL_TEMPLATE_TRAITS_HPP
