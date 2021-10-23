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

namespace fold_suite
{

template <std::size_t N>
using constant = lean::integral_constant<std::size_t, N>;

static_assert(std::is_same<pack_fold<pack<constant<1>>, type_less>, constant<1>>(), "");
static_assert(std::is_same<pack_fold<pack<constant<1>, constant<2>>, type_less>, constant<1>>(), "");

static_assert(std::is_same<pack_fold<pack<constant<1>, constant<2>, constant<3>>, type_less>, constant<1>>(), "");
static_assert(std::is_same<pack_fold<pack<constant<2>, constant<3>, constant<1>>, type_less>, constant<1>>(), "");
static_assert(std::is_same<pack_fold<pack<constant<3>, constant<1>, constant<2>>, type_less>, constant<1>>(), "");

static_assert(std::is_same<pack_fold<pack<constant<1>, constant<2>, constant<3>>, type_greater>, constant<3>>(), "");
static_assert(std::is_same<pack_fold<pack<constant<2>, constant<3>, constant<1>>, type_greater>, constant<3>>(), "");
static_assert(std::is_same<pack_fold<pack<constant<3>, constant<1>, constant<2>>, type_greater>, constant<3>>(), "");

template <typename Lhs, typename Rhs>
struct type_less_sizeof : public type_less_with<type_sizeof, Lhs, Rhs> {};

static_assert(std::is_same<pack_fold<pack<int[1]>, type_less_sizeof>, int[1]>(), "");
static_assert(std::is_same<pack_fold<pack<int[1], int[2]>, type_less_sizeof>, int[1]>(), "");

static_assert(std::is_same<pack_fold<pack<int[1], int[2], int[3]>, type_less_sizeof>, int[1]>(), "");
static_assert(std::is_same<pack_fold<pack<int[2], int[3], int[1]>, type_less_sizeof>, int[1]>(), "");
static_assert(std::is_same<pack_fold<pack<int[3], int[1], int[2]>, type_less_sizeof>, int[1]>(), "");

} // namespace fold_suite

//-----------------------------------------------------------------------------

int main()
{
    return 0;
}
