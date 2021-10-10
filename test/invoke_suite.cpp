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

#if __cpp_noexcept_function_type

constexpr bool noexcept_true(bool yes) { return yes; }

#else

// We are unable to detect noexcept if it not part of the function type
constexpr bool noexcept_true(bool yes) { return !yes; }

#endif

//-----------------------------------------------------------------------------

void function();
void function_noexcept() noexcept;

struct object {};
struct undefined_object;

struct function_object
{
    void invoke();
    void operator()();
};

auto lambda_const = [] {};
auto lambda_mutable = [] () mutable {};
auto lambda_const_noexcept = [] () noexcept {};
auto lambda_mutable_noexcept = [] () mutable noexcept {};

//-----------------------------------------------------------------------------
// invoke_result

namespace invoke_result_suite
{

using lean::invoke_result_t;

// Function

static_assert(std::is_same<invoke_result_t<void()>, void>::value, "");
static_assert(std::is_same<invoke_result_t<void(*)()>, void>::value, "");
static_assert(std::is_same<invoke_result_t<void(&)()>, void>::value, "");
static_assert(std::is_same<invoke_result_t<void(&&)()>, void>::value, "");

static_assert(std::is_same<invoke_result_t<int(short, long), short, long>, int>::value, "");
static_assert(std::is_same<invoke_result_t<int(*)(short, long), short, long>, int>::value, "");
static_assert(std::is_same<invoke_result_t<int(&)(short, long), short, long>, int>::value, "");
static_assert(std::is_same<invoke_result_t<int(&&)(short, long), short, long>, int>::value, "");

static_assert(std::is_same<invoke_result_t<decltype(function)>, void>::value, "");
static_assert(std::is_same<invoke_result_t<decltype(&function)>, void>::value, "");

static_assert(std::is_same<invoke_result_t<decltype(function_noexcept)>, void>::value, "");
static_assert(std::is_same<invoke_result_t<decltype(&function_noexcept)>, void>::value, "");

// Function object

static_assert(std::is_same<invoke_result_t<function_object>, void>::value, "");

static_assert(std::is_same<invoke_result_t<decltype(lambda_mutable)>, void>::value, "");
static_assert(std::is_same<invoke_result_t<decltype(lambda_const)>, void>::value, "");
static_assert(std::is_same<invoke_result_t<decltype(lambda_mutable_noexcept)>, void>::value, "");
static_assert(std::is_same<invoke_result_t<decltype(lambda_const_noexcept)>, void>::value, "");

// Member function

static_assert(std::is_same<invoke_result_t<void(function_object::*)(), function_object*>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)(), function_object&>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)(), function_object&&>, void>(), "");

static_assert(std::is_same<invoke_result_t<void(function_object::*)() &, function_object*>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() &, function_object&>, void>(), "");

static_assert(std::is_same<invoke_result_t<void(function_object::*)() &&, function_object&&>, void>(), "");

static_assert(std::is_same<invoke_result_t<void(function_object::*)() const, function_object*>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() const, function_object&>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() const, function_object&&>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() const, const function_object*>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() const, const function_object&>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() const, const function_object&&>, void>(), "");

static_assert(std::is_same<invoke_result_t<void(function_object::*)() const &, function_object*>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() const &, function_object&>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() const &, const function_object*>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() const &, const function_object&>, void>(), "");

static_assert(std::is_same<invoke_result_t<void(function_object::*)() const &&, function_object&&>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() const &&, const function_object&&>, void>(), "");

static_assert(std::is_same<invoke_result_t<void(function_object::*)() noexcept, function_object*>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() noexcept, function_object&>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() noexcept, function_object&&>, void>(), "");

static_assert(std::is_same<invoke_result_t<void(function_object::*)() & noexcept, function_object*>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() & noexcept, function_object&>, void>(), "");

static_assert(std::is_same<invoke_result_t<void(function_object::*)() && noexcept, function_object&&>, void>(), "");

static_assert(std::is_same<invoke_result_t<void(function_object::*)() const noexcept, function_object*>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() const noexcept, function_object&>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() const noexcept, function_object&&>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() const noexcept, const function_object*>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() const noexcept, const function_object&>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() const noexcept, const function_object&&>, void>(), "");

static_assert(std::is_same<invoke_result_t<void(function_object::*)() const & noexcept, function_object*>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() const & noexcept, function_object&>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() const & noexcept, const function_object*>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() const & noexcept, const function_object&>, void>(), "");

static_assert(std::is_same<invoke_result_t<void(function_object::*)() const && noexcept, function_object&&>, void>(), "");
static_assert(std::is_same<invoke_result_t<void(function_object::*)() const && noexcept, const function_object&&>, void>(), "");

} // namespace invoke_result_suite

//-----------------------------------------------------------------------------
// is_invocable

