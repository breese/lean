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
#include <lean/type_traits.hpp>

//-----------------------------------------------------------------------------

struct trivial
{
    ~trivial() = default;
};

struct nontrivial
{
    ~nontrivial() {};
};

//-----------------------------------------------------------------------------

namespace type_identity_suite
{

static_assert(std::is_same<lean::type_identity_t<void>, void>(), "");

static_assert(std::is_same<lean::type_identity_t<int>, int>(), "");
static_assert(std::is_same<lean::type_identity_t<int&>, int&>(), "");
static_assert(std::is_same<lean::type_identity_t<int&&>, int&&>(), "");
static_assert(std::is_same<lean::type_identity_t<const int>, const int>(), "");
static_assert(std::is_same<lean::type_identity_t<const int&>, const int&>(), "");
static_assert(std::is_same<lean::type_identity_t<const int&&>, const int&&>(), "");

static_assert(!std::is_same<lean::type_identity_t<int>, void>(), "");
static_assert(!std::is_same<lean::type_identity_t<void>, int>(), "");

} // namespace type_identity_suite

//-----------------------------------------------------------------------------

namespace type_sizeof_suite
{

static_assert(lean::type_sizeof<int>() == sizeof(int), "");
static_assert(lean::type_sizeof<int&>() == sizeof(int&), "");
static_assert(lean::type_sizeof<int&&>() == sizeof(int&&), "");
static_assert(lean::type_sizeof<const int>() == sizeof(const int), "");
static_assert(lean::type_sizeof<const int&>() == sizeof(const int&), "");
static_assert(lean::type_sizeof<const int&&>() == sizeof(const int&&), "");

static_assert(lean::type_sizeof<int[2]>() == sizeof(int[2]), "");
static_assert(lean::type_sizeof<int[2]>() != sizeof(int[1]), "");

} // namespace type_sizeof_suite

//-----------------------------------------------------------------------------

namespace type_less_suite
{

template <std::size_t N>
using constant = lean::integral_constant<std::size_t, N>;

static_assert(!lean::type_less<constant<0>, constant<0>>(), "");
static_assert(!lean::type_less<constant<1>, constant<0>>(), "");
static_assert( lean::type_less<constant<0>, constant<1>>(), "");
static_assert(!lean::type_less<constant<1>, constant<1>>(), "");

static_assert(!lean::type_less_with<lean::type_sizeof, int[1], int[1]>(), "");
static_assert(!lean::type_less_with<lean::type_sizeof, int[2], int[1]>(), "");
static_assert( lean::type_less_with<lean::type_sizeof, int[1], int[2]>(), "");
static_assert(!lean::type_less_with<lean::type_sizeof, int[2], int[2]>(), "");

static_assert(!lean::type_less_with<lean::type_sizeof, int, int>(), "");

} // namespace type_less_suite

//-----------------------------------------------------------------------------

namespace type_greater_suite
{

template <std::size_t N>
using constant = lean::integral_constant<std::size_t, N>;

static_assert(!lean::type_greater<constant<0>, constant<0>>(), "");
static_assert( lean::type_greater<constant<1>, constant<0>>(), "");
static_assert(!lean::type_greater<constant<0>, constant<1>>(), "");
static_assert(!lean::type_greater<constant<1>, constant<1>>(), "");

static_assert(!lean::type_greater_with<lean::type_sizeof, int[1], int[1]>(), "");
static_assert( lean::type_greater_with<lean::type_sizeof, int[2], int[1]>(), "");
static_assert(!lean::type_greater_with<lean::type_sizeof, int[1], int[2]>(), "");
static_assert(!lean::type_greater_with<lean::type_sizeof, int[2], int[2]>(), "");

static_assert(!lean::type_greater_with<lean::type_sizeof, int, int>(), "");

} // namespace type_greater_suite

//-----------------------------------------------------------------------------

