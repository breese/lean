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
#include <functional>
#include <lean/detail/invoke_traits.hpp>

//-----------------------------------------------------------------------------

constexpr bool noexcept_true = !std::is_same<void(), void() noexcept>();

// Compilers disagree about invocation of const-ref qualified function on rvalue objects
#if defined(_MSC_VER)
constexpr bool invoke_xref = true;
#else
constexpr bool invoke_xref = false;
#endif

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

enum specifier
{
    specifier_mutable,
    specifier_const
};

struct mutable_function_object
{
    specifier operator()() { return specifier_mutable; }
    specifier invoke() { return specifier_mutable; }
    specifier lvalue_invoke() & { return specifier_mutable; }
    specifier rvalue_invoke() && { return specifier_mutable; }
};

struct const_function_object
{
    constexpr specifier operator()() const { return specifier_const; }
    constexpr specifier invoke() const { return specifier_const; }
    constexpr specifier lvalue_invoke() const & { return specifier_const; }
    constexpr specifier rvalue_invoke() const && { return specifier_const; }
};

//-----------------------------------------------------------------------------
// is_invocable

namespace is_invocable_suite
{

using lean::v1::is_invocable;

// Function

static_assert(is_invocable<void()>(), "");
static_assert(is_invocable<void(*)()>(), "");
static_assert(is_invocable<void(&)()>(), "");
static_assert(is_invocable<void(&&)()>(), "");

static_assert(is_invocable<int(short, long), short, long>(), "");
static_assert(is_invocable<int(*)(short, long), short, long>(), "");
static_assert(is_invocable<int(&)(short, long), short, long>(), "");
static_assert(is_invocable<int(&&)(short, long), short, long>(), "");

static_assert(is_invocable<int(const int&), const int&>(), "");
static_assert(is_invocable<int(const int&), int>(), "");
static_assert(is_invocable<int(const int&), short>(), "");

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

static_assert( is_invocable<void(function_object::*)(), function_object*>(), "pointer to object");
static_assert( is_invocable<void(function_object::*)(), function_object&>(), "");
static_assert( is_invocable<void(function_object::*)(), function_object&&>(), "");
static_assert( is_invocable<void(function_object::*)(), function_object * const>(), "const pointer to object");
static_assert(!is_invocable<void(function_object::*)(), function_object const *>(), "pointer to const object");
static_assert(!is_invocable<void(function_object::*)(), const function_object&>(), "");
static_assert(!is_invocable<void(function_object::*)(), const function_object&&>(), "");
static_assert(!is_invocable<void(function_object::*)(), function_object const * const>(), "const pointer to const object");

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
static_assert( is_invocable<void(function_object::*)() const &, function_object&&>() == invoke_xref, "");
static_assert( is_invocable<void(function_object::*)() const &, const function_object *>(), "");
static_assert( is_invocable<void(function_object::*)() const &, const function_object&>(), "");
static_assert( is_invocable<void(function_object::*)() const &, const function_object&&>() == invoke_xref, "");

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
static_assert( is_invocable<void(function_object::*)() const & noexcept, function_object&&>() == invoke_xref, "");
static_assert( is_invocable<void(function_object::*)() const & noexcept, const function_object *>(), "");
static_assert( is_invocable<void(function_object::*)() const & noexcept, const function_object&>(), "");
static_assert( is_invocable<void(function_object::*)() const & noexcept, const function_object&&>() == invoke_xref, "");

static_assert(!is_invocable<void(function_object::*)() const && noexcept, function_object*>(), "");
static_assert(!is_invocable<void(function_object::*)() const && noexcept, function_object&>(), "");
static_assert( is_invocable<void(function_object::*)() const && noexcept, function_object&&>(), "");
static_assert(!is_invocable<void(function_object::*)() const && noexcept, const function_object*>(), "");
static_assert(!is_invocable<void(function_object::*)() const && noexcept, const function_object&>(), "");
static_assert( is_invocable<void(function_object::*)() const && noexcept, const function_object&&>(), "");

static_assert( is_invocable<std::function<void()>>(), "");
static_assert( is_invocable<std::function<int(short, long)>, short, long>(), "");

} // namespace is_invocable_suite

//-----------------------------------------------------------------------------
// is_nothrow_invocable

