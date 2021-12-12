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

struct function_object {
    void invoke();
    void operator()();
};

struct function_object_noexcept {
    void invoke() noexcept;
    void operator()() noexcept;
};

auto lambda_const = [] {};
auto lambda_mutable = [] () mutable {};
auto lambda_const_noexcept = [] () noexcept {};
auto lambda_mutable_noexcept = [] () mutable noexcept {};

//-----------------------------------------------------------------------------

namespace suite_function_type
{

// Function type

static_assert(std::is_same<lean::function_type_t<bool()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() const>, bool() const>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() const &>, bool() const &>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() const &&>, bool() const &&>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() const volatile>, bool() const volatile>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() const volatile &>, bool() const volatile &>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() const volatile &&>, bool() const volatile &&>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() volatile>, bool() volatile>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() volatile &>, bool() volatile &>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() volatile &&>, bool() volatile &&>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() &>, bool() &>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() &&>, bool() &&>{}, "");

static_assert(std::is_same<lean::function_type_t<bool(...)>, bool(...)>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) const>, bool(...) const>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) const &>, bool(...) const &>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) const &&>, bool(...) const &&>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) const volatile>, bool(...) const volatile>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) const volatile &>, bool(...) const volatile &>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) const volatile &&>, bool(...) const volatile &&>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) volatile>, bool(...) volatile>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) volatile &>, bool(...) volatile &>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) volatile &&>, bool(...) volatile &&>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) &>, bool(...) &>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) &&>, bool(...) &&>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<lean::function_type_t<bool() noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() const noexcept>, bool() const noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() const & noexcept>, bool() const & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() const && noexcept>, bool() const && noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() const volatile noexcept>, bool() const volatile noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() const volatile & noexcept>, bool() const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() const volatile && noexcept>, bool() const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() volatile noexcept>, bool() volatile noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() volatile & noexcept>, bool() volatile & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() volatile && noexcept>, bool() volatile && noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() & noexcept>, bool() & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool() && noexcept>, bool() && noexcept>{}, "");

static_assert(std::is_same<lean::function_type_t<bool(...) noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) const noexcept>, bool(...) const noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) const & noexcept>, bool(...) const & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) const && noexcept>, bool(...) const && noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) const volatile noexcept>, bool(...) const volatile noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) const volatile & noexcept>, bool(...) const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) const volatile && noexcept>, bool(...) const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) volatile noexcept>, bool(...) volatile noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) volatile & noexcept>, bool(...) volatile & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) volatile && noexcept>, bool(...) volatile && noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) & noexcept>, bool(...) & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool(...) && noexcept>, bool(...) && noexcept>{}, "");

#endif

// Function pointer and reference

static_assert(std::is_same<lean::function_type_t<bool (*)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (**)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (***)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (&)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (&&)()>, bool()>{}, "");

static_assert(std::is_same<lean::function_type_t<bool (*)(...)>, bool(...)>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (**)(...)>, bool(...)>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (***)(...)>, bool(...)>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (&)(...)>, bool(...)>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (&&)(...)>, bool(...)>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<lean::function_type_t<bool (*)() noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (**)() noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (***)() noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (&)() noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (&&)() noexcept>, bool() noexcept>{}, "");

static_assert(std::is_same<lean::function_type_t<bool (*)(...) noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (**)(...) noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (***)(...) noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (&)(...) noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (&&)(...) noexcept>, bool(...) noexcept>{}, "");

#endif

// Function pointer qualifiers

static_assert(std::is_same<lean::function_type_t<bool (* const)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (* const &)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (* const &&)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (* const volatile)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (* const volatile &)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (* const volatile &&)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (* volatile)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (* volatile &)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (* volatile &&)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (* &)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (* &&)()>, bool()>{}, "");

// Member function pointer

static_assert(std::is_same<lean::function_type_t<bool (cls::*)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() const>, bool() const>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() const &>, bool() const &>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() const &&>, bool() const &&>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() const volatile>, bool() const volatile>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() const volatile &>, bool() const volatile &>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() const volatile &&>, bool() const volatile &&>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() volatile>, bool() volatile>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() volatile &>, bool() volatile &>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() volatile &&>, bool() volatile &&>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() &>, bool() &>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() &&>, bool() &&>{}, "");

static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...)>, bool(...)>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) const>, bool(...) const>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) const &>, bool(...) const &>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) const &&>, bool(...) const &&>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) const volatile>, bool(...) const volatile>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) const volatile &>, bool(...) const volatile &>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) const volatile &&>, bool(...) const volatile &&>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) volatile>, bool(...) volatile>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) volatile &>, bool(...) volatile &>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) volatile &&>, bool(...) volatile &&>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) &>, bool(...) &>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) &&>, bool(...) &&>{}, "");

static_assert(std::is_same<lean::function_type_t<void (cls::*)(bool)>, void(bool)>{}, "");
static_assert(std::is_same<lean::function_type_t<void (cls::*)(bool, int)>, void(bool, int)>{}, "");
static_assert(std::is_same<lean::function_type_t<void (cls::*)(bool, int, float)>, void(bool, int, float)>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<lean::function_type_t<bool (cls::*)() noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() const noexcept>, bool() const noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() const & noexcept>, bool() const & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() const && noexcept>, bool() const && noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() const volatile noexcept>, bool() const volatile noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() const volatile & noexcept>, bool() const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() const volatile && noexcept>, bool() const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() volatile noexcept>, bool() volatile noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() volatile & noexcept>, bool() volatile & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() volatile && noexcept>, bool() volatile && noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() & noexcept>, bool() & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)() && noexcept>, bool() && noexcept>{}, "");

static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) const noexcept>, bool(...) const noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) const & noexcept>, bool(...) const & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) const && noexcept>, bool(...) const && noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) const volatile noexcept>, bool(...) const volatile noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) const volatile & noexcept>, bool(...) const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) const volatile && noexcept>, bool(...) const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) volatile noexcept>, bool(...) volatile noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) volatile & noexcept>, bool(...) volatile & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) volatile && noexcept>, bool(...) volatile && noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) & noexcept>, bool(...) & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*)(...) && noexcept>, bool(...) && noexcept>{}, "");

