///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <new> // std::nothrow_t
#include <lean/checked.hpp>

//-----------------------------------------------------------------------------

static_assert(lean::v1::is_checked_policy<void>::value, "");
static_assert(!lean::v1::is_checked_policy<lean::v1::unchecked>::value, "");

static_assert(lean::is_checked_policy<void>::value, "");
static_assert(!lean::is_checked_policy<lean::unchecked>::value, "");

//-----------------------------------------------------------------------------

namespace lean { namespace v1 {

template <>
struct is_checked_policy<std::nothrow_t> : std::false_type {};

}}

static_assert(!lean::v1::is_checked_policy<std::nothrow_t>::value, "");

//-----------------------------------------------------------------------------

int main()
{
    return 0;
}