namespace is_invocable_suite
{

using lean::is_invocable;

// Function

static_assert(is_invocable<void()>(), "");
static_assert(is_invocable<void(*)()>(), "");
static_assert(is_invocable<void(&)()>(), "");
static_assert(is_invocable<void(&&)()>(), "");

static_assert(is_invocable<int(short, long), short, long>(), "");
static_assert(is_invocable<int(*)(short, long), short, long>(), "");
static_assert(is_invocable<int(&)(short, long), short, long>(), "");
static_assert(is_invocable<int(&&)(short, long), short, long>(), "");

static_assert(is_invocable<void() noexcept>(), "");
static_assert(is_invocable<void(*)() noexcept>(), "");
static_assert(is_invocable<void(&)() noexcept>(), "");
static_assert(is_invocable<void(&&)() noexcept>(), "");

static_assert(!is_invocable<void>(), "");
static_assert(!is_invocable<void() &>(), "");
static_assert(!is_invocable<void() &&>(), "");

// Function object

static_assert(!is_invocable<object>(), "");
static_assert(!is_invocable<undefined_object>(), "");
static_assert( is_invocable<function_object>(), "");

static_assert(is_invocable<decltype(lambda_mutable)>(), "");
static_assert(is_invocable<decltype(lambda_const)>(), "");
static_assert(is_invocable<decltype(lambda_mutable_noexcept)>(), "");
static_assert(is_invocable<decltype(lambda_const_noexcept)>(), "");

// Member function

static_assert( is_invocable<void(function_object::*)(), function_object*>(), "");
static_assert( is_invocable<void(function_object::*)(), function_object&>(), "");
static_assert( is_invocable<void(function_object::*)(), function_object&&>(), "");
static_assert(!is_invocable<void(function_object::*)(), const function_object*>(), "");
static_assert(!is_invocable<void(function_object::*)(), const function_object&>(), "");
static_assert(!is_invocable<void(function_object::*)(), const function_object&&>(), "");

static_assert( is_invocable<void(function_object::*)() &, function_object*>(), "");
static_assert( is_invocable<void(function_object::*)() &, function_object&>(), "");
static_assert(!is_invocable<void(function_object::*)() &, function_object&&>(), "");
static_assert(!is_invocable<void(function_object::*)() &, const function_object*>(), "");
static_assert(!is_invocable<void(function_object::*)() &, const function_object&>(), "");
static_assert(!is_invocable<void(function_object::*)() &, const function_object&&>(), "");

static_assert(!is_invocable<void(function_object::*)() &&, function_object*>(), "");
static_assert(!is_invocable<void(function_object::*)() &&, function_object&>(), "");
static_assert( is_invocable<void(function_object::*)() &&, function_object&&>(), "");
static_assert(!is_invocable<void(function_object::*)() &&, const function_object*>(), "");
static_assert(!is_invocable<void(function_object::*)() &&, const function_object&>(), "");
static_assert(!is_invocable<void(function_object::*)() &&, const function_object&&>(), "");

static_assert( is_invocable<void(function_object::*)() const, function_object *>(), "");
static_assert( is_invocable<void(function_object::*)() const, function_object&>(), "");
static_assert( is_invocable<void(function_object::*)() const, function_object&&>(), "");
static_assert( is_invocable<void(function_object::*)() const, const function_object *>(), "");
static_assert( is_invocable<void(function_object::*)() const, const function_object&>(), "");
static_assert( is_invocable<void(function_object::*)() const, const function_object&&>(), "");

static_assert( is_invocable<void(function_object::*)() const &, function_object *>(), "");
static_assert( is_invocable<void(function_object::*)() const &, function_object&>(), "");
static_assert(!is_invocable<void(function_object::*)() const &, function_object&&>(), "");
static_assert( is_invocable<void(function_object::*)() const &, const function_object *>(), "");
static_assert( is_invocable<void(function_object::*)() const &, const function_object&>(), "");
static_assert(!is_invocable<void(function_object::*)() const &, const function_object&&>(), "");

static_assert(!is_invocable<void(function_object::*)() const &&, function_object*>(), "");
static_assert(!is_invocable<void(function_object::*)() const &&, function_object&>(), "");
static_assert( is_invocable<void(function_object::*)() const &&, function_object&&>(), "");
static_assert(!is_invocable<void(function_object::*)() const &&, const function_object*>(), "");
static_assert(!is_invocable<void(function_object::*)() const &&, const function_object&>(), "");
static_assert( is_invocable<void(function_object::*)() const &&, const function_object&&>(), "");

static_assert( is_invocable<void(function_object::*)() noexcept, function_object*>(), "");
static_assert( is_invocable<void(function_object::*)() noexcept, function_object&>(), "");
static_assert( is_invocable<void(function_object::*)() noexcept, function_object&&>(), "");
static_assert(!is_invocable<void(function_object::*)() noexcept, const function_object*>(), "");
static_assert(!is_invocable<void(function_object::*)() noexcept, const function_object&>(), "");
static_assert(!is_invocable<void(function_object::*)() noexcept, const function_object&&>(), "");

static_assert( is_invocable<void(function_object::*)() & noexcept, function_object*>(), "");
static_assert( is_invocable<void(function_object::*)() & noexcept, function_object&>(), "");
static_assert(!is_invocable<void(function_object::*)() & noexcept, function_object&&>(), "");
static_assert(!is_invocable<void(function_object::*)() & noexcept, const function_object*>(), "");
static_assert(!is_invocable<void(function_object::*)() & noexcept, const function_object&>(), "");
static_assert(!is_invocable<void(function_object::*)() & noexcept, const function_object&&>(), "");

static_assert(!is_invocable<void(function_object::*)() && noexcept, function_object*>(), "");
static_assert(!is_invocable<void(function_object::*)() && noexcept, function_object&>(), "");
static_assert( is_invocable<void(function_object::*)() && noexcept, function_object&&>(), "");
static_assert(!is_invocable<void(function_object::*)() && noexcept, const function_object*>(), "");
static_assert(!is_invocable<void(function_object::*)() && noexcept, const function_object&>(), "");
static_assert(!is_invocable<void(function_object::*)() && noexcept, const function_object&&>(), "");

static_assert( is_invocable<void(function_object::*)() const noexcept, function_object *>(), "");
static_assert( is_invocable<void(function_object::*)() const noexcept, function_object&>(), "");
static_assert( is_invocable<void(function_object::*)() const noexcept, function_object&&>(), "");
static_assert( is_invocable<void(function_object::*)() const noexcept, const function_object *>(), "");
static_assert( is_invocable<void(function_object::*)() const noexcept, const function_object&>(), "");
static_assert( is_invocable<void(function_object::*)() const noexcept, const function_object&&>(), "");

static_assert( is_invocable<void(function_object::*)() const & noexcept, function_object *>(), "");
static_assert( is_invocable<void(function_object::*)() const & noexcept, function_object&>(), "");
static_assert(!is_invocable<void(function_object::*)() const & noexcept, function_object&&>(), "");
static_assert( is_invocable<void(function_object::*)() const & noexcept, const function_object *>(), "");
static_assert( is_invocable<void(function_object::*)() const & noexcept, const function_object&>(), "");
static_assert(!is_invocable<void(function_object::*)() const & noexcept, const function_object&&>(), "");

static_assert(!is_invocable<void(function_object::*)() const && noexcept, function_object*>(), "");
static_assert(!is_invocable<void(function_object::*)() const && noexcept, function_object&>(), "");
static_assert( is_invocable<void(function_object::*)() const && noexcept, function_object&&>(), "");
static_assert(!is_invocable<void(function_object::*)() const && noexcept, const function_object*>(), "");
static_assert(!is_invocable<void(function_object::*)() const && noexcept, const function_object&>(), "");
static_assert( is_invocable<void(function_object::*)() const && noexcept, const function_object&&>(), "");

} // namespace is_invocable_suite

