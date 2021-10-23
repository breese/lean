///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include "test_assert.hpp"
#include <lean/pack.hpp>

using namespace lean;

//-----------------------------------------------------------------------------

namespace front_suite
{

static_assert(std::is_same<pack_front<bool>, bool>(), "");
static_assert(std::is_same<pack_front<bool, int>, bool>(), "");
static_assert(std::is_same<pack_front<bool, int, float>, bool>(), "");

static_assert(std::is_same<pack_front<bool&>, bool&>(), "");
static_assert(std::is_same<pack_front<bool&&>, bool&&>(), "");
static_assert(std::is_same<pack_front<const bool&>, const bool&>(), "");

static_assert(std::is_same<pack_front<pack<bool>>, bool>(), "");
static_assert(std::is_same<pack_front<pack<bool, int>>, bool>(), "");
static_assert(std::is_same<pack_front<pack<bool, int, float>>, bool>(), "");

static_assert(std::is_same<pack_front<pack<bool&>>, bool&>(), "");
static_assert(std::is_same<pack_front<pack<bool&&>>, bool&&>(), "");
static_assert(std::is_same<pack_front<pack<const bool&>>, const bool&>(), "");

} // namespace front_suite

//-----------------------------------------------------------------------------

namespace contains_suite
{

static_assert(pack_contains<pack<bool>, bool>(), "");
static_assert(pack_contains<pack<bool, int>, bool>(), "");
static_assert(pack_contains<pack<int, bool>, bool>(), "");
static_assert(pack_contains<pack<bool, bool>, bool>(), "");

static_assert(!pack_contains<pack<bool>, float>(), "");
static_assert(!pack_contains<pack<bool, int>, float>(), "");

static_assert( pack_contains<pack<int>, int>(), "");
static_assert(!pack_contains<pack<int>, int&>(), "");
static_assert(!pack_contains<pack<int>, int&&>(), "");
static_assert(!pack_contains<pack<int>, const int>(), "");
static_assert(!pack_contains<pack<int>, const int&>(), "");
static_assert(!pack_contains<pack<int>, const int&&>(), "");

static_assert(!pack_contains<pack<int&, int&&, const int, const int&, const int&&>, int>(), "");
static_assert( pack_contains<pack<int&, int&&, const int, const int&, const int&&>, int&>(), "");
static_assert( pack_contains<pack<int&, int&&, const int, const int&, const int&&>, int&&>(), "");
static_assert( pack_contains<pack<int&, int&&, const int, const int&, const int&&>, const int>(), "");
static_assert( pack_contains<pack<int&, int&&, const int, const int&, const int&&>, const int&>(), "");
static_assert( pack_contains<pack<int&, int&&, const int, const int&, const int&&>, const int&&>(), "");

static_assert(!pack_contains<bool, bool>(), ""); // Must be pack<bool>

} // namespace contains_suite

//-----------------------------------------------------------------------------

int main()
{
    return 0;
}
