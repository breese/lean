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
#include <type_traits>
#include <lean/detail/function_type.hpp>

//-----------------------------------------------------------------------------

class my_class;

//-----------------------------------------------------------------------------

namespace type_suite
{

using lean::v1::detail::function_type_t;

static_assert(std::is_same<function_type_t<void()>, void()>::value, "");
static_assert(std::is_same<function_type_t<void() &>, void()>::value, "");
static_assert(std::is_same<function_type_t<void() &&>, void()>::value, "");

static_assert(std::is_same<function_type_t<void() const>, void() const>::value, "");
static_assert(std::is_same<function_type_t<void() const &>, void() const>::value, "");
static_assert(std::is_same<function_type_t<void() const &&>, void() const>::value, "");

static_assert(std::is_same<function_type_t<void(*)()>, void()>::value, "");
static_assert(std::is_same<function_type_t<void(&)()>, void()>::value, "");
static_assert(std::is_same<function_type_t<void(&&)()>, void()>::value, "");

static_assert(std::is_same<function_type_t<void(my_class::*)(), my_class *>, void()>::value, "");
static_assert(std::is_same<function_type_t<void(my_class::*)() &, my_class *>, void()>::value, "");
static_assert(std::is_same<function_type_t<void(my_class::*)() &&, my_class *>, void()>::value, "");

static_assert(std::is_same<function_type_t<void(my_class::*)() const, const my_class *>, void() const>::value, "");
static_assert(std::is_same<function_type_t<void(my_class::*)() const &, const my_class *>, void() const>::value, "");
static_assert(std::is_same<function_type_t<void(my_class::*)() const &&, const my_class *>, void() const>::value, "");

#if __cpp_noexcept_function_type

static_assert(std::is_same<function_type_t<void() noexcept>, void() noexcept>::value, "");
static_assert(std::is_same<function_type_t<void() & noexcept>, void() noexcept>::value, "");
static_assert(std::is_same<function_type_t<void() && noexcept>, void() noexcept>::value, "");

static_assert(std::is_same<function_type_t<void() const noexcept>, void() const noexcept>::value, "");
static_assert(std::is_same<function_type_t<void() const & noexcept>, void() const noexcept>::value, "");
static_assert(std::is_same<function_type_t<void() const && noexcept>, void() const noexcept>::value, "");

static_assert(std::is_same<function_type_t<void(*)() noexcept>, void() noexcept>::value, "");
static_assert(std::is_same<function_type_t<void(&)() noexcept>, void() noexcept>::value, "");
static_assert(std::is_same<function_type_t<void(&&)() noexcept>, void() noexcept>::value, "");

static_assert(std::is_same<function_type_t<void(my_class::*)() noexcept, my_class *>, void() noexcept>::value, "");
static_assert(std::is_same<function_type_t<void(my_class::*)() & noexcept, my_class *>, void() noexcept>::value, "");
static_assert(std::is_same<function_type_t<void(my_class::*)() && noexcept, my_class *>, void() noexcept>::value, "");

static_assert(std::is_same<function_type_t<void(my_class::*)() const noexcept, const my_class *>, void() const noexcept>::value, "");
static_assert(std::is_same<function_type_t<void(my_class::*)() const & noexcept, const my_class *>, void() const noexcept>::value, "");
static_assert(std::is_same<function_type_t<void(my_class::*)() const && noexcept, const my_class *>, void() const noexcept>::value, "");


#else

static_assert(std::is_same<function_type_t<void() noexcept>, void()>::value, "");
static_assert(std::is_same<function_type_t<void() & noexcept>, void()>::value, "");
static_assert(std::is_same<function_type_t<void() && noexcept>, void()>::value, "");

static_assert(std::is_same<function_type_t<void() const noexcept>, void() const>::value, "");
static_assert(std::is_same<function_type_t<void() const & noexcept>, void() const>::value, "");
static_assert(std::is_same<function_type_t<void() const && noexcept>, void() const>::value, "");

static_assert(std::is_same<function_type_t<void(*)() noexcept>, void()>::value, "");
static_assert(std::is_same<function_type_t<void(&)() noexcept>, void()>::value, "");
static_assert(std::is_same<function_type_t<void(&&)() noexcept>, void()>::value, "");

static_assert(std::is_same<function_type_t<void(my_class::*)() noexcept, my_class *>, void()>::value, "");
static_assert(std::is_same<function_type_t<void(my_class::*)() & noexcept, my_class *>, void()>::value, "");
static_assert(std::is_same<function_type_t<void(my_class::*)() && noexcept, my_class *>, void()>::value, "");

static_assert(std::is_same<function_type_t<void(my_class::*)() const noexcept, const my_class *>, void() const>::value, "");
static_assert(std::is_same<function_type_t<void(my_class::*)() const & noexcept, const my_class *>, void() const>::value, "");
static_assert(std::is_same<function_type_t<void(my_class::*)() const && noexcept, const my_class *>, void() const>::value, "");

#endif

// Trailing return type

static_assert(std::is_same<function_type_t<auto() -> void>, void()>::value, "");
static_assert(std::is_same<function_type_t<auto(*)() -> void>, void()>::value, "");
static_assert(std::is_same<function_type_t<auto(&)() -> void>, void()>::value, "");
static_assert(std::is_same<function_type_t<auto(&&)() -> void>, void()>::value, "");
static_assert(std::is_same<function_type_t<auto() const -> void>, void() const>::value, "");

} // namespace type_suite