#endif

// Member function pointer qualifiers

static_assert(std::is_same<lean::function_type_t<bool (cls::*const)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*const &)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*const &&)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*const volatile)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*const volatile &)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*const volatile &&)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*volatile)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*volatile &)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*volatile &&)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*&)()>, bool()>{}, "");
static_assert(std::is_same<lean::function_type_t<bool (cls::*&&)()>, bool()>{}, "");

// Function object

static_assert(std::is_same<lean::function_type_t<function_object>, void()>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(&function_object::operator())>, void()>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(&function_object::invoke)>, void()>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(lambda_const)>, void() const>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(lambda_mutable)>, void()>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<lean::function_type_t<function_object_noexcept>, void() noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(&function_object_noexcept::operator())>, void() noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(&function_object_noexcept::invoke)>, void() noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(lambda_const_noexcept)>, void() const noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(lambda_mutable_noexcept)>, void() noexcept>{}, "");

#endif


} // namespace suite_function_type

//-----------------------------------------------------------------------------

namespace suite_function_return
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

static_assert(std::is_same<lean::function_return_t<bool(...) const>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool(...) const &>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool(...) const &&>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool(...) const volatile>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool(...) const volatile &>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool(...) const volatile &&>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool(...) volatile>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool(...) volatile &>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool(...) volatile &&>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool(...) &>, bool>{}, "");
static_assert(std::is_same<lean::function_return_t<bool(...) &&>, bool>{}, "");

} // namespace suite_function_return

//-----------------------------------------------------------------------------

namespace suite_function_arguments
{

template <typename...> struct argument_tuple;

static_assert(std::is_same<lean::function_arguments_t<argument_tuple, bool()>, argument_tuple<>>{}, "");
static_assert(std::is_same<lean::function_arguments_t<argument_tuple, bool(bool)>, argument_tuple<bool>>{}, "");
static_assert(std::is_same<lean::function_arguments_t<argument_tuple, bool(bool, int)>, argument_tuple<bool, int>>{}, "");
static_assert(std::is_same<lean::function_arguments_t<argument_tuple, bool(bool, int, float)>, argument_tuple<bool, int, float>>{}, "");

static_assert(std::is_same<lean::function_arguments_t<argument_tuple, bool(...)>, argument_tuple<>>{}, "");
static_assert(std::is_same<lean::function_arguments_t<argument_tuple, bool(bool, ...)>, argument_tuple<bool>>{}, "");
static_assert(std::is_same<lean::function_arguments_t<argument_tuple, bool(bool, int, ...)>, argument_tuple<bool, int>>{}, "");
static_assert(std::is_same<lean::function_arguments_t<argument_tuple, bool(bool, int, float, ...)>, argument_tuple<bool, int, float>>{}, "");

} // namespace suite_function_arguments

//-----------------------------------------------------------------------------

namespace suite_function_rebind
{

static_assert(std::is_same<lean::function_rebind_t<void(), int, lean::prototype<bool>>, int(bool)>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() const, int, lean::prototype<bool>>, int(bool) const>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() const &, int, lean::prototype<bool>>, int(bool) const &>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() const &&, int, lean::prototype<bool>>, int(bool) const &&>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() const volatile, int, lean::prototype<bool>>, int(bool) const volatile>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() const volatile &, int, lean::prototype<bool>>, int(bool) const volatile &>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() const volatile &&, int, lean::prototype<bool>>, int(bool) const volatile &&>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() volatile, int, lean::prototype<bool>>, int(bool) volatile>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() volatile &, int, lean::prototype<bool>>, int(bool) volatile &>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() volatile &&, int, lean::prototype<bool>>, int(bool) volatile &&>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() &, int, lean::prototype<bool>>, int(bool) &>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() &&, int, lean::prototype<bool>>, int(bool) &&>{}, "");

static_assert(std::is_same<lean::function_rebind_t<void(...), int, lean::prototype<bool>>, int(bool, ...)>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) const, int, lean::prototype<bool>>, int(bool, ...) const>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) const &, int, lean::prototype<bool>>, int(bool, ...) const &>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) const &&, int, lean::prototype<bool>>, int(bool, ...) const &&>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) const volatile, int, lean::prototype<bool>>, int(bool, ...) const volatile>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) const volatile &, int, lean::prototype<bool>>, int(bool, ...) const volatile &>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) const volatile &&, int, lean::prototype<bool>>, int(bool, ...) const volatile &&>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) volatile, int, lean::prototype<bool>>, int(bool, ...) volatile>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) volatile &, int, lean::prototype<bool>>, int(bool, ...) volatile &>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) volatile &&, int, lean::prototype<bool>>, int(bool, ...) volatile &&>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) &, int, lean::prototype<bool>>, int(bool, ...) &>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) &&, int, lean::prototype<bool>>, int(bool, ...) &&>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<lean::function_rebind_t<void() noexcept, int, lean::prototype<bool>>, int(bool) noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() const noexcept, int, lean::prototype<bool>>, int(bool) const noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() const & noexcept, int, lean::prototype<bool>>, int(bool) const & noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() const && noexcept, int, lean::prototype<bool>>, int(bool) const && noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() const volatile noexcept, int, lean::prototype<bool>>, int(bool) const volatile noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() const volatile & noexcept, int, lean::prototype<bool>>, int(bool) const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() const volatile && noexcept, int, lean::prototype<bool>>, int(bool) const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() volatile noexcept, int, lean::prototype<bool>>, int(bool) volatile noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() volatile & noexcept, int, lean::prototype<bool>>, int(bool) volatile & noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() volatile && noexcept, int, lean::prototype<bool>>, int(bool) volatile && noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() & noexcept, int, lean::prototype<bool>>, int(bool) & noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void() && noexcept, int, lean::prototype<bool>>, int(bool) && noexcept>{}, "");

