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
#include <cstdarg>
#include <stdexcept>
#include <system_error>
#include <lean/throw.hpp>

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

} // namespace decay_forward_suite

//-----------------------------------------------------------------------------

namespace v1_throw_suite
{

void throw_bool()
{
    assert_throw_with((throw true), bool);
    assert_throw_with(lean::v1::throw_exception<bool>(true), \
                      bool);
}

void throw_logic_error()
{
    assert_throw_with(lean::v1::throw_exception<std::logic_error>("failure"), \
                      std::logic_error);
}

void throw_invalid_argument()
{
    assert_throw_with(lean::v1::throw_exception<std::invalid_argument>("failure"), \
                      std::invalid_argument);
}

void throw_domain_error()
{
    assert_throw_with(lean::v1::throw_exception<std::domain_error>("failure"), \
                      std::domain_error);
}

void throw_length_error()
{
    assert_throw_with(lean::v1::throw_exception<std::length_error>("failure"), \
                      std::length_error);
}

void throw_out_of_range()
{
    assert_throw_with(lean::v1::throw_exception<std::out_of_range>("failure"), \
                      std::out_of_range);
}

void throw_runtime_error()
{
    assert_throw_with(lean::v1::throw_exception<std::runtime_error>("failure"), \
                      std::runtime_error);
}

void throw_range_error()
{
    assert_throw_with(lean::v1::throw_exception<std::range_error>("failure"), \
                      std::range_error);
}

void throw_overflow_error()
{
    assert_throw_with(lean::v1::throw_exception<std::overflow_error>("failure"), \
                      std::overflow_error);
}

void throw_underflow_error()
{
    assert_throw_with(lean::v1::throw_exception<std::underflow_error>("failure"), \
                      std::underflow_error);
}

void throw_system_error()
{
    assert_throw_with((lean::v1::throw_exception<std::system_error>(int(std::errc::invalid_argument), std::generic_category())), \
                      std::system_error);
    assert_throw_with((lean::v1::throw_exception<std::system_error>(std::make_error_code(std::errc::invalid_argument))), \
                      std::system_error);
    assert_throw_with((lean::v1::throw_exception<std::system_error>(std::make_error_code(std::errc::invalid_argument), "failure")), \
                      std::system_error);
}

void run()
{
    throw_bool();
    throw_logic_error();
    throw_invalid_argument();
    throw_domain_error();
    throw_length_error();
    throw_out_of_range();
    throw_runtime_error();
    throw_range_error();
    throw_overflow_error();
    throw_underflow_error();
    throw_system_error();
}

} // namespace v1_throw_suite


//-----------------------------------------------------------------------------

struct ignored_error {};

struct returning_error {};

namespace lean { namespace v1 {

template <>
struct throw_traits<ignored_error>
{
    using result_type = void;

    template <typename... Args>
    static result_type invoke(Args&&...) {}
};

template <>
struct throw_traits<returning_error>
{
    using result_type = bool;

    template <typename... Args>
    static result_type invoke(Args&&...)
    {
        return false;
    }
};

}}

namespace v1_throw_traits_suite
{

void traits_ignored()
{
    assert_nothrow(lean::v1::throw_exception<ignored_error>());
}

void traits_returning()
{
    assert(!lean::v1::throw_exception<returning_error>());
}

void run()
{
    traits_ignored();
    traits_returning();
}

} // namespace v1_throw_traits_suite

//-----------------------------------------------------------------------------

int main()
{
    v1_throw_suite::run();
    v1_throw_traits_suite::run();
    return 0;
}
