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

namespace exchange_suite
{

void exchange_int()
{
    int value = 42;
    auto original = lean::exchange(value, 43);
    assert(value == 43);
    assert(original == 42);
}

void exchange_trivial()
{
    trivial value_trivial;
    lean::exchange(value_trivial, trivial{});
}

void exchange_nontrivial()
{
    nontrivial value_nontrivial;
    lean::exchange(value_nontrivial, nontrivial{});
}

void run()
{
    exchange_int();
    exchange_trivial();
    exchange_nontrivial();
}

} // namespace exchange_suite

//-----------------------------------------------------------------------------

namespace integer_sequence_suite
{

static_assert(std::is_same<typename lean::integer_sequence<int>::value_type, int>::value, "");
static_assert(std::is_same<typename lean::integer_sequence<unsigned int>::value_type, unsigned int>::value, "");

static_assert(lean::integer_sequence<int>::size() == 0, "");
static_assert(lean::integer_sequence<int, 0>::size() == 1, "");
static_assert(lean::integer_sequence<int, 0, 1>::size() == 2, "");
static_assert(lean::integer_sequence<int, 0, 1, 2>::size() == 3, "");

static_assert(std::is_same<lean::make_integer_sequence<int, 0>, lean::integer_sequence<int>>::value, "");
static_assert(std::is_same<lean::make_integer_sequence<int, 1>, lean::integer_sequence<int, 0>>::value, "");
static_assert(std::is_same<lean::make_integer_sequence<int, 2>, lean::integer_sequence<int, 0, 1>>::value, "");
static_assert(std::is_same<lean::make_integer_sequence<int, 3>, lean::integer_sequence<int, 0, 1, 2>>::value, "");
static_assert(std::is_same<lean::make_integer_sequence<int, 4>, lean::integer_sequence<int, 0, 1, 2, 3>>::value, "");

} // namespace integer_sequence_suite

//-----------------------------------------------------------------------------

namespace index_sequence_suite
{

static_assert(std::is_same<typename lean::index_sequence<>::value_type, std::size_t>::value, "");

static_assert(lean::index_sequence<>::size() == 0, "");
static_assert(lean::index_sequence<0>::size() == 1, "");
static_assert(lean::index_sequence<0, 1>::size() == 2, "");
static_assert(lean::index_sequence<0, 1, 2>::size() == 3, "");

static_assert(std::is_same<lean::make_index_sequence<0>, lean::index_sequence<>>::value, "");
static_assert(std::is_same<lean::make_index_sequence<1>, lean::index_sequence<0>>::value, "");
static_assert(std::is_same<lean::make_index_sequence<2>, lean::index_sequence<0, 1>>::value, "");
static_assert(std::is_same<lean::make_index_sequence<3>, lean::index_sequence<0, 1, 2>>::value, "");
static_assert(std::is_same<lean::make_index_sequence<4>, lean::index_sequence<0, 1, 2, 3>>::value, "");

static_assert(std::is_same<lean::index_sequence_for<int>, lean::index_sequence<0>>::value, "");
static_assert(std::is_same<lean::index_sequence_for<int, unsigned>, lean::index_sequence<0, 1>>::value, "");
static_assert(std::is_same<lean::index_sequence_for<int, unsigned, float>, lean::index_sequence<0, 1, 2>>::value, "");

} // namespace index_sequence_suite

//-----------------------------------------------------------------------------

int main()
{
    exchange_suite::run();
    return 0;
}