//-----------------------------------------------------------------------------

namespace result_type_suite
{

using lean::v1::detail::result_type_t;

static_assert(std::is_same<result_type_t<void()>, void>::value, "");
static_assert(std::is_same<result_type_t<void() &>, void>::value, "");
static_assert(std::is_same<result_type_t<void() &&>, void>::value, "");

static_assert(std::is_same<result_type_t<void() const>, void>::value, "");
static_assert(std::is_same<result_type_t<void() const &>, void>::value, "");
static_assert(std::is_same<result_type_t<void() const &&>, void>::value, "");

static_assert(std::is_same<result_type_t<void(*)()>, void>::value, "");
static_assert(std::is_same<result_type_t<void(&)()>, void>::value, "");
static_assert(std::is_same<result_type_t<void(&&)()>, void>::value, "");

static_assert(std::is_same<result_type_t<void(my_class::*)(), my_class *>, void>::value, "");
static_assert(std::is_same<result_type_t<void(my_class::*)() &, my_class *>, void>::value, "");
static_assert(std::is_same<result_type_t<void(my_class::*)() &&, my_class *>, void>::value, "");

static_assert(std::is_same<result_type_t<void(my_class::*)() const, const my_class *>, void>::value, "");
static_assert(std::is_same<result_type_t<void(my_class::*)() const &, const my_class *>, void>::value, "");
static_assert(std::is_same<result_type_t<void(my_class::*)() const &&, const my_class *>, void>::value, "");

static_assert(std::is_same<result_type_t<void() noexcept>, void>::value, "");
static_assert(std::is_same<result_type_t<void() & noexcept>, void>::value, "");
static_assert(std::is_same<result_type_t<void() && noexcept>, void>::value, "");

static_assert(std::is_same<result_type_t<void() const noexcept>, void>::value, "");
static_assert(std::is_same<result_type_t<void() const & noexcept>, void>::value, "");
static_assert(std::is_same<result_type_t<void() const && noexcept>, void>::value, "");

static_assert(std::is_same<result_type_t<void(*)() noexcept>, void>::value, "");
static_assert(std::is_same<result_type_t<void(&)() noexcept>, void>::value, "");
static_assert(std::is_same<result_type_t<void(&&)() noexcept>, void>::value, "");

static_assert(std::is_same<result_type_t<void(my_class::*)() noexcept, my_class *>, void>::value, "");
static_assert(std::is_same<result_type_t<void(my_class::*)() & noexcept, my_class *>, void>::value, "");
static_assert(std::is_same<result_type_t<void(my_class::*)() && noexcept, my_class *>, void>::value, "");

static_assert(std::is_same<result_type_t<void(my_class::*)() const noexcept, const my_class *>, void>::value, "");
static_assert(std::is_same<result_type_t<void(my_class::*)() const & noexcept, const my_class *>, void>::value, "");
static_assert(std::is_same<result_type_t<void(my_class::*)() const && noexcept, const my_class *>, void>::value, "");

static_assert(std::is_same<result_type_t<auto() -> void>, void>::value, "");
static_assert(std::is_same<result_type_t<auto(*)() -> void>, void>::value, "");
static_assert(std::is_same<result_type_t<auto(&)() -> void>, void>::value, "");
static_assert(std::is_same<result_type_t<auto(&&)() -> void>, void>::value, "");
static_assert(std::is_same<result_type_t<auto() const -> void>, void>::value, "");

static_assert(std::is_same<result_type_t<void *()>, void *>::value, "");
static_assert(std::is_same<result_type_t<const void *()>, const void *>::value, "");

} // namespace result_type_suite

//-----------------------------------------------------------------------------