static_assert(std::is_same<lean::function_rebind_t<void(...) noexcept, int, lean::prototype<bool>>, int(bool, ...) noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) const noexcept, int, lean::prototype<bool>>, int(bool, ...) const noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) const & noexcept, int, lean::prototype<bool>>, int(bool, ...) const & noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) const && noexcept, int, lean::prototype<bool>>, int(bool, ...) const && noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) const volatile noexcept, int, lean::prototype<bool>>, int(bool, ...) const volatile noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) const volatile & noexcept, int, lean::prototype<bool>>, int(bool, ...) const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) const volatile && noexcept, int, lean::prototype<bool>>, int(bool, ...) const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) volatile noexcept, int, lean::prototype<bool>>, int(bool, ...) volatile noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) volatile & noexcept, int, lean::prototype<bool>>, int(bool, ...) volatile & noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) volatile && noexcept, int, lean::prototype<bool>>, int(bool, ...) volatile && noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) & noexcept, int, lean::prototype<bool>>, int(bool, ...) & noexcept>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(...) && noexcept, int, lean::prototype<bool>>, int(bool, ...) && noexcept>{}, "");

#endif

static_assert(std::is_same<lean::function_rebind_t<void(), void, lean::prototype<>>, void()>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(), bool, lean::prototype<>>, bool()>{}, "");
static_assert(std::is_same<lean::function_rebind_t<bool(), void, lean::prototype<>>, void()>{}, "");
static_assert(std::is_same<lean::function_rebind_t<bool(), bool, lean::prototype<>>, bool()>{}, "");

static_assert(std::is_same<lean::function_rebind_t<void(), void, lean::prototype<bool>>, void(bool)>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(), void, lean::prototype<bool, int>>, void(bool, int)>{}, "");
static_assert(std::is_same<lean::function_rebind_t<void(), void, lean::prototype<bool, int, float>>, void(bool, int, float)>{}, "");

} // namespace suite_function_rebind

//-----------------------------------------------------------------------------

namespace suite_is_function_const
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

static_assert(!lean::is_function_const_t<bool(...)>{}, "");
static_assert( lean::is_function_const_t<bool(...) const>{}, "");
static_assert( lean::is_function_const_t<bool(...) const &>{}, "");
static_assert( lean::is_function_const_t<bool(...) const &&>{}, "");
static_assert( lean::is_function_const_t<bool(...) const volatile>{}, "");
static_assert( lean::is_function_const_t<bool(...) const volatile &>{}, "");
static_assert( lean::is_function_const_t<bool(...) const volatile &&>{}, "");
static_assert(!lean::is_function_const_t<bool(...) volatile>{}, "");
static_assert(!lean::is_function_const_t<bool(...) volatile &>{}, "");
static_assert(!lean::is_function_const_t<bool(...) volatile &&>{}, "");
static_assert(!lean::is_function_const_t<bool(...) &>{}, "");
static_assert(!lean::is_function_const_t<bool(...) &&>{}, "");

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

static_assert(!lean::is_function_const_t<bool(...) noexcept>{}, "");
static_assert( lean::is_function_const_t<bool(...) const noexcept>{}, "");
static_assert( lean::is_function_const_t<bool(...) const & noexcept>{}, "");
static_assert( lean::is_function_const_t<bool(...) const && noexcept>{}, "");
static_assert( lean::is_function_const_t<bool(...) const volatile noexcept>{}, "");
static_assert( lean::is_function_const_t<bool(...) const volatile & noexcept>{}, "");
static_assert( lean::is_function_const_t<bool(...) const volatile && noexcept>{}, "");
static_assert(!lean::is_function_const_t<bool(...) volatile noexcept>{}, "");
static_assert(!lean::is_function_const_t<bool(...) volatile & noexcept>{}, "");
static_assert(!lean::is_function_const_t<bool(...) volatile && noexcept>{}, "");
static_assert(!lean::is_function_const_t<bool(...) & noexcept>{}, "");
static_assert(!lean::is_function_const_t<bool(...) && noexcept>{}, "");

#endif

static_assert(!lean::is_function_const_t<bool>{}, "");
static_assert(!lean::is_function_const_t<const bool>{}, "");
static_assert(!lean::is_function_const_t<bool *>{}, "");
static_assert(!lean::is_function_const_t<bool * const>{}, "");
static_assert(!lean::is_function_const_t<const bool *>{}, "");

} // namespace suite_is_function_const

//-----------------------------------------------------------------------------

namespace suite_is_function_volatile
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

static_assert(!lean::is_function_volatile_t<bool(...)>{}, "");
static_assert(!lean::is_function_volatile_t<bool(...) const>{}, "");
static_assert(!lean::is_function_volatile_t<bool(...) const &>{}, "");
static_assert(!lean::is_function_volatile_t<bool(...) const &&>{}, "");
static_assert( lean::is_function_volatile_t<bool(...) const volatile>{}, "");
static_assert( lean::is_function_volatile_t<bool(...) const volatile &>{}, "");
static_assert( lean::is_function_volatile_t<bool(...) const volatile &&>{}, "");
static_assert( lean::is_function_volatile_t<bool(...) volatile>{}, "");
static_assert( lean::is_function_volatile_t<bool(...) volatile &>{}, "");
static_assert( lean::is_function_volatile_t<bool(...) volatile &&>{}, "");
static_assert(!lean::is_function_volatile_t<bool(...) &>{}, "");
static_assert(!lean::is_function_volatile_t<bool(...) &&>{}, "");

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