namespace is_nothrow_invocable_suite
{

using lean::v1::is_nothrow_invocable;

// Function

static_assert(!is_nothrow_invocable<void()>(), "");
static_assert(!is_nothrow_invocable<void(*)()>(), "");
static_assert(!is_nothrow_invocable<void(&)()>(), "");
static_assert(!is_nothrow_invocable<void(&&)()>(), "");

static_assert(!is_nothrow_invocable<int(short, long), short, long>(), "");
static_assert(!is_nothrow_invocable<int(*)(short, long), short, long>(), "");
static_assert(!is_nothrow_invocable<int(&)(short, long), short, long>(), "");
static_assert(!is_nothrow_invocable<int(&&)(short, long), short, long>(), "");

static_assert(noexcept_true == is_nothrow_invocable<void() noexcept>(), "");
static_assert(noexcept_true == is_nothrow_invocable<void(*)() noexcept>(), "");
static_assert(noexcept_true == is_nothrow_invocable<void(&)() noexcept>(), "");
static_assert(noexcept_true == is_nothrow_invocable<void(&&)() noexcept>(), "");

static_assert(!is_nothrow_invocable<void>(), "");
static_assert(!is_nothrow_invocable<void() &>(), "");
static_assert(!is_nothrow_invocable<void() &&>(), "");

// Function object

static_assert(!is_nothrow_invocable<object>(), "");
static_assert(!is_nothrow_invocable<undefined_object>(), "");
static_assert(!is_nothrow_invocable<function_object>(), "");

static_assert(!is_nothrow_invocable<decltype(lambda_mutable)>(), "");
static_assert(!is_nothrow_invocable<decltype(lambda_const)>(), "");
// Oddly these works before C++17
static_assert( is_nothrow_invocable<decltype(lambda_mutable_noexcept)>(), "");
static_assert( is_nothrow_invocable<decltype(lambda_const_noexcept)>(), "");

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

static_assert(noexcept_true == is_nothrow_invocable<void(function_object::*)() noexcept, function_object*>(), "");
static_assert(noexcept_true == is_nothrow_invocable<void(function_object::*)() noexcept, function_object&>(), "");
static_assert(noexcept_true == is_nothrow_invocable<void(function_object::*)() noexcept, function_object&&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() noexcept, const function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() noexcept, const function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() noexcept, const function_object&&>(), "");

static_assert(noexcept_true == is_nothrow_invocable<void(function_object::*)() & noexcept, function_object*>(), "");
static_assert(noexcept_true == is_nothrow_invocable<void(function_object::*)() & noexcept, function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() & noexcept, function_object&&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() & noexcept, const function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() & noexcept, const function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() & noexcept, const function_object&&>(), "");

static_assert(!is_nothrow_invocable<void(function_object::*)() && noexcept, function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() && noexcept, function_object&>(), "");
static_assert(noexcept_true == is_nothrow_invocable<void(function_object::*)() && noexcept, function_object&&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() && noexcept, const function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() && noexcept, const function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() && noexcept, const function_object&&>(), "");

static_assert(noexcept_true == is_nothrow_invocable<void(function_object::*)() const noexcept, function_object *>(), "");
static_assert(noexcept_true == is_nothrow_invocable<void(function_object::*)() const noexcept, function_object&>(), "");
static_assert(noexcept_true == is_nothrow_invocable<void(function_object::*)() const noexcept, function_object&&>(), "");
static_assert(noexcept_true == is_nothrow_invocable<void(function_object::*)() const noexcept, const function_object *>(), "");
static_assert(noexcept_true == is_nothrow_invocable<void(function_object::*)() const noexcept, const function_object&>(), "");
static_assert(noexcept_true == is_nothrow_invocable<void(function_object::*)() const noexcept, const function_object&&>(), "");

static_assert(noexcept_true == is_nothrow_invocable<void(function_object::*)() const & noexcept, function_object *>(), "");
static_assert(noexcept_true == is_nothrow_invocable<void(function_object::*)() const & noexcept, function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const & noexcept, function_object&&>(), "");
static_assert(noexcept_true == is_nothrow_invocable<void(function_object::*)() const & noexcept, const function_object *>(), "");
static_assert(noexcept_true == is_nothrow_invocable<void(function_object::*)() const & noexcept, const function_object&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const & noexcept, const function_object&&>(), "");

static_assert(!is_nothrow_invocable<void(function_object::*)() const && noexcept, function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const && noexcept, function_object&>(), "");
static_assert(noexcept_true == is_nothrow_invocable<void(function_object::*)() const && noexcept, function_object&&>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const && noexcept, const function_object*>(), "");
static_assert(!is_nothrow_invocable<void(function_object::*)() const && noexcept, const function_object&>(), "");
static_assert(noexcept_true == is_nothrow_invocable<void(function_object::*)() const && noexcept, const function_object&&>(), "");

static_assert(!is_nothrow_invocable<std::function<void()>>(), "");
static_assert(!is_nothrow_invocable<std::function<int(short, long)>, short, long>(), "");

} // namespace is_nothrow_invocable_suite

//-----------------------------------------------------------------------------
// invoke_result