namespace is_noexcept_suite
{

using lean::v1::detail::is_noexcept;

static_assert(!is_noexcept<void()>::value, "");
static_assert(!is_noexcept<void() &>::value, "");
static_assert(!is_noexcept<void() &&>::value, "");

static_assert(!is_noexcept<void() const>::value, "");
static_assert(!is_noexcept<void() const &>::value, "");
static_assert(!is_noexcept<void() const &&>::value, "");

static_assert(!is_noexcept<void(*)()>::value, "");
static_assert(!is_noexcept<void(&)()>::value, "");
static_assert(!is_noexcept<void(&&)()>::value, "");

static_assert(!is_noexcept<void(my_class::*)(), my_class *>::value, "");
static_assert(!is_noexcept<void(my_class::*)() &, my_class *>::value, "");
static_assert(!is_noexcept<void(my_class::*)() &&, my_class *>::value, "");

static_assert(!is_noexcept<void(my_class::*)() const, const my_class *>::value, "");
static_assert(!is_noexcept<void(my_class::*)() const &, const my_class *>::value, "");
static_assert(!is_noexcept<void(my_class::*)() const &&, const my_class *>::value, "");

#if __cpp_noexcept_function_type

static_assert(is_noexcept<void() noexcept>::value, "");
static_assert(is_noexcept<void() & noexcept>::value, "");
static_assert(is_noexcept<void() && noexcept>::value, "");

static_assert(is_noexcept<void() const noexcept>::value, "");
static_assert(is_noexcept<void() const & noexcept>::value, "");
static_assert(is_noexcept<void() const && noexcept>::value, "");

static_assert(is_noexcept<void(*)() noexcept>::value, "");
static_assert(is_noexcept<void(&)() noexcept>::value, "");
static_assert(is_noexcept<void(&&)() noexcept>::value, "");

static_assert(is_noexcept<void(my_class::*)() noexcept, my_class *>::value, "");
static_assert(is_noexcept<void(my_class::*)() & noexcept, my_class *>::value, "");
static_assert(is_noexcept<void(my_class::*)() && noexcept, my_class *>::value, "");

static_assert(is_noexcept<void(my_class::*)() const noexcept, const my_class *>::value, "");
static_assert(is_noexcept<void(my_class::*)() const & noexcept, const my_class *>::value, "");
static_assert(is_noexcept<void(my_class::*)() const && noexcept, const my_class *>::value, "");

#else

static_assert(!is_noexcept<void() noexcept>::value, "");
static_assert(!is_noexcept<void() & noexcept>::value, "");
static_assert(!is_noexcept<void() && noexcept>::value, "");

static_assert(!is_noexcept<void() const noexcept>::value, "");
static_assert(!is_noexcept<void() const & noexcept>::value, "");
static_assert(!is_noexcept<void() const && noexcept>::value, "");

static_assert(!is_noexcept<void(*)() noexcept>::value, "");
static_assert(!is_noexcept<void(&)() noexcept>::value, "");
static_assert(!is_noexcept<void(&&)() noexcept>::value, "");

static_assert(!is_noexcept<void(my_class::*)() noexcept, my_class *>::value, "");
static_assert(!is_noexcept<void(my_class::*)() & noexcept, my_class *>::value, "");
static_assert(!is_noexcept<void(my_class::*)() && noexcept, my_class *>::value, "");

static_assert(!is_noexcept<void(my_class::*)() const noexcept, const my_class *>::value, "");
static_assert(!is_noexcept<void(my_class::*)() const & noexcept, const my_class *>::value, "");
static_assert(!is_noexcept<void(my_class::*)() const && noexcept, const my_class *>::value, "");

#endif

} // namespace is_noexcept_suite

//-----------------------------------------------------------------------------

namespace is_const_suite
{

using lean::v1::detail::is_const;

static_assert(!is_const<void()>::value, "");
static_assert(!is_const<void() &>::value, "");
static_assert(!is_const<void() &&>::value, "");

static_assert(is_const<void() const>::value, "");
static_assert(is_const<void() const &>::value, "");
static_assert(is_const<void() const &&>::value, "");

static_assert(!is_const<void(*)()>::value, "");
static_assert(!is_const<void(&)()>::value, "");
static_assert(!is_const<void(&&)()>::value, "");

static_assert(!is_const<void(my_class::*)(), my_class *>::value, "");
static_assert(!is_const<void(my_class::*)() &, my_class *>::value, "");
static_assert(!is_const<void(my_class::*)() &&, my_class *>::value, "");

static_assert(is_const<void(my_class::*)() const, const my_class *>::value, "");
static_assert(is_const<void(my_class::*)() const &, const my_class *>::value, "");
static_assert(is_const<void(my_class::*)() const &&, const my_class *>::value, "");

static_assert(!is_const<void() noexcept>::value, "");
static_assert(!is_const<void() & noexcept>::value, "");
static_assert(!is_const<void() && noexcept>::value, "");

static_assert(is_const<void() const noexcept>::value, "");
static_assert(is_const<void() const & noexcept>::value, "");
static_assert(is_const<void() const && noexcept>::value, "");

static_assert(!is_const<void(*)() noexcept>::value, "");
static_assert(!is_const<void(&)() noexcept>::value, "");
static_assert(!is_const<void(&&)() noexcept>::value, "");

static_assert(!is_const<void(my_class::*)() noexcept, my_class *>::value, "");
static_assert(!is_const<void(my_class::*)() & noexcept, my_class *>::value, "");
static_assert(!is_const<void(my_class::*)() && noexcept, my_class *>::value, "");

static_assert(is_const<void(my_class::*)() const noexcept, const my_class *>::value, "");
static_assert(is_const<void(my_class::*)() const & noexcept, const my_class *>::value, "");
static_assert(is_const<void(my_class::*)() const && noexcept, const my_class *>::value, "");

} // namespace is_const_suite

//-----------------------------------------------------------------------------

int main()
{
    return 0;
}