static_assert(!lean::is_function_volatile_t<bool(...) noexcept>{}, "");
static_assert(!lean::is_function_volatile_t<bool(...) const noexcept>{}, "");
static_assert(!lean::is_function_volatile_t<bool(...) const & noexcept>{}, "");
static_assert(!lean::is_function_volatile_t<bool(...) const && noexcept>{}, "");
static_assert( lean::is_function_volatile_t<bool(...) const volatile noexcept>{}, "");
static_assert( lean::is_function_volatile_t<bool(...) const volatile & noexcept>{}, "");
static_assert( lean::is_function_volatile_t<bool(...) const volatile && noexcept>{}, "");
static_assert( lean::is_function_volatile_t<bool(...) volatile noexcept>{}, "");
static_assert( lean::is_function_volatile_t<bool(...) volatile & noexcept>{}, "");
static_assert( lean::is_function_volatile_t<bool(...) volatile && noexcept>{}, "");
static_assert(!lean::is_function_volatile_t<bool(...) & noexcept>{}, "");
static_assert(!lean::is_function_volatile_t<bool(...) && noexcept>{}, "");

#endif

static_assert(!lean::is_function_volatile_t<bool>{}, "");
static_assert(!lean::is_function_volatile_t<volatile bool>{}, "");
static_assert(!lean::is_function_volatile_t<bool *>{}, "");
static_assert(!lean::is_function_volatile_t<bool * volatile>{}, "");
static_assert(!lean::is_function_volatile_t<volatile bool *>{}, "");

} // namespace suite_is_function_volatile

//-----------------------------------------------------------------------------

namespace suite_is_function_lvalue_reference
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

static_assert(!lean::is_function_lvalue_reference_t<bool(...)>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool(...) const>{}, "");
static_assert( lean::is_function_lvalue_reference_t<bool(...) const &>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool(...) const &&>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool(...) const volatile>{}, "");
static_assert( lean::is_function_lvalue_reference_t<bool(...) const volatile &>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool(...) const volatile &&>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool(...) volatile>{}, "");
static_assert( lean::is_function_lvalue_reference_t<bool(...) volatile &>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool(...) volatile &&>{}, "");
static_assert( lean::is_function_lvalue_reference_t<bool(...) &>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool(...) &&>{}, "");

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

static_assert(!lean::is_function_lvalue_reference_t<bool(...) noexcept>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool(...) const noexcept>{}, "");
static_assert( lean::is_function_lvalue_reference_t<bool(...) const & noexcept>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool(...) const && noexcept>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool(...) const volatile noexcept>{}, "");
static_assert( lean::is_function_lvalue_reference_t<bool(...) const volatile & noexcept>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool(...) const volatile && noexcept>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool(...) volatile noexcept>{}, "");
static_assert( lean::is_function_lvalue_reference_t<bool(...) volatile & noexcept>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool(...) volatile && noexcept>{}, "");
static_assert( lean::is_function_lvalue_reference_t<bool(...) & noexcept>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool(...) && noexcept>{}, "");

#endif

static_assert(!lean::is_function_lvalue_reference_t<bool>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool&>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<bool&&>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<const bool>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<const bool&>{}, "");
static_assert(!lean::is_function_lvalue_reference_t<const bool&&>{}, "");

} // namespace suite_is_function_lvalue_reference

//-----------------------------------------------------------------------------

namespace suite_is_function_rvalue_reference
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

static_assert(!lean::is_function_rvalue_reference_t<bool(...)>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool(...) const>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool(...) const &>{}, "");
static_assert( lean::is_function_rvalue_reference_t<bool(...) const &&>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool(...) const volatile>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool(...) const volatile &>{}, "");
static_assert( lean::is_function_rvalue_reference_t<bool(...) const volatile &&>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool(...) volatile>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool(...) volatile &>{}, "");
static_assert( lean::is_function_rvalue_reference_t<bool(...) volatile &&>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool(...) &>{}, "");
static_assert( lean::is_function_rvalue_reference_t<bool(...) &&>{}, "");

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

static_assert(!lean::is_function_rvalue_reference_t<bool(...) noexcept>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool(...) const noexcept>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool(...) const & noexcept>{}, "");
static_assert( lean::is_function_rvalue_reference_t<bool(...) const && noexcept>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool(...) const volatile noexcept>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool(...) const volatile & noexcept>{}, "");
static_assert( lean::is_function_rvalue_reference_t<bool(...) const volatile && noexcept>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool(...) volatile noexcept>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool(...) volatile & noexcept>{}, "");
static_assert( lean::is_function_rvalue_reference_t<bool(...) volatile && noexcept>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool(...) & noexcept>{}, "");
static_assert( lean::is_function_rvalue_reference_t<bool(...) && noexcept>{}, "");

#endif

static_assert(!lean::is_function_rvalue_reference_t<bool>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool&>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<bool&&>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<const bool>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<const bool&>{}, "");
static_assert(!lean::is_function_rvalue_reference_t<const bool&&>{}, "");

} // namespace suite_is_function_rvalue_reference

//-----------------------------------------------------------------------------

namespace suite_is_function_reference
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

static_assert(!lean::is_function_reference_t<bool(...)>{}, "");
static_assert(!lean::is_function_reference_t<bool(...) const>{}, "");
static_assert( lean::is_function_reference_t<bool(...) const &>{}, "");
static_assert( lean::is_function_reference_t<bool(...) const &&>{}, "");
static_assert(!lean::is_function_reference_t<bool(...) const volatile>{}, "");
static_assert( lean::is_function_reference_t<bool(...) const volatile &>{}, "");
static_assert( lean::is_function_reference_t<bool(...) const volatile &&>{}, "");
static_assert(!lean::is_function_reference_t<bool(...) volatile>{}, "");
static_assert( lean::is_function_reference_t<bool(...) volatile &>{}, "");
static_assert( lean::is_function_reference_t<bool(...) volatile &&>{}, "");
static_assert( lean::is_function_reference_t<bool(...) &>{}, "");
static_assert( lean::is_function_reference_t<bool(...) &&>{}, "");

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