//-----------------------------------------------------------------------------
// is_nothrow_invocable

namespace is_nothrow_invocable_suite
{

using lean::is_nothrow_invocable;

// Function

static_assert(!is_nothrow_invocable<void()>(), "");
static_assert(!is_nothrow_invocable<void(*)()>(), "");
static_assert(!is_nothrow_invocable<void(&)()>(), "");
static_assert(!is_nothrow_invocable<void(&&)()>(), "");

static_assert(!is_nothrow_invocable<int(short, long), short, long>(), "");
static_assert(!is_nothrow_invocable<int(*)(short, long), short, long>(), "");
static_assert(!is_nothrow_invocable<int(&)(short, long), short, long>(), "");
static_assert(!is_nothrow_invocable<int(&&)(short, long), short, long>(), "");

static_assert(noexcept_true(is_nothrow_invocable<void() noexcept>()), "");
static_assert(noexcept_true(is_nothrow_invocable<void(*)() noexcept>()), "");
static_assert(noexcept_true(is_nothrow_invocable<void(&)() noexcept>()), "");
static_assert(noexcept_true(is_nothrow_invocable<void(&&)() noexcept>()), "");

static_assert(!is_nothrow_invocable<void>(), "");
static_assert(!is_nothrow_invocable<void() &>(), "");
static_assert(!is_nothrow_invocable<void() &&>(), "");

// Function object

static_assert(!is_nothrow_invocable<object>(), "");
static_assert(!is_nothrow_invocable<undefined_object>(), "");
static_assert(!is_nothrow_invocable<function_object>(), "");

static_assert(!is_nothrow_invocable<decltype(lambda_mutable)>(), "");
static_assert(!is_nothrow_invocable<decltype(lambda_const)>(), "");
static_assert(noexcept_true(is_nothrow_invocable<decltype(lambda_mutable_noexcept)>()), "");
static_assert(noexcept_true(is_nothrow_invocable<decltype(lambda_const_noexcept)>()), "");

// Member function

static_assert(!is_nothrow_invocable<void(function_object::*)(), function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)(), function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)(), function_object&&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)(), const function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)(), const function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)(), const function_object&&>(), "");

