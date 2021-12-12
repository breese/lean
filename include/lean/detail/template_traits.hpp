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