static_assert(!lean::is_function_reference_t<bool(...) noexcept>{}, "");
static_assert(!lean::is_function_reference_t<bool(...) const noexcept>{}, "");
static_assert( lean::is_function_reference_t<bool(...) const & noexcept>{}, "");
static_assert( lean::is_function_reference_t<bool(...) const && noexcept>{}, "");
static_assert(!lean::is_function_reference_t<bool(...) const volatile noexcept>{}, "");
static_assert( lean::is_function_reference_t<bool(...) const volatile & noexcept>{}, "");
static_assert( lean::is_function_reference_t<bool(...) const volatile && noexcept>{}, "");
static_assert(!lean::is_function_reference_t<bool(...) volatile noexcept>{}, "");
static_assert( lean::is_function_reference_t<bool(...) volatile & noexcept>{}, "");
static_assert( lean::is_function_reference_t<bool(...) volatile && noexcept>{}, "");
static_assert( lean::is_function_reference_t<bool(...) & noexcept>{}, "");
static_assert( lean::is_function_reference_t<bool(...) && noexcept>{}, "");

#endif

static_assert(!lean::is_function_reference_t<bool>{}, "");
static_assert(!lean::is_function_reference_t<bool&>{}, "");
static_assert(!lean::is_function_reference_t<bool&&>{}, "");
static_assert(!lean::is_function_reference_t<const bool>{}, "");
static_assert(!lean::is_function_reference_t<const bool&>{}, "");
static_assert(!lean::is_function_reference_t<const bool&&>{}, "");

} // namespace suite_is_function_reference

//-----------------------------------------------------------------------------

namespace suite_is_function_ellipsis
{

static_assert(!lean::is_function_ellipsis_t<bool()>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() const>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() const &>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() const &&>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() const volatile>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() const volatile &>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() const volatile &&>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() volatile>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() volatile &>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() volatile &&>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() &>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() &&>{}, "");

static_assert( lean::is_function_ellipsis_t<bool(...)>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) const>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) const &>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) const &&>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) const volatile>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) const volatile &>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) const volatile &&>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) volatile>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) volatile &>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) volatile &&>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) &>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) &&>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(!lean::is_function_ellipsis_t<bool() noexcept>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() const noexcept>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() const & noexcept>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() const && noexcept>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() const volatile noexcept>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() const volatile & noexcept>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() const volatile && noexcept>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() volatile noexcept>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() volatile & noexcept>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() volatile && noexcept>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() & noexcept>{}, "");
static_assert(!lean::is_function_ellipsis_t<bool() && noexcept>{}, "");

static_assert( lean::is_function_ellipsis_t<bool(...) noexcept>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) const noexcept>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) const & noexcept>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) const && noexcept>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) const volatile noexcept>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) const volatile & noexcept>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) const volatile && noexcept>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) volatile noexcept>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) volatile & noexcept>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) volatile && noexcept>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) & noexcept>{}, "");
static_assert( lean::is_function_ellipsis_t<bool(...) && noexcept>{}, "");

#endif

} // namespace suite_is_function_ellipsis

//-----------------------------------------------------------------------------

namespace suite_add_function_const
{

static_assert(std::is_same<lean::add_function_const_t<bool()>, bool() const>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() const>, bool() const>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() const &>, bool() const &>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() const &&>, bool() const &&>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() const volatile>, bool() const volatile>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() const volatile &>, bool() const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() const volatile &&>, bool() const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() volatile>, bool() const volatile>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() volatile &>, bool() const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() volatile &&>, bool() const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() &>, bool() const &>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() &&>, bool() const &&>{}, "");

static_assert(std::is_same<lean::add_function_const_t<bool(...)>, bool(...) const>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) const>, bool(...) const>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) const &>, bool(...) const &>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) const &&>, bool(...) const &&>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) const volatile>, bool(...) const volatile>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) const volatile &>, bool(...) const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) const volatile &&>, bool(...) const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) volatile>, bool(...) const volatile>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) volatile &>, bool(...) const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) volatile &&>, bool(...) const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) &>, bool(...) const &>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) &&>, bool(...) const &&>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<lean::add_function_const_t<bool() noexcept>, bool() const noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() const noexcept>, bool() const noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() const & noexcept>, bool() const & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() const && noexcept>, bool() const && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() const volatile noexcept>, bool() const volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() const volatile & noexcept>, bool() const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() const volatile && noexcept>, bool() const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() volatile noexcept>, bool() const volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() volatile & noexcept>, bool() const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() volatile && noexcept>, bool() const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() & noexcept>, bool() const & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool() && noexcept>, bool() const && noexcept>{}, "");

static_assert(std::is_same<lean::add_function_const_t<bool(...) noexcept>, bool(...) const noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) const noexcept>, bool(...) const noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) const & noexcept>, bool(...) const & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) const && noexcept>, bool(...) const && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) const volatile noexcept>, bool(...) const volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) const volatile & noexcept>, bool(...) const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) const volatile && noexcept>, bool(...) const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) volatile noexcept>, bool(...) const volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) volatile & noexcept>, bool(...) const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) volatile && noexcept>, bool(...) const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) & noexcept>, bool(...) const & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_const_t<bool(...) && noexcept>, bool(...) const && noexcept>{}, "");

#endif

} // namespace suite_add_function_const

//-----------------------------------------------------------------------------

namespace suite_add_function_volatile
{

static_assert(std::is_same<lean::add_function_volatile_t<bool()>, bool() volatile>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() const>, bool() const volatile>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() const &>, bool() const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() const &&>, bool() const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() const volatile>, bool() const volatile>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() const volatile &>, bool() const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() const volatile &&>, bool() const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() volatile>, bool() volatile>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() volatile &>, bool() volatile &>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() volatile &&>, bool() volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() &>, bool() volatile &>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() &&>, bool() volatile &&>{}, "");

static_assert(std::is_same<lean::add_function_volatile_t<bool(...)>, bool(...) volatile>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) const>, bool(...) const volatile>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) const &>, bool(...) const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) const &&>, bool(...) const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) const volatile>, bool(...) const volatile>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) const volatile &>, bool(...) const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) const volatile &&>, bool(...) const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) volatile>, bool(...) volatile>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) volatile &>, bool(...) volatile &>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) volatile &&>, bool(...) volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) &>, bool(...) volatile &>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) &&>, bool(...) volatile &&>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<lean::add_function_volatile_t<bool() noexcept>, bool() volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() const noexcept>, bool() const volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() const & noexcept>, bool() const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() const && noexcept>, bool() const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() const volatile noexcept>, bool() const volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() const volatile & noexcept>, bool() const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() const volatile && noexcept>, bool() const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() volatile noexcept>, bool() volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() volatile & noexcept>, bool() volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() volatile && noexcept>, bool() volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() & noexcept>, bool() volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool() && noexcept>, bool() volatile && noexcept>{}, "");