namespace is_mutable_reference_suite
{

static_assert(!lean::is_mutable_reference<int>::value, "no");
static_assert( lean::is_mutable_reference<int&>::value, "yes");
static_assert(!lean::is_mutable_reference<int&&>::value, "no");
static_assert(!lean::is_mutable_reference<const int>::value, "no");
static_assert(!lean::is_mutable_reference<const int&>::value, "no");
static_assert(!lean::is_mutable_reference<const int&&>::value, "no");

static_assert(!lean::is_mutable_reference<int[]>::value, "no");
static_assert( lean::is_mutable_reference<int(&)[]>::value, "yes");
static_assert(!lean::is_mutable_reference<int(&&)[]>::value, "no");
static_assert(!lean::is_mutable_reference<const int[]>::value, "no");
static_assert(!lean::is_mutable_reference<const int(&)[]>::value, "no");
static_assert(!lean::is_mutable_reference<const int(&&)[]>::value, "no");

static_assert(!lean::is_mutable_reference<int[4]>::value, "no");
static_assert( lean::is_mutable_reference<int(&)[4]>::value, "yes");
static_assert(!lean::is_mutable_reference<int(&&)[4]>::value, "no");
static_assert(!lean::is_mutable_reference<const int[4]>::value, "no");
static_assert(!lean::is_mutable_reference<const int(&)[4]>::value, "no");
static_assert(!lean::is_mutable_reference<const int(&&)[4]>::value, "no");

static_assert(!lean::is_mutable_reference<trivial>::value, "no");
static_assert( lean::is_mutable_reference<trivial&>::value, "yes");
static_assert(!lean::is_mutable_reference<trivial&&>::value, "no");
static_assert(!lean::is_mutable_reference<const trivial>::value, "no");
static_assert(!lean::is_mutable_reference<const trivial&>::value, "no");
static_assert(!lean::is_mutable_reference<const trivial&&>::value, "no");

static_assert(!lean::is_mutable_reference<trivial[]>::value, "no");
static_assert( lean::is_mutable_reference<trivial(&)[]>::value, "yes");
static_assert(!lean::is_mutable_reference<trivial(&&)[]>::value, "no");
static_assert(!lean::is_mutable_reference<const trivial[]>::value, "no");
static_assert(!lean::is_mutable_reference<const trivial(&)[]>::value, "no");
static_assert(!lean::is_mutable_reference<const trivial(&&)[]>::value, "no");

static_assert(!lean::is_mutable_reference<trivial[4]>::value, "no");
static_assert( lean::is_mutable_reference<trivial(&)[4]>::value, "yes");
static_assert(!lean::is_mutable_reference<trivial(&&)[4]>::value, "no");
static_assert(!lean::is_mutable_reference<const trivial[4]>::value, "no");
static_assert(!lean::is_mutable_reference<const trivial(&)[4]>::value, "no");
static_assert(!lean::is_mutable_reference<const trivial(&&)[4]>::value, "no");

static_assert(!lean::is_mutable_reference<nontrivial>::value, "no");
static_assert( lean::is_mutable_reference<nontrivial&>::value, "yes");
static_assert(!lean::is_mutable_reference<nontrivial&&>::value, "no");
static_assert(!lean::is_mutable_reference<const nontrivial>::value, "no");
static_assert(!lean::is_mutable_reference<const nontrivial&>::value, "no");
static_assert(!lean::is_mutable_reference<const nontrivial&&>::value, "no");

static_assert(!lean::is_mutable_reference<nontrivial[]>::value, "no");
static_assert( lean::is_mutable_reference<nontrivial(&)[]>::value, "yes");
static_assert(!lean::is_mutable_reference<nontrivial(&&)[]>::value, "no");
static_assert(!lean::is_mutable_reference<const nontrivial[]>::value, "no");
static_assert(!lean::is_mutable_reference<const nontrivial(&)[]>::value, "no");
static_assert(!lean::is_mutable_reference<const nontrivial(&&)[]>::value, "no");

static_assert(!lean::is_mutable_reference<nontrivial[4]>::value, "no");
static_assert( lean::is_mutable_reference<nontrivial(&)[4]>::value, "yes");
static_assert(!lean::is_mutable_reference<nontrivial(&&)[4]>::value, "no");
static_assert(!lean::is_mutable_reference<const nontrivial[4]>::value, "no");
static_assert(!lean::is_mutable_reference<const nontrivial(&)[4]>::value, "no");
static_assert(!lean::is_mutable_reference<const nontrivial(&&)[4]>::value, "no");

} // namespace is_mutable_reference_suite

