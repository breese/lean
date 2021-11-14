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
#include <lean/function_traits.hpp>

//-----------------------------------------------------------------------------

class cls;

//-----------------------------------------------------------------------------

namespace function_return_suite
{

static_assert(std::is_same<lean::function_return_t<bool()>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool &()>, bool &>{}, "");
static_assert(std::is_same<lean::function_return_t<bool && ()>, bool &&>{}, "");
static_assert(std::is_same<lean::function_return_t<const bool &()>, const bool &>{}, "");
static_assert(std::is_same<lean::function_return_t<const bool && ()>, const bool &&>{}, "");
static_assert(std::is_same<lean::function_return_t<bool *()>, bool *>{}, "");
static_assert(std::is_same<lean::function_return_t<const bool *()>, const bool *>{}, "");

static_assert(std::is_same<lean::function_return_t<int(bool, float)>, int>{}, "");
static_assert(std::is_same<lean::function_return_t<float(bool, int)>, float>{}, "");

static_assert(std::is_same<lean::function_return_t<bool() const>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool() const &>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool() const &&>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool() const volatile>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool() const volatile &>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool() const volatile &&>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool() volatile>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool() volatile &>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool() volatile &&>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool() &>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool() &&>, bool>{}, "");

} // namespace function_return_suite

//-----------------------------------------------------------------------------

namespace function_arguments_suite
{

template <typename...> struct argument_tuple;

static_assert(std::is_same<lean::function_arguments_t<argument_tuple, bool()>, argument_tuple<>>{}, "");
static_assert(std::is_same<lean::function_arguments_t<argument_tuple, bool(bool)>, argument_tuple<bool>>{}, "");
static_assert(std::is_same<lean::function_arguments_t<argument_tuple, bool(bool, int)>, argument_tuple<bool, int>>{}, "");
static_assert(std::is_same<lean::function_arguments_t<argument_tuple, bool(bool, int, float)>, argument_tuple<bool, int, float>>{}, "");

} // namespace function_arguments_suite

//-----------------------------------------------------------------------------