static_assert(std::is_same<lean::add_function_volatile_t<bool(...) noexcept>, bool(...) volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) const noexcept>, bool(...) const volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) const & noexcept>, bool(...) const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) const && noexcept>, bool(...) const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) const volatile noexcept>, bool(...) const volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) const volatile & noexcept>, bool(...) const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) const volatile && noexcept>, bool(...) const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) volatile noexcept>, bool(...) volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) volatile & noexcept>, bool(...) volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) volatile && noexcept>, bool(...) volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) & noexcept>, bool(...) volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_volatile_t<bool(...) && noexcept>, bool(...) volatile && noexcept>{}, "");

#endif

} // namespace suite_add_function_volatile

//-----------------------------------------------------------------------------

namespace suite_add_function_cv
{

static_assert(std::is_same<lean::add_function_cv_t<bool()>, bool() const volatile>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() const>, bool() const volatile>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() const &>, bool() const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() const &&>, bool() const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() const volatile>, bool() const volatile>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() const volatile &>, bool() const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() const volatile &&>, bool() const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() volatile>, bool() const volatile>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() volatile &>, bool() const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() volatile &&>, bool() const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() &>, bool() const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() &&>, bool() const volatile &&>{}, "");

static_assert(std::is_same<lean::add_function_cv_t<bool(...)>, bool(...) const volatile>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) const>, bool(...) const volatile>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) const &>, bool(...) const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) const &&>, bool(...) const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) const volatile>, bool(...) const volatile>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) const volatile &>, bool(...) const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) const volatile &&>, bool(...) const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) volatile>, bool(...) const volatile>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) volatile &>, bool(...) const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) volatile &&>, bool(...) const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) &>, bool(...) const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) &&>, bool(...) const volatile &&>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<lean::add_function_cv_t<bool() noexcept>, bool() const volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() const noexcept>, bool() const volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() const & noexcept>, bool() const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() const && noexcept>, bool() const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() const volatile noexcept>, bool() const volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() const volatile & noexcept>, bool() const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() const volatile && noexcept>, bool() const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() volatile noexcept>, bool() const volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() volatile & noexcept>, bool() const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() volatile && noexcept>, bool() const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() & noexcept>, bool() const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool() && noexcept>, bool() const volatile && noexcept>{}, "");

static_assert(std::is_same<lean::add_function_cv_t<bool(...) noexcept>, bool(...) const volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) const noexcept>, bool(...) const volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) const & noexcept>, bool(...) const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) const && noexcept>, bool(...) const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) const volatile noexcept>, bool(...) const volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) const volatile & noexcept>, bool(...) const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) const volatile && noexcept>, bool(...) const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) volatile noexcept>, bool(...) const volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) volatile & noexcept>, bool(...) const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) volatile && noexcept>, bool(...) const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) & noexcept>, bool(...) const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_cv_t<bool(...) && noexcept>, bool(...) const volatile && noexcept>{}, "");

#endif

} // namespace suite_add_function_cv

//-----------------------------------------------------------------------------

namespace suite_add_function_lvalue_reference
{
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool()>, bool() &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() const>, bool() const &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() const &>, bool() const &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() const &&>, bool() const &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() const volatile>, bool() const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() const volatile &>, bool() const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() const volatile &&>, bool() const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() volatile>, bool() volatile &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() volatile &>, bool() volatile &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() volatile &&>, bool() volatile &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() &>, bool() &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() &&>, bool() &>{}, "");

static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...)>, bool(...) &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) const>, bool(...) const &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) const &>, bool(...) const &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) const &&>, bool(...) const &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) const volatile>, bool(...) const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) const volatile &>, bool(...) const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) const volatile &&>, bool(...) const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) volatile>, bool(...) volatile &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) volatile &>, bool(...) volatile &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) volatile &&>, bool(...) volatile &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) &>, bool(...) &>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) &&>, bool(...) &>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() noexcept>, bool() & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() const noexcept>, bool() const & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() const & noexcept>, bool() const & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() const && noexcept>, bool() const & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() const volatile noexcept>, bool() const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() const volatile & noexcept>, bool() const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() const volatile && noexcept>, bool() const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() volatile noexcept>, bool() volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() volatile & noexcept>, bool() volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() volatile && noexcept>, bool() volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() & noexcept>, bool() & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool() && noexcept>, bool() & noexcept>{}, "");

static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) noexcept>, bool(...) & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) const noexcept>, bool(...) const & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) const & noexcept>, bool(...) const & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) const && noexcept>, bool(...) const & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) const volatile noexcept>, bool(...) const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) const volatile & noexcept>, bool(...) const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) const volatile && noexcept>, bool(...) const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) volatile noexcept>, bool(...) volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) volatile & noexcept>, bool(...) volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) volatile && noexcept>, bool(...) volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) & noexcept>, bool(...) & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_lvalue_reference_t<bool(...) && noexcept>, bool(...) & noexcept>{}, "");

#endif

} // namespace suite_add_function_lvalue_reference

//-----------------------------------------------------------------------------