namespace invoke_result_suite
{

using lean::v1::invoke_result_t;

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

static_assert(std::is_same<invoke_result_t<std::function<void()>>, void>(), "");
static_assert(std::is_same<invoke_result_t<std::function<int()>>, int>(), "");
static_assert(std::is_same<invoke_result_t<std::function<int(short)>, short>, int>(), "");
static_assert(std::is_same<invoke_result_t<std::function<int(short)>, int>, int>(), "");
static_assert(std::is_same<invoke_result_t<std::function<int(short, long)>, short, long>, int>(), "");
static_assert(std::is_same<invoke_result_t<std::function<int(short, long)>, int, int>, int>(), "");

} // namespace invoke_result_suite

//-----------------------------------------------------------------------------

namespace invoke_suite
{

static_assert(lean::v1::invoke(&const_function_object::invoke, const_function_object{}) == specifier_const, "");

void invoke_mutable_function_object()
{
    {
        mutable_function_object object;
        assert(lean::v1::invoke(object) == specifier_mutable);
    }
    {
        mutable_function_object object;
        assert(lean::v1::invoke(std::move(object)) == specifier_mutable);
    }
    {
        mutable_function_object object;
        assert(lean::v1::invoke(&decltype(object)::operator(), object) == specifier_mutable);
    }
    {
        mutable_function_object object;
        assert(lean::v1::invoke(&decltype(object)::invoke, object) == specifier_mutable);
    }
    {
        mutable_function_object object;
        assert(lean::v1::invoke(&decltype(object)::invoke, std::move(object)) == specifier_mutable);
    }
    {
        mutable_function_object object;
        decltype(object) *ptr = &object;
        assert(lean::v1::invoke(&decltype(object)::invoke, ptr) == specifier_mutable);
    }
    {
        mutable_function_object object;
        decltype(object) * const ptr = &object;
        assert(lean::v1::invoke(&decltype(object)::invoke, ptr) == specifier_mutable);
    }
#if 0 // Must fail to compile
    {
        mutable_function_object object;
        const decltype(object) *ptr = &object;
        assert(lean::v1::invoke(&decltype(object)::invoke, ptr) == specifier_mutable);
    }
    {
        mutable_function_object object;
        const decltype(object) * const ptr = &object;
        assert(lean::v1::invoke(&decltype(object)::invoke, ptr) == specifier_mutable);
    }
#endif
}

void invoke_const_function_object()
{
    {
        const_function_object object;
        assert(lean::v1::invoke(object) == specifier_const);
    }
    {
        const_function_object object;
        assert(lean::v1::invoke(std::move(object)) == specifier_const);
    }
    {
        const_function_object object;
        assert(lean::v1::invoke(&decltype(object)::operator(), object) == specifier_const);
    }
    {
        const_function_object object;
        assert(lean::v1::invoke(&decltype(object)::invoke, object) == specifier_const);
    }
    {
        const_function_object object;
        assert(lean::v1::invoke(&decltype(object)::invoke, std::move(object)) == specifier_const);
    }
    {
        const_function_object object;
        decltype(object) *ptr = &object;
        assert(lean::v1::invoke(&decltype(object)::invoke, ptr) == specifier_const);
    }
    {
        const_function_object object;
        decltype(object) * const ptr = &object;
        assert(lean::v1::invoke(&decltype(object)::invoke, ptr) == specifier_const);
    }
    {
        const_function_object object;
        const decltype(object) *ptr = &object;
        assert(lean::v1::invoke(&decltype(object)::invoke, ptr) == specifier_const);
    }
    {
        const_function_object object;
        const decltype(object) * const ptr = &object;
        assert(lean::v1::invoke(&decltype(object)::invoke, ptr) == specifier_const);
    }
}

void invoke_arithmetic()
{
    assert(lean::v1::invoke(std::plus<int>{}, 20, 2) == 22);
    assert(lean::v1::invoke(std::minus<int>{}, 20, 2) == 18);
    assert(lean::v1::invoke(std::multiplies<int>{}, 20, 2) == 40);
    assert(lean::v1::invoke(std::divides<int>{}, 20, 2) == 10);
    assert(lean::v1::invoke(std::modulus<int>{}, 20, 2) == 0);
    assert(lean::v1::invoke(std::negate<int>{}, 20) == -20);
}

void invoke_comparison()
{
    assert( lean::v1::invoke(std::equal_to<int>{}, 20, 20));
    assert(!lean::v1::invoke(std::equal_to<int>{}, 20, 2));
    assert(!lean::v1::invoke(std::less<int>{}, 20, 20));
    assert( lean::v1::invoke(std::less<int>{}, 2, 20));
    assert(!lean::v1::invoke(std::less<int>{}, 20, 2));
}

void run()
{
    invoke_mutable_function_object();
    invoke_const_function_object();
    invoke_arithmetic();
    invoke_comparison();
}

} // namespace invoke_suite

//-----------------------------------------------------------------------------

int main()
{
    (void)lambda_mutable;
    (void)lambda_const;
    (void)lambda_mutable_noexcept;
    (void)lambda_const_noexcept;

    invoke_suite::run();
    return 0;
}