static_assert(!is_nothrow_invocable<void(function_object::*)() &, function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() &, function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() &, function_object&&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() &, const function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() &, const function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() &, const function_object&&>(), "");

static_assert(!is_nothrow_invocable<void(function_object::*)() &&, function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() &&, function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() &&, function_object&&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() &&, const function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() &&, const function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() &&, const function_object&&>(), "");

static_assert(!is_nothrow_invocable<void(function_object::*)() const, function_object *>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const, function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const, function_object&&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const, const function_object *>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const, const function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const, const function_object&&>(), "");

static_assert(!is_nothrow_invocable<void(function_object::*)() const &, function_object *>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const &, function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const &, function_object&&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const &, const function_object *>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const &, const function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const &, const function_object&&>(), "");

static_assert(!is_nothrow_invocable<void(function_object::*)() const &&, function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const &&, function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const &&, function_object&&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const &&, const function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const &&, const function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const &&, const function_object&&>(), "");

static_assert(noexcept_true(is_nothrow_invocable<void(function_object::*)() noexcept, function_object*>()), "");
static_assert(noexcept_true(is_nothrow_invocable<void(function_object::*)() noexcept, function_object&>()), "");
static_assert(noexcept_true(is_nothrow_invocable<void(function_object::*)() noexcept, function_object&&>()), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() noexcept, const function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() noexcept, const function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() noexcept, const function_object&&>(), "");

static_assert(noexcept_true(is_nothrow_invocable<void(function_object::*)() & noexcept, function_object*>()), "");
static_assert(noexcept_true(is_nothrow_invocable<void(function_object::*)() & noexcept, function_object&>()), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() & noexcept, function_object&&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() & noexcept, const function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() & noexcept, const function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() & noexcept, const function_object&&>(), "");

static_assert(!is_nothrow_invocable<void(function_object::*)() && noexcept, function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() && noexcept, function_object&>(), "");
static_assert(noexcept_true(is_nothrow_invocable<void(function_object::*)() && noexcept, function_object&&>()), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() && noexcept, const function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() && noexcept, const function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() && noexcept, const function_object&&>(), "");

static_assert(noexcept_true(is_nothrow_invocable<void(function_object::*)() const noexcept, function_object *>()), "");
static_assert(noexcept_true(is_nothrow_invocable<void(function_object::*)() const noexcept, function_object&>()), "");
static_assert(noexcept_true(is_nothrow_invocable<void(function_object::*)() const noexcept, function_object&&>()), "");
static_assert(noexcept_true(is_nothrow_invocable<void(function_object::*)() const noexcept, const function_object *>()), "");
static_assert(noexcept_true(is_nothrow_invocable<void(function_object::*)() const noexcept, const function_object&>()), "");
static_assert(noexcept_true(is_nothrow_invocable<void(function_object::*)() const noexcept, const function_object&&>()), "");

static_assert(noexcept_true(is_nothrow_invocable<void(function_object::*)() const & noexcept, function_object *>()), "");
static_assert(noexcept_true(is_nothrow_invocable<void(function_object::*)() const & noexcept, function_object&>()), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const & noexcept, function_object&&>(), "");
static_assert(noexcept_true(is_nothrow_invocable<void(function_object::*)() const & noexcept, const function_object *>()), "");
static_assert(noexcept_true(is_nothrow_invocable<void(function_object::*)() const & noexcept, const function_object&>()), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const & noexcept, const function_object&&>(), "");

static_assert(!is_nothrow_invocable<void(function_object::*)() const && noexcept, function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const && noexcept, function_object&>(), "");
static_assert(noexcept_true(is_nothrow_invocable<void(function_object::*)() const && noexcept, function_object&&>()), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const && noexcept, const function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const && noexcept, const function_object&>(), "");
static_assert(noexcept_true(is_nothrow_invocable<void(function_object::*)() const && noexcept, const function_object&&>()), "");

} // namespace is_nothrow_invocable_suite

//-----------------------------------------------------------------------------

int main()
{
    (void)lambda_mutable;
    (void)lambda_const;
    (void)lambda_mutable_noexcept;
    (void)lambda_const_noexcept;

    return 0;
}
