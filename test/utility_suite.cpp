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
#include <lean/utility.hpp>

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

namespace decay_forward_suite
{

int value = 42;

static_assert(std::is_same<decltype(lean::decay_forward<int>(value)), int>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<int&>(value)), int&>::value, "reference");
static_assert(std::is_same<decltype(lean::decay_forward<int&&>(value)), int>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<const int>(value)), int>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<const int&>(value)), int>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<const int&&>(value)), int>::value, "value");

int& value_ref = value;

static_assert(std::is_same<decltype(lean::decay_forward<int>(value_ref)), int>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<int&>(value_ref)), int&>::value, "reference");
static_assert(std::is_same<decltype(lean::decay_forward<int&&>(value_ref)), int>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<const int>(value_ref)), int>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<const int&>(value_ref)), int>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<const int&&>(value_ref)), int>::value, "value");

int&& value_rref = [] { return value; }();

static_assert(std::is_same<decltype(lean::decay_forward<int>(value_rref)), int>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<int&>(value_rref)), int&>::value, "reference");
static_assert(std::is_same<decltype(lean::decay_forward<int&&>(value_rref)), int>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<const int>(value_rref)), int>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<const int&>(value_rref)), int>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<const int&&>(value_rref)), int>::value, "value");

const int cvalue = 42;

static_assert(std::is_same<decltype(lean::decay_forward<const int>(cvalue)), int>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<const int&>(cvalue)), int>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<const int&&>(cvalue)), int>::value, "value");

const int& cvalue_ref = value;

static_assert(std::is_same<decltype(lean::decay_forward<const int>(cvalue_ref)), int>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<const int&>(cvalue_ref)), int>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<const int&&>(cvalue_ref)), int>::value, "value");

const int&& cvalue_rref = [] { return cvalue; }();

static_assert(std::is_same<decltype(lean::decay_forward<const int>(cvalue_rref)), int>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<const int&>(cvalue_rref)), int>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<const int&&>(cvalue_rref)), int>::value, "value");

trivial value_trivial;

static_assert(std::is_same<decltype(lean::decay_forward<trivial>(value_trivial)), trivial>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<trivial&>(value_trivial)), trivial&>::value, "reference");
static_assert(std::is_same<decltype(lean::decay_forward<trivial&&>(value_trivial)), trivial>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<const trivial>(value_trivial)), trivial>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<const trivial&>(value_trivial)), trivial>::value, "value");
static_assert(std::is_same<decltype(lean::decay_forward<const trivial&&>(value_trivial)), trivial>::value, "value");

nontrivial value_nontrivial;

static_assert(std::is_same<decltype(lean::decay_forward<nontrivial>(value_nontrivial)), nontrivial&&>::value, "rvalue reference");
static_assert(std::is_same<decltype(lean::decay_forward<nontrivial&>(value_nontrivial)), nontrivial&>::value, "reference");
static_assert(std::is_same<decltype(lean::decay_forward<nontrivial&&>(value_nontrivial)), nontrivial&&>::value, "rvalue value");
static_assert(std::is_same<decltype(lean::decay_forward<const nontrivial>(value_nontrivial)), const nontrivial&&>::value, "rvalue reference");
static_assert(std::is_same<decltype(lean::decay_forward<const nontrivial&>(value_nontrivial)), const nontrivial&>::value, "reference");
static_assert(std::is_same<decltype(lean::decay_forward<const nontrivial&&>(value_nontrivial)), const nontrivial&&>::value, "rvalue reference");

} // namespace decay_forward_suite

//-----------------------------------------------------------------------------

int main()
{
    return 0;
}