//-----------------------------------------------------------------------------

namespace decay_forward_suite
{

static_assert(std::is_same<lean::decay_forward_t<int>, int>::value, "value");
static_assert(std::is_same<lean::decay_forward_t<int&>, int&>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<int&&>, int>::value, "value");
static_assert(std::is_same<lean::decay_forward_t<const int>, int>::value, "value");
static_assert(std::is_same<lean::decay_forward_t<const int&>, int>::value, "value");
static_assert(std::is_same<lean::decay_forward_t<const int&&>, int>::value, "value");

static_assert(std::is_same<lean::decay_forward_t<int[]>, int *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<int(&)[]>, int(&)[]>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<int(&&)[]>, int *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const int[]>, const int *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const int(&)[]>, const int *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const int(&&)[]>, const int *>::value, "pointer");

static_assert(std::is_same<lean::decay_forward_t<int[4]>, int *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<int(&)[4]>, int(&)[4]>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<int(&&)[4]>, int *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const int[4]>, const int *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const int(&)[4]>, const int *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const int(&&)[4]>, const int *>::value, "pointer");

static_assert(std::is_same<lean::decay_forward_t<int *>, int *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const int *>, const int *>::value, "pointer");

static_assert(std::is_same<lean::decay_forward_t<trivial>, trivial>::value, "value");
static_assert(std::is_same<lean::decay_forward_t<trivial&>, trivial&>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<trivial&&>, trivial>::value, "value");
static_assert(std::is_same<lean::decay_forward_t<const trivial>, trivial>::value, "value");
static_assert(std::is_same<lean::decay_forward_t<const trivial&>, trivial>::value, "value");
static_assert(std::is_same<lean::decay_forward_t<const trivial&&>, trivial>::value, "value");

static_assert(std::is_same<lean::decay_forward_t<trivial[]>, trivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<trivial(&)[]>, trivial(&)[]>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<trivial(&&)[]>, trivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const trivial[]>, const trivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const trivial(&)[]>, const trivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const trivial(&&)[]>, const trivial *>::value, "pointer");

static_assert(std::is_same<lean::decay_forward_t<trivial[4]>, trivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<trivial(&)[4]>, trivial(&)[4]>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<trivial(&&)[4]>, trivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const trivial[4]>, const trivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const trivial(&)[4]>, const trivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const trivial(&&)[4]>, const trivial *>::value, "pointer");

static_assert(std::is_same<lean::decay_forward_t<trivial *>, trivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const trivial *>, const trivial *>::value, "pointer");

static_assert(std::is_same<lean::decay_forward_t<nontrivial>, nontrivial&&>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<nontrivial&>, nontrivial&>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<nontrivial&&>, nontrivial&&>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial>, const  nontrivial&&>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial&>, const nontrivial&>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial&&>, const nontrivial&&>::value, "reference");

static_assert(std::is_same<lean::decay_forward_t<nontrivial[]>, nontrivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<nontrivial(&)[]>, nontrivial(&)[]>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<nontrivial(&&)[]>, nontrivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial[]>, const nontrivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial(&)[]>, const nontrivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial(&&)[]>, const nontrivial *>::value, "pointer");

static_assert(std::is_same<lean::decay_forward_t<nontrivial[4]>, nontrivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<nontrivial(&)[4]>, nontrivial(&)[4]>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<nontrivial(&&)[4]>, nontrivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial[4]>, const nontrivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial(&)[4]>, const nontrivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial(&&)[4]>, const nontrivial *>::value, "pointer");

static_assert(std::is_same<lean::decay_forward_t<nontrivial *>, nontrivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial *>, const nontrivial *>::value, "pointer");

} // namespace decay_forward_suite

//-----------------------------------------------------------------------------

int main()
{
    return 0;
}
