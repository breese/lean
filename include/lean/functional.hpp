#ifndef LEAN_FUNCTIONAL_HPP
#define LEAN_FUNCTIONAL_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <lean/detail/invoke_traits.hpp>
#include <lean/type_traits.hpp>

namespace lean
{

#if __cpp_lib_constexpr_functional >= 201907L

using std::invoke;
using std::invoke_r;

#else

using v1::invoke;
using v1::invoke_r;

#endif

} // namespace lean

#endif // LEAN_FUNCTIONAL_HPP
