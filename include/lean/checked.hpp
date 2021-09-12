#ifndef LEAN_CHECKED_HPP
#define LEAN_CHECKED_HPP

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
#include <lean/detail/config.hpp>

// Invocation policy

namespace lean
{
namespace v1
{

struct unchecked {};

template <typename>
struct is_checked_policy : std::true_type {};

template <>
struct is_checked_policy<unchecked> : std::false_type {};

} // namespace v1

using v1::unchecked;
using v1::is_checked_policy;

} // namespace lean

#endif // LEAN_CHECKED_HPP