namespace suite_add_function_rvalue_reference
{
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool()>, bool() &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() const>, bool() const &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() const &>, bool() const &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() const &&>, bool() const &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() const volatile>, bool() const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() const volatile &>, bool() const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() const volatile &&>, bool() const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() volatile>, bool() volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() volatile &>, bool() volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() volatile &&>, bool() volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() &>, bool() &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() &&>, bool() &&>{}, "");

static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...)>, bool(...) &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) const>, bool(...) const &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) const &>, bool(...) const &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) const &&>, bool(...) const &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) const volatile>, bool(...) const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) const volatile &>, bool(...) const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) const volatile &&>, bool(...) const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) volatile>, bool(...) volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) volatile &>, bool(...) volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) volatile &&>, bool(...) volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) &>, bool(...) &&>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) &&>, bool(...) &&>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() noexcept>, bool() && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() const noexcept>, bool() const && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() const & noexcept>, bool() const && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() const && noexcept>, bool() const && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() const volatile noexcept>, bool() const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() const volatile & noexcept>, bool() const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() const volatile && noexcept>, bool() const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() volatile noexcept>, bool() volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() volatile & noexcept>, bool() volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() volatile && noexcept>, bool() volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() & noexcept>, bool() && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool() && noexcept>, bool() && noexcept>{}, "");

static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) noexcept>, bool(...) && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) const noexcept>, bool(...) const && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) const & noexcept>, bool(...) const && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) const && noexcept>, bool(...) const && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) const volatile noexcept>, bool(...) const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) const volatile & noexcept>, bool(...) const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) const volatile && noexcept>, bool(...) const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) volatile noexcept>, bool(...) volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) volatile & noexcept>, bool(...) volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) volatile && noexcept>, bool(...) volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) & noexcept>, bool(...) && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_rvalue_reference_t<bool(...) && noexcept>, bool(...) && noexcept>{}, "");

#endif

} // namespace suite_add_function_rvalue_reference

//-----------------------------------------------------------------------------

namespace suite_add_function_ellipsis
{

static_assert(std::is_same<lean::add_function_ellipsis_t<bool()>, bool(...)>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() const>, bool(...) const>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() const &>, bool(...) const &>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() const &&>, bool(...) const &&>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() const volatile>, bool(...) const volatile>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() const volatile &>, bool(...) const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() const volatile &&>, bool(...) const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() volatile>, bool(...) volatile>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() volatile &>, bool(...) volatile &>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() volatile &&>, bool(...) volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() &>, bool(...) &>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() &&>, bool(...) &&>{}, "");

static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...)>, bool(...)>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) const>, bool(...) const>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) const &>, bool(...) const &>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) const &&>, bool(...) const &&>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) const volatile>, bool(...) const volatile>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) const volatile &>, bool(...) const volatile &>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) const volatile &&>, bool(...) const volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) volatile>, bool(...) volatile>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) volatile &>, bool(...) volatile &>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) volatile &&>, bool(...) volatile &&>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) &>, bool(...) &>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) &&>, bool(...) &&>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<lean::add_function_ellipsis_t<bool() noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() const noexcept>, bool(...) const noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() const & noexcept>, bool(...) const & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() const && noexcept>, bool(...) const && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() const volatile noexcept>, bool(...) const volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() const volatile & noexcept>, bool(...) const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() const volatile && noexcept>, bool(...) const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() volatile noexcept>, bool(...) volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() volatile & noexcept>, bool(...) volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() volatile && noexcept>, bool(...) volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() & noexcept>, bool(...) & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool() && noexcept>, bool(...) && noexcept>{}, "");

static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) const noexcept>, bool(...) const noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) const & noexcept>, bool(...) const & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) const && noexcept>, bool(...) const && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) const volatile noexcept>, bool(...) const volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) const volatile & noexcept>, bool(...) const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) const volatile && noexcept>, bool(...) const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) volatile noexcept>, bool(...) volatile noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) volatile & noexcept>, bool(...) volatile & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) volatile && noexcept>, bool(...) volatile && noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) & noexcept>, bool(...) & noexcept>{}, "");
static_assert(std::is_same<lean::add_function_ellipsis_t<bool(...) && noexcept>, bool(...) && noexcept>{}, "");

#endif

} // namespace suite_add_function_ellipsis

//-----------------------------------------------------------------------------

namespace suite_remove_function_const
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

static_assert(std::is_same<lean::remove_function_const_t<bool(...)>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) const>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) const &>, bool(...) &>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) const &&>, bool(...) &&>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) const volatile>, bool(...) volatile>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) const volatile &>, bool(...) volatile &>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) const volatile &&>, bool(...) volatile &&>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) volatile>, bool(...) volatile>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) volatile &>, bool(...) volatile &>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) volatile &&>, bool(...) volatile &&>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) &>, bool(...) &>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) &&>, bool(...) &&>{}, "");

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

static_assert(std::is_same<lean::remove_function_const_t<bool(...) noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) const noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) const & noexcept>, bool(...) & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) const && noexcept>, bool(...) && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) const volatile noexcept>, bool(...) volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) const volatile & noexcept>, bool(...) volatile & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) const volatile && noexcept>, bool(...) volatile && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) volatile noexcept>, bool(...) volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) volatile & noexcept>, bool(...) volatile & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) volatile && noexcept>, bool(...) volatile && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) & noexcept>, bool(...) & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_const_t<bool(...) && noexcept>, bool(...) && noexcept>{}, "");

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

} // namespace suite_remove_function_const

//-----------------------------------------------------------------------------

namespace suite_remove_function_volatile
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

static_assert(std::is_same<lean::remove_function_volatile_t<bool(...)>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) const>, bool(...) const>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) const &>, bool(...) const &>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) const &&>, bool(...) const &&>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) const volatile>, bool(...) const>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) const volatile &>, bool(...) const &>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) const volatile &&>, bool(...) const &&>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) volatile>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) volatile &>, bool(...) &>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) volatile &&>, bool(...) &&>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) &>, bool(...) &>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) &&>, bool(...) &&>{}, "");

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