namespace is_function_const_suite
{

static_assert(!lean::is_function_const_t<bool()>{}, "");
static_assert( lean::is_function_const_t<bool() const>{}, "");
static_assert( lean::is_function_const_t<bool() const &>{}, "");
static_assert( lean::is_function_const_t<bool() const &&>{}, "");
static_assert( lean::is_function_const_t<bool() const volatile>{}, "");
static_assert( lean::is_function_const_t<bool() const volatile &>{}, "");
static_assert( lean::is_function_const_t<bool() const volatile &&>{}, "");
static_assert(!lean::is_function_const_t<bool() volatile>{}, "");
static_assert(!lean::is_function_const_t<bool() volatile &>{}, "");
static_assert(!lean::is_function_const_t<bool() volatile &&>{}, "");
static_assert(!lean::is_function_const_t<bool() &>{}, "");
static_assert(!lean::is_function_const_t<bool() &&>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(!lean::is_function_const_t<bool() noexcept>{}, "");
static_assert( lean::is_function_const_t<bool() const noexcept>{}, "");
static_assert( lean::is_function_const_t<bool() const & noexcept>{}, "");
static_assert( lean::is_function_const_t<bool() const && noexcept>{}, "");
static_assert( lean::is_function_const_t<bool() const volatile noexcept>{}, "");
static_assert( lean::is_function_const_t<bool() const volatile & noexcept>{}, "");
static_assert( lean::is_function_const_t<bool() const volatile && noexcept>{}, "");
static_assert(!lean::is_function_const_t<bool() volatile noexcept>{}, "");
static_assert(!lean::is_function_const_t<bool() volatile & noexcept>{}, "");
static_assert(!lean::is_function_const_t<bool() volatile && noexcept>{}, "");
static_assert(!lean::is_function_const_t<bool() & noexcept>{}, "");
static_assert(!lean::is_function_const_t<bool() && noexcept>{}, "");

#endif

static_assert(!lean::is_function_const_t<bool>{}, "");
static_assert(!lean::is_function_const_t<const bool>{}, "");
static_assert(!lean::is_function_const_t<bool *>{}, "");
static_assert(!lean::is_function_const_t<bool * const>{}, "");
static_assert(!lean::is_function_const_t<const bool *>{}, "");

} // namespace is_function_const_suite

//-----------------------------------------------------------------------------

namespace is_function_volatile_suite
{

static_assert(!lean::is_function_volatile_t<bool()>{}, "");
static_assert(!lean::is_function_volatile_t<bool() const>{}, "");
static_assert(!lean::is_function_volatile_t<bool() const &>{}, "");
static_assert(!lean::is_function_volatile_t<bool() const &&>{}, "");
static_assert( lean::is_function_volatile_t<bool() const volatile>{}, "");
static_assert( lean::is_function_volatile_t<bool() const volatile &>{}, "");
static_assert( lean::is_function_volatile_t<bool() const volatile &&>{}, "");
static_assert( lean::is_function_volatile_t<bool() volatile>{}, "");
static_assert( lean::is_function_volatile_t<bool() volatile &>{}, "");
static_assert( lean::is_function_volatile_t<bool() volatile &&>{}, "");
static_assert(!lean::is_function_volatile_t<bool() &>{}, "");
static_assert(!lean::is_function_volatile_t<bool() &&>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(!lean::is_function_volatile_t<bool() noexcept>{}, "");
static_assert(!lean::is_function_volatile_t<bool() const noexcept>{}, "");
static_assert(!lean::is_function_volatile_t<bool() const & noexcept>{}, "");
static_assert(!lean::is_function_volatile_t<bool() const && noexcept>{}, "");
static_assert( lean::is_function_volatile_t<bool() const volatile noexcept>{}, "");
static_assert( lean::is_function_volatile_t<bool() const volatile & noexcept>{}, "");
static_assert( lean::is_function_volatile_t<bool() const volatile && noexcept>{}, "");
static_assert( lean::is_function_volatile_t<bool() volatile noexcept>{}, "");
static_assert( lean::is_function_volatile_t<bool() volatile & noexcept>{}, "");
static_assert( lean::is_function_volatile_t<bool() volatile && noexcept>{}, "");
static_assert(!lean::is_function_volatile_t<bool() & noexcept>{}, "");
static_assert(!lean::is_function_volatile_t<bool() && noexcept>{}, "");

#endif

static_assert(!lean::is_function_volatile_t<bool>{}, "");
static_assert(!lean::is_function_volatile_t<volatile bool>{}, "");
static_assert(!lean::is_function_volatile_t<bool *>{}, "");
static_assert(!lean::is_function_volatile_t<bool * volatile>{}, "");
static_assert(!lean::is_function_volatile_t<volatile bool *>{}, "");

} // namespace is_function_volatile_suite

//-----------------------------------------------------------------------------

namespace is_function_lvalue_reference_suite
{

static_assert(!lean::is_function_lvalue_reference_t<bool()>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool() const>{}, "");
static_assert( lean::is_function_lvalue_reference_t<bool() const &>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool() const &&>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool() const volatile>{}, "");
static_assert( lean::is_function_lvalue_reference_t<bool() const volatile &>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool() const volatile &&>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool() volatile>{}, "");
static_assert( lean::is_function_lvalue_reference_t<bool() volatile &>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool() volatile &&>{}, "");
static_assert( lean::is_function_lvalue_reference_t<bool() &>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool() &&>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(!lean::is_function_lvalue_reference_t<bool() noexcept>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool() const noexcept>{}, "");
static_assert( lean::is_function_lvalue_reference_t<bool() const & noexcept>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool() const && noexcept>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool() const volatile noexcept>{}, "");
static_assert( lean::is_function_lvalue_reference_t<bool() const volatile & noexcept>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool() const volatile && noexcept>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool() volatile noexcept>{}, "");
static_assert( lean::is_function_lvalue_reference_t<bool() volatile & noexcept>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool() volatile && noexcept>{}, "");
static_assert( lean::is_function_lvalue_reference_t<bool() & noexcept>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool() && noexcept>{}, "");

#endif

static_assert(!lean::is_function_lvalue_reference_t<bool>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool&>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool&&>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<const bool>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<const bool&>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<const bool&&>{}, "");

} // namespace is_function_lvalue_reference_suite

//-----------------------------------------------------------------------------

namespace is_function_rvalue_reference_suite
{

static_assert(!lean::is_function_rvalue_reference_t<bool()>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool() const>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool() const &>{}, "");
static_assert( lean::is_function_rvalue_reference_t<bool() const &&>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool() const volatile>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool() const volatile &>{}, "");
static_assert( lean::is_function_rvalue_reference_t<bool() const volatile &&>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool() volatile>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool() volatile &>{}, "");
static_assert( lean::is_function_rvalue_reference_t<bool() volatile &&>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool() &>{}, "");
static_assert( lean::is_function_rvalue_reference_t<bool() &&>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(!lean::is_function_rvalue_reference_t<bool() noexcept>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool() const noexcept>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool() const & noexcept>{}, "");
static_assert( lean::is_function_rvalue_reference_t<bool() const && noexcept>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool() const volatile noexcept>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool() const volatile & noexcept>{}, "");
static_assert( lean::is_function_rvalue_reference_t<bool() const volatile && noexcept>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool() volatile noexcept>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool() volatile & noexcept>{}, "");
static_assert( lean::is_function_rvalue_reference_t<bool() volatile && noexcept>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool() & noexcept>{}, "");
static_assert( lean::is_function_rvalue_reference_t<bool() && noexcept>{}, "");

#endif

static_assert(!lean::is_function_rvalue_reference_t<bool>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool&>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool&&>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<const bool>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<const bool&>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<const bool&&>{}, "");

} // namespace is_function_rvalue_reference_suite

//-----------------------------------------------------------------------------

namespace is_function_reference_suite
{

static_assert(!lean::is_function_reference_t<bool()>{}, "");
static_assert(!lean::is_function_reference_t<bool() const>{}, "");
static_assert( lean::is_function_reference_t<bool() const &>{}, "");
static_assert( lean::is_function_reference_t<bool() const &&>{}, "");
static_assert(!lean::is_function_reference_t<bool() const volatile>{}, "");
static_assert( lean::is_function_reference_t<bool() const volatile &>{}, "");
static_assert( lean::is_function_reference_t<bool() const volatile &&>{}, "");
static_assert(!lean::is_function_reference_t<bool() volatile>{}, "");
static_assert( lean::is_function_reference_t<bool() volatile &>{}, "");
static_assert( lean::is_function_reference_t<bool() volatile &&>{}, "");
static_assert( lean::is_function_reference_t<bool() &>{}, "");
static_assert( lean::is_function_reference_t<bool() &&>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(!lean::is_function_reference_t<bool() noexcept>{}, "");
static_assert(!lean::is_function_reference_t<bool() const noexcept>{}, "");
static_assert( lean::is_function_reference_t<bool() const & noexcept>{}, "");
static_assert( lean::is_function_reference_t<bool() const && noexcept>{}, "");
static_assert(!lean::is_function_reference_t<bool() const volatile noexcept>{}, "");
static_assert( lean::is_function_reference_t<bool() const volatile & noexcept>{}, "");
static_assert( lean::is_function_reference_t<bool() const volatile && noexcept>{}, "");
static_assert(!lean::is_function_reference_t<bool() volatile noexcept>{}, "");
static_assert( lean::is_function_reference_t<bool() volatile & noexcept>{}, "");
static_assert( lean::is_function_reference_t<bool() volatile && noexcept>{}, "");
static_assert( lean::is_function_reference_t<bool() & noexcept>{}, "");
static_assert( lean::is_function_reference_t<bool() && noexcept>{}, "");

#endif

static_assert(!lean::is_function_reference_t<bool>{}, "");
static_assert(!lean::is_function_reference_t<bool&>{}, "");
static_assert(!lean::is_function_reference_t<bool&&>{}, "");
static_assert(!lean::is_function_reference_t<const bool>{}, "");
static_assert(!lean::is_function_reference_t<const bool&>{}, "");
static_assert(!lean::is_function_reference_t<const bool&&>{}, "");

} // namespace is_function_reference_suite

//-----------------------------------------------------------------------------

namespace remove_function_const_suite
{

static_assert(std::is_same<lean::remove_function_const_t<bool()>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() const>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() const &>, bool() &>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() const &&>, bool() &&>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() const volatile>, bool() volatile>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() const volatile &>, bool() volatile &>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() const volatile &&>, bool() volatile &&>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() volatile>, bool() volatile>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() volatile &>, bool() volatile &>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() volatile &&>, bool() volatile &&>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() &>, bool() &>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() &&>, bool() &&>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<lean::remove_function_const_t<bool() noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() const noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() const & noexcept>, bool() & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() const && noexcept>, bool() && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() const volatile noexcept>, bool() volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() const volatile & noexcept>, bool() volatile & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() const volatile && noexcept>, bool() volatile && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() volatile noexcept>, bool() volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() volatile & noexcept>, bool() volatile & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() volatile && noexcept>, bool() volatile && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() & noexcept>, bool() & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool() && noexcept>, bool() && noexcept>{}, "");

#endif

static_assert(std::is_same<lean::remove_function_const_t<bool(cls::*)()>, bool(cls::*)()>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(cls::*)() const>, bool(cls::*)() const>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(cls::*)() volatile>, bool(cls::*)() volatile>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(cls::*)() &>, bool(cls::*)() &>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(cls::*)() &&>, bool(cls::*)() &&>{}, "");

static_assert(std::is_same<lean::remove_function_const_t<bool>, bool>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<const bool>, const bool>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool *>, bool *>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool * const>, bool * const>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<const bool *>, const bool *>{}, "");

} // namespace remove_function_const_suite

//-----------------------------------------------------------------------------

namespace remove_function_volatile_suite
{

static_assert(std::is_same<lean::remove_function_volatile_t<bool()>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() const>, bool() const>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() const &>, bool() const &>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() const &&>, bool() const &&>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() const volatile>, bool() const>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() const volatile &>, bool() const &>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() const volatile &&>, bool() const &&>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() volatile>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() volatile &>, bool() &>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() volatile &&>, bool() &&>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() &>, bool() &>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() &&>, bool() &&>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<lean::remove_function_volatile_t<bool() noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() const noexcept>, bool() const noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() const & noexcept>, bool() const & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() const && noexcept>, bool() const && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() const volatile noexcept>, bool() const noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() const volatile & noexcept>, bool() const & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() const volatile && noexcept>, bool() const && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() volatile noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() volatile & noexcept>, bool() & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() volatile && noexcept>, bool() && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() & noexcept>, bool() & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool() && noexcept>, bool() && noexcept>{}, "");

#endif

static_assert(std::is_same<lean::remove_function_volatile_t<bool(cls::*)()>, bool(cls::*)()>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(cls::*)() const>, bool(cls::*)() const>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(cls::*)() volatile>, bool(cls::*)() volatile>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(cls::*)() &>, bool(cls::*)() &>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(cls::*)() &&>, bool(cls::*)() &&>{}, "");

static_assert(std::is_same<lean::remove_function_volatile_t<bool>, bool>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<const bool>, const bool>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool *>, bool *>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool * const>, bool * const>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<const bool *>, const bool *>{}, "");

} // namespace remove_function_volatile_suite

//-----------------------------------------------------------------------------

namespace remove_function_cv_suite
{

static_assert(std::is_same<lean::remove_function_cv_t<bool()>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() const>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() const &>, bool() &>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() const &&>, bool() &&>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() const volatile>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() const volatile &>, bool() &>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() const volatile &&>, bool() &&>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() volatile>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() volatile &>, bool() &>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() volatile &&>, bool() &&>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() &>, bool() &>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() &&>, bool() &&>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<lean::remove_function_cv_t<bool() noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() const noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() const & noexcept>, bool() & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() const && noexcept>, bool() && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() const volatile noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() const volatile & noexcept>, bool() & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() const volatile && noexcept>, bool() && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() volatile noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() volatile & noexcept>, bool() & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() volatile && noexcept>, bool() && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() & noexcept>, bool() & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool() && noexcept>, bool() && noexcept>{}, "");

#endif

static_assert(std::is_same<lean::remove_function_cv_t<bool(cls::*)()>, bool(cls::*)()>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(cls::*)() const>, bool(cls::*)() const>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(cls::*)() volatile>, bool(cls::*)() volatile>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(cls::*)() &>, bool(cls::*)() &>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(cls::*)() &&>, bool(cls::*)() &&>{}, "");

static_assert(std::is_same<lean::remove_function_cv_t<bool>, bool>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<const bool>, const bool>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool *>, bool *>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool * const>, bool * const>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<const bool *>, const bool *>{}, "");

} // namespace remove_function_cv_suite

//-----------------------------------------------------------------------------

namespace remove_function_reference_suite
{

static_assert(std::is_same<lean::remove_function_reference_t<bool()>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() const>, bool() const>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() const &>, bool() const>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() const &&>, bool() const>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() const volatile>, bool() const volatile>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() const volatile &>, bool() const volatile>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() const volatile &&>, bool() const volatile>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() volatile>, bool() volatile>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() volatile &>, bool() volatile>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() volatile &&>, bool() volatile>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() &>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() &&>, bool()>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<lean::remove_function_reference_t<bool() noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() const noexcept>, bool() const noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() const & noexcept>, bool() const noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() const && noexcept>, bool() const noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() const volatile noexcept>, bool() const volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() const volatile & noexcept>, bool() const volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() const volatile && noexcept>, bool() const volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() volatile noexcept>, bool() volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() volatile & noexcept>, bool() volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() volatile && noexcept>, bool() volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() & noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool() && noexcept>, bool() noexcept>{}, "");

#endif

static_assert(std::is_same<lean::remove_function_reference_t<bool(cls::*)()>, bool(cls::*)()>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(cls::*)() const>, bool(cls::*)() const>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(cls::*)() volatile>, bool(cls::*)() volatile>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(cls::*)() &>, bool(cls::*)() &>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(cls::*)() &&>, bool(cls::*)() &&>{}, "");

static_assert(std::is_same<lean::remove_function_reference_t<bool>, bool>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<const bool>, const bool>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool *>, bool *>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool * const>, bool * const>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<const bool *>, const bool *>{}, "");

} // namespace remove_function_reference_suite

//-----------------------------------------------------------------------------

namespace remove_function_cvref_suite
{

static_assert(std::is_same<lean::remove_function_cvref_t<bool()>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() const>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() const &>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() const &&>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() const volatile>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() const volatile &>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() const volatile &&>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() volatile>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() volatile &>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() volatile &&>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() &>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() &&>, bool()>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<lean::remove_function_cvref_t<bool() noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() const noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() const & noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() const && noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() const volatile noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() const volatile & noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() const volatile && noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() volatile noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() volatile & noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() volatile && noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() & noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool() && noexcept>, bool() noexcept>{}, "");

#endif

static_assert(std::is_same<lean::remove_function_cvref_t<bool(cls::*)()>, bool(cls::*)()>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(cls::*)() const>, bool(cls::*)() const>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(cls::*)() volatile>, bool(cls::*)() volatile>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(cls::*)() &>, bool(cls::*)() &>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(cls::*)() &&>, bool(cls::*)() &&>{}, "");

static_assert(std::is_same<lean::remove_function_cvref_t<bool>, bool>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<const bool>, const bool>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool *>, bool *>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool * const>, bool * const>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<const bool *>, const bool *>{}, "");

} // namespace remove_function_cvref_suite

//-----------------------------------------------------------------------------

int main()
{
    return 0;
}
