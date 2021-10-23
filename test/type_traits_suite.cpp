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