static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) const noexcept>, bool(...) const noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) const & noexcept>, bool(...) const & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) const && noexcept>, bool(...) const && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) const volatile noexcept>, bool(...) const noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) const volatile & noexcept>, bool(...) const & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) const volatile && noexcept>, bool(...) const && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) volatile noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) volatile & noexcept>, bool(...) & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) volatile && noexcept>, bool(...) && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) & noexcept>, bool(...) & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_volatile_t<bool(...) && noexcept>, bool(...) && noexcept>{}, "");

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

} // namespace suite_remove_function_volatile

//-----------------------------------------------------------------------------

namespace suite_remove_function_cv
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

static_assert(std::is_same<lean::remove_function_cv_t<bool(...)>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) const>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) const &>, bool(...) &>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) const &&>, bool(...) &&>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) const volatile>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) const volatile &>, bool(...) &>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) const volatile &&>, bool(...) &&>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) volatile>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) volatile &>, bool(...) &>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) volatile &&>, bool(...) &&>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) &>, bool(...) &>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) &&>, bool(...) &&>{}, "");

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

static_assert(std::is_same<lean::remove_function_cv_t<bool(...) noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) const noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) const & noexcept>, bool(...) & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) const && noexcept>, bool(...) && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) const volatile noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) const volatile & noexcept>, bool(...) & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) const volatile && noexcept>, bool(...) && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) volatile noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) volatile & noexcept>, bool(...) & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) volatile && noexcept>, bool(...) && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) & noexcept>, bool(...) & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cv_t<bool(...) && noexcept>, bool(...) && noexcept>{}, "");

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

} // namespace suite_remove_function_cv

//-----------------------------------------------------------------------------

namespace suite_remove_function_reference
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

static_assert(std::is_same<lean::remove_function_reference_t<bool(...)>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) const>, bool(...) const>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) const &>, bool(...) const>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) const &&>, bool(...) const>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) const volatile>, bool(...) const volatile>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) const volatile &>, bool(...) const volatile>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) const volatile &&>, bool(...) const volatile>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) volatile>, bool(...) volatile>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) volatile &>, bool(...) volatile>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) volatile &&>, bool(...) volatile>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) &>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) &&>, bool(...)>{}, "");

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

static_assert(std::is_same<lean::remove_function_reference_t<bool(...) noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) const noexcept>, bool(...) const noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) const & noexcept>, bool(...) const noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) const && noexcept>, bool(...) const noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) const volatile noexcept>, bool(...) const volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) const volatile & noexcept>, bool(...) const volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) const volatile && noexcept>, bool(...) const volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) volatile noexcept>, bool(...) volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) volatile & noexcept>, bool(...) volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) volatile && noexcept>, bool(...) volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) & noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_reference_t<bool(...) && noexcept>, bool(...) noexcept>{}, "");

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

} // namespace suite_remove_function_reference

//-----------------------------------------------------------------------------

namespace suite_remove_function_cvref
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

static_assert(std::is_same<lean::remove_function_cvref_t<bool(...)>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) const>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) const &>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) const &&>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) const volatile>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) const volatile &>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) const volatile &&>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) volatile>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) volatile &>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) volatile &&>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) &>, bool(...)>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) &&>, bool(...)>{}, "");

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

static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) const noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) const & noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) const && noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) const volatile noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) const volatile & noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) const volatile && noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) volatile noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) volatile & noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) volatile && noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) & noexcept>, bool(...) noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_cvref_t<bool(...) && noexcept>, bool(...) noexcept>{}, "");

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

} // namespace suite_remove_function_cvref

//-----------------------------------------------------------------------------

namespace suite_remove_function_ellipsis
{

static_assert(std::is_same<lean::remove_function_ellipsis_t<bool()>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() const>, bool() const>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() const &>, bool() const &>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() const &&>, bool() const &&>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() const volatile>, bool() const volatile>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() const volatile &>, bool() const volatile &>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() const volatile &&>, bool() const volatile &&>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() volatile>, bool() volatile>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() volatile &>, bool() volatile &>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() volatile &&>, bool() volatile &&>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() &>, bool() &>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() &&>, bool() &&>{}, "");

static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...)>, bool()>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) const>, bool() const>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) const &>, bool() const &>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) const &&>, bool() const &&>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) const volatile>, bool() const volatile>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) const volatile &>, bool() const volatile &>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) const volatile &&>, bool() const volatile &&>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) volatile>, bool() volatile>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) volatile &>, bool() volatile &>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) volatile &&>, bool() volatile &&>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) &>, bool() &>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) &&>, bool() &&>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() const noexcept>, bool() const noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() const & noexcept>, bool() const & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() const && noexcept>, bool() const && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() const volatile noexcept>, bool() const volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() const volatile & noexcept>, bool() const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() const volatile && noexcept>, bool() const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() volatile noexcept>, bool() volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() volatile & noexcept>, bool() volatile & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() volatile && noexcept>, bool() volatile && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() & noexcept>, bool() & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool() && noexcept>, bool() && noexcept>{}, "");

static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) const noexcept>, bool() const noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) const & noexcept>, bool() const & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) const && noexcept>, bool() const && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) const volatile noexcept>, bool() const volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) const volatile & noexcept>, bool() const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) const volatile && noexcept>, bool() const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) volatile noexcept>, bool() volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) volatile & noexcept>, bool() volatile & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) volatile && noexcept>, bool() volatile && noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) & noexcept>, bool() & noexcept>{}, "");
static_assert(std::is_same<lean::remove_function_ellipsis_t<bool(...) && noexcept>, bool() && noexcept>{}, "");

#endif

} // namespace suite_remove_function_ellipsis

//-----------------------------------------------------------------------------

int main()
{
    (void)lambda_const;
    (void)lambda_mutable;
    (void)lambda_const_noexcept;
    (void)lambda_mutable_noexcept;
    return 0;
}
