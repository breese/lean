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
#include <lean/detail/config.hpp> // attributes
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

//-----------------------------------------------------------------------------

namespace suite_function_type
{

template <typename F, typename... Args>
constexpr auto test_invoker(F, Args...)
    -> lean::add_pointer_t<lean::prototype<lean::function_type_t<F, Args...>>>
{
    return nullptr;
}

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

// Function

constexpr void function(bool);

static_assert(std::is_same<decltype(test_invoker(function)), lean::prototype<void(bool)>*>{}, "");
static_assert(std::is_same<decltype(test_invoker(&function)), lean::prototype<void(bool)>*>{}, "");

constexpr bool overloaded_function(bool);
constexpr int overloaded_function(int);

// Overloaded function must be disambiguated manually
static_assert(std::is_same<decltype(test_invoker(static_cast<bool(&)(bool)>(overloaded_function))), lean::prototype<bool(bool)>*>{}, "");
static_assert(std::is_same<decltype(test_invoker(static_cast<bool(&)(bool)>(overloaded_function), std::declval<bool>())), lean::prototype<bool(bool)>*>{}, "");
static_assert(std::is_same<decltype(test_invoker(static_cast<bool(&)(bool)>(overloaded_function), std::declval<int>())), lean::prototype<bool(bool)>*>{}, "");
static_assert(std::is_same<decltype(test_invoker(static_cast<int(&)(int)>(overloaded_function))), lean::prototype<int(int)>*>{}, "");
static_assert(std::is_same<decltype(test_invoker(static_cast<int(&)(int)>(overloaded_function), std::declval<int*>())), lean::prototype<int(int)>*>{}, "argument ignored");

#if __cpp_noexcept_function_type >= 201510L

constexpr void function_noexcept(bool) noexcept;

static_assert(std::is_same<decltype(test_invoker(function_noexcept)), lean::prototype<void(bool) noexcept>*>{}, "");
static_assert(std::is_same<decltype(test_invoker(&function_noexcept)), lean::prototype<void(bool) noexcept>*>{}, "");

#endif

// Function object

static_assert(std::is_same<lean::function_type_t<function_object>, void()>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(&function_object::operator())>, void()>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(&function_object::invoke)>, void()>{}, "");

struct function_object_mutable
{
    void operator()();
};

static_assert(std::is_same<lean::function_type_t<function_object_mutable>, void()>{}, "");

struct function_object_const
{
    void operator()() const;
};

static_assert(std::is_same<lean::function_type_t<const function_object_const>, void() const>{}, "");

struct function_object_const_lvalue
{
    void operator()() const &;
};

static_assert(std::is_same<lean::function_type_t<const function_object_const_lvalue&>, void() const &>{}, "");

struct function_object_const_rvalue
{
    void operator()() const &&;
};

static_assert(std::is_same<lean::function_type_t<const function_object_const_rvalue&&>, void() const &&>{}, "");

struct function_object_const_volatile
{
    void operator()() const volatile;
};

static_assert(std::is_same<lean::function_type_t<const volatile function_object_const_volatile>, void() const volatile>{}, "");

struct function_object_const_volatile_lvalue
{
    void operator()() const volatile &;
};

static_assert(std::is_same<lean::function_type_t<const volatile function_object_const_volatile_lvalue&>, void() const volatile &>{}, "");

struct function_object_const_volatile_rvalue
{
    void operator()() const volatile &&;
};

static_assert(std::is_same<lean::function_type_t<const volatile function_object_const_volatile_rvalue&&>, void() const volatile &&>{}, "");

struct function_object_volatile
{
    void operator()() volatile;
};

static_assert(std::is_same<lean::function_type_t<volatile function_object_volatile>, void() volatile>{}, "");

struct function_object_volatile_lvalue
{
    void operator()() volatile &;
};

static_assert(std::is_same<lean::function_type_t<volatile function_object_volatile_lvalue&>, void() volatile &>{}, "");

struct function_object_volatile_rvalue
{
    void operator()() volatile &&;
};

static_assert(std::is_same<lean::function_type_t<volatile function_object_volatile_rvalue&&>, void() volatile &&>{}, "");

struct function_object_lvalue
{
    void operator()() &;
};

static_assert(std::is_same<lean::function_type_t<function_object_lvalue&>, void() &>{}, "");

struct function_object_rvalue
{
    void operator()() &&;
};

static_assert(std::is_same<lean::function_type_t<function_object_rvalue&&>, void() &&>{}, "");

struct function_object_overload_1
{
    void operator()();
    void operator()() const;
    void operator()() const volatile;
    void operator()() volatile;
};

static_assert(std::is_same<lean::function_type_t<function_object_overload_1>, void()>{}, "");
static_assert(std::is_same<lean::function_type_t<const function_object_overload_1>, void() const>{}, "");
static_assert(std::is_same<lean::function_type_t<const volatile function_object_overload_1>, void() const volatile>{}, "");
static_assert(std::is_same<lean::function_type_t<volatile function_object_overload_1>, void() volatile>{}, "");

struct function_object_overload_2
{
    void operator()() &;
    void operator()() const &;
    void operator()() const volatile &;
    void operator()() volatile &;
};

static_assert(std::is_same<lean::function_type_t<function_object_overload_2&>, void() &>{}, "");
static_assert(std::is_same<lean::function_type_t<const function_object_overload_2&>, void() const &>{}, "");
static_assert(std::is_same<lean::function_type_t<const volatile function_object_overload_2&>, void() const volatile &>{}, "");
static_assert(std::is_same<lean::function_type_t<volatile function_object_overload_2&>, void() volatile &>{}, "");

struct function_object_overload_3
{
    void operator()() &&;
    void operator()() const &&;
    void operator()() const volatile &&;
    void operator()() volatile &&;
};

static_assert(std::is_same<lean::function_type_t<function_object_overload_3&&>, void() &&>{}, "");
static_assert(std::is_same<lean::function_type_t<const function_object_overload_3&&>, void() const &&>{}, "");
static_assert(std::is_same<lean::function_type_t<const volatile function_object_overload_3&&>, void() const volatile &&>{}, "");
static_assert(std::is_same<lean::function_type_t<volatile function_object_overload_3&&>, void() volatile &&>{}, "");

struct function_object_overload_4
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
    void operator()() volatile &;
    void operator()() volatile &&;
};

static_assert(std::is_same<lean::function_type_t<function_object_overload_4&>, void() &>{}, "");
static_assert(std::is_same<lean::function_type_t<function_object_overload_4&&>, void() &&>{}, "");
static_assert(std::is_same<lean::function_type_t<const function_object_overload_4&>, void() const &>{}, "");
static_assert(std::is_same<lean::function_type_t<const function_object_overload_4&&>, void() const &&>{}, "");
static_assert(std::is_same<lean::function_type_t<const volatile function_object_overload_4&>, void() const volatile &>{}, "");
static_assert(std::is_same<lean::function_type_t<const volatile function_object_overload_4&&>, void() const volatile &&>{}, "");
static_assert(std::is_same<lean::function_type_t<volatile function_object_overload_4&>, void() volatile &>{}, "");
static_assert(std::is_same<lean::function_type_t<volatile function_object_overload_4&&>, void() volatile &&>{}, "");

struct function_object_overload_arg
{
    void operator()(bool);
    void operator()(bool, int);
    void operator()(int);
};

static_assert(std::is_same<lean::function_type_t<function_object_overload_arg, bool>, void(bool)>{}, "");
static_assert(std::is_same<lean::function_type_t<function_object_overload_arg, bool, int>, void(bool, int)>{}, "");
static_assert(std::is_same<lean::function_type_t<function_object_overload_arg, int>, void(int)>{}, "");

struct templated_function_object
{
    template <typename... Args>
    void operator()(Args...);
};

static_assert(std::is_same<lean::function_type_t<templated_function_object>, void()>{}, "");
static_assert(std::is_same<lean::function_type_t<templated_function_object, bool>, void(bool)>{}, "");
static_assert(std::is_same<lean::function_type_t<templated_function_object, bool, int>, void(bool, int)>{}, "");
static_assert(std::is_same<lean::function_type_t<templated_function_object, bool, int, float>, void(bool, int, float)>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<lean::function_type_t<function_object_noexcept>, void() noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(&function_object_noexcept::operator())>, void() noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(&function_object_noexcept::invoke)>, void() noexcept>{}, "");

struct function_object_mutable_noexcept
{
    void operator()() noexcept;
};

static_assert(std::is_same<lean::function_type_t<function_object_mutable_noexcept>, void() noexcept>{}, "");

struct function_object_const_noexcept
{
    void operator()() const noexcept;
};

static_assert(std::is_same<lean::function_type_t<const function_object_const_noexcept>, void() const noexcept>{}, "");

struct function_object_const_lvalue_noexcept
{
    void operator()() const & noexcept;
};

static_assert(std::is_same<lean::function_type_t<const function_object_const_lvalue_noexcept&>, void() const & noexcept>{}, "");

struct function_object_const_rvalue_noexcept
{
    void operator()() const && noexcept;
};

static_assert(std::is_same<lean::function_type_t<const function_object_const_rvalue_noexcept&&>, void() const && noexcept>{}, "");

struct function_object_const_volatile_noexcept
{
    void operator()() const volatile noexcept;
};

static_assert(std::is_same<lean::function_type_t<const volatile function_object_const_volatile_noexcept>, void() const volatile noexcept>{}, "");

struct function_object_const_volatile_lvalue_noexcept
{
    void operator()() const volatile & noexcept;
};

static_assert(std::is_same<lean::function_type_t<const volatile function_object_const_volatile_lvalue_noexcept&>, void() const volatile & noexcept>{}, "");

struct function_object_const_volatile_rvalue_noexcept
{
    void operator()() const volatile && noexcept;
};

static_assert(std::is_same<lean::function_type_t<const volatile function_object_const_volatile_rvalue_noexcept&&>, void() const volatile && noexcept>{}, "");

struct function_object_volatile_noexcept
{
    void operator()() volatile noexcept;
};

static_assert(std::is_same<lean::function_type_t<volatile function_object_volatile_noexcept>, void() volatile noexcept>{}, "");

struct function_object_volatile_lvalue_noexcept
{
    void operator()() volatile & noexcept;
};

static_assert(std::is_same<lean::function_type_t<volatile function_object_volatile_lvalue_noexcept&>, void() volatile & noexcept>{}, "");

struct function_object_volatile_rvalue_noexcept
{
    void operator()() volatile && noexcept;
};

static_assert(std::is_same<lean::function_type_t<volatile function_object_volatile_rvalue_noexcept&&>, void() volatile && noexcept>{}, "");

struct function_object_lvalue_noexcept
{
    void operator()() & noexcept;
};

static_assert(std::is_same<lean::function_type_t<function_object_lvalue_noexcept&>, void() & noexcept>{}, "");

struct function_object_rvalue_noexcept
{
    void operator()() && noexcept;
};

static_assert(std::is_same<lean::function_type_t<function_object_rvalue_noexcept&&>, void() && noexcept>{}, "");

struct function_object_noexcept_overload_1
{
    void operator()() noexcept;
    void operator()() const noexcept;
    void operator()() const volatile noexcept;
    void operator()() volatile noexcept;
};

static_assert(std::is_same<lean::function_type_t<function_object_noexcept_overload_1>, void() noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<const function_object_noexcept_overload_1>, void() const noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<const volatile function_object_noexcept_overload_1>, void() const volatile noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<volatile function_object_noexcept_overload_1>, void() volatile noexcept>{}, "");

struct function_object_noexcept_overload_2
{
    void operator()() & noexcept;
    void operator()() const & noexcept;
    void operator()() const volatile & noexcept;
    void operator()() volatile & noexcept;
};

static_assert(std::is_same<lean::function_type_t<function_object_noexcept_overload_2&>, void() & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<const function_object_noexcept_overload_2&>, void() const & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<const volatile function_object_noexcept_overload_2&>, void() const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<volatile function_object_noexcept_overload_2&>, void() volatile & noexcept>{}, "");

struct function_object_noexcept_overload_3
{
    void operator()() && noexcept;
    void operator()() const && noexcept;
    void operator()() const volatile && noexcept;
    void operator()() volatile && noexcept;
};

static_assert(std::is_same<lean::function_type_t<function_object_noexcept_overload_3&&>, void() && noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<const function_object_noexcept_overload_3&&>, void() const && noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<const volatile function_object_noexcept_overload_3&&>, void() const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<volatile function_object_noexcept_overload_3&&>, void() volatile && noexcept>{}, "");

struct function_object_noexcept_overload_4
{
    void operator()() & noexcept;
    void operator()() && noexcept;
    void operator()() const & noexcept;
    void operator()() const && noexcept;
    void operator()() const volatile & noexcept;
    void operator()() const volatile && noexcept;
    void operator()() volatile & noexcept;
    void operator()() volatile && noexcept;
};

static_assert(std::is_same<lean::function_type_t<function_object_noexcept_overload_4&>, void() & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<function_object_noexcept_overload_4&&>, void() && noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<const function_object_noexcept_overload_4&>, void() const & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<const function_object_noexcept_overload_4&&>, void() const && noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<const volatile function_object_noexcept_overload_4&>, void() const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<const volatile function_object_noexcept_overload_4&&>, void() const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<volatile function_object_noexcept_overload_4&>, void() volatile & noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<volatile function_object_noexcept_overload_4&&>, void() volatile && noexcept>{}, "");

struct function_object_noexcept_overload_arg
{
    void operator()(bool) noexcept;
    void operator()(bool, int) noexcept;
    void operator()(int) noexcept;
};

static_assert(std::is_same<lean::function_type_t<function_object_noexcept_overload_arg, bool>, void(bool) noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<function_object_noexcept_overload_arg, bool, int>, void(bool, int) noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<function_object_noexcept_overload_arg, int>, void(int) noexcept>{}, "");

struct templated_function_object_noexcept
{
    template <typename... Args>
    void operator()(Args...) noexcept;
};

static_assert(std::is_same<lean::function_type_t<templated_function_object_noexcept>, void() noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<templated_function_object_noexcept, bool>, void(bool) noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<templated_function_object_noexcept, bool, int>, void(bool, int) noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<templated_function_object_noexcept, bool, int, float>, void(bool, int, float) noexcept>{}, "");

#endif

// Lamdba

LEAN_ATTRIBUTE_UNUSED auto lambda_const = [] {};
LEAN_ATTRIBUTE_UNUSED auto lambda_mutable = [] () mutable {};

static_assert(std::is_same<lean::function_type_t<decltype(lambda_const)>, void() const>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(lambda_mutable)>, void()>{}, "");

#if __cpp_noexcept_function_type >= 201510L

LEAN_ATTRIBUTE_UNUSED auto lambda_const_noexcept = [] () noexcept {};
LEAN_ATTRIBUTE_UNUSED auto lambda_mutable_noexcept = [] () mutable noexcept {};

static_assert(std::is_same<lean::function_type_t<decltype(lambda_const_noexcept)>, void() const noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(lambda_mutable_noexcept)>, void() noexcept>{}, "");

#endif

// Generic lambda

#if __cpp_generic_lambdas >= 201304L

LEAN_ATTRIBUTE_UNUSED auto generic_lambda_const = [] (auto...) {};
LEAN_ATTRIBUTE_UNUSED auto generic_lambda_mutable = [] (auto...) mutable {};

static_assert(std::is_same<lean::function_type_t<decltype(generic_lambda_mutable)>, void()>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(generic_lambda_mutable), bool>, void(bool)>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(generic_lambda_mutable), bool, int>, void(bool, int)>{}, "");

static_assert(std::is_same<decltype(test_invoker(generic_lambda_mutable)), lean::prototype<void()>*>{}, "");
static_assert(std::is_same<decltype(test_invoker(generic_lambda_mutable, std::declval<bool>())), lean::prototype<void(bool)>*>{}, "");
static_assert(std::is_same<decltype(test_invoker(generic_lambda_mutable, std::declval<bool>(), std::declval<int>())), lean::prototype<void(bool, int)>*>{}, "");

static_assert(std::is_same<lean::function_type_t<decltype(generic_lambda_const)>, void() const>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(generic_lambda_const), bool>, void(bool) const>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(generic_lambda_const), bool, int>, void(bool, int) const>{}, "");

static_assert(std::is_same<decltype(test_invoker(generic_lambda_const)), lean::prototype<void() const>*>{}, "");
static_assert(std::is_same<decltype(test_invoker(generic_lambda_const, std::declval<bool>())), lean::prototype<void(bool) const>*>{}, "");
static_assert(std::is_same<decltype(test_invoker(generic_lambda_const, std::declval<bool>(), std::declval<int>())), lean::prototype<void(bool, int) const>*>{}, "");

#if __cpp_noexcept_function_type >= 201510L

LEAN_ATTRIBUTE_UNUSED auto generic_lambda_const_noexcept = [] (auto...) noexcept {};
LEAN_ATTRIBUTE_UNUSED auto generic_lambda_mutable_noexcept = [] (auto...) mutable noexcept {};

static_assert(std::is_same<lean::function_type_t<decltype(generic_lambda_mutable_noexcept)>, void() noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(generic_lambda_mutable_noexcept), bool>, void(bool) noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(generic_lambda_mutable_noexcept), bool, int>, void(bool, int) noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(generic_lambda_const_noexcept)>, void() const noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(generic_lambda_const_noexcept), bool>, void(bool) const noexcept>{}, "");
static_assert(std::is_same<lean::function_type_t<decltype(generic_lambda_const_noexcept), bool, int>, void(bool, int) const noexcept>{}, "");

static_assert(std::is_same<decltype(test_invoker(generic_lambda_mutable_noexcept)), lean::prototype<void() noexcept>*>{}, "");
static_assert(std::is_same<decltype(test_invoker(generic_lambda_mutable_noexcept, std::declval<bool>())), lean::prototype<void(bool) noexcept>*>{}, "");
static_assert(std::is_same<decltype(test_invoker(generic_lambda_mutable_noexcept, std::declval<bool>(), std::declval<int>())), lean::prototype<void(bool, int) noexcept>*>{}, "");

static_assert(std::is_same<decltype(test_invoker(generic_lambda_const_noexcept)), lean::prototype<void() const noexcept>*>{}, "");
static_assert(std::is_same<decltype(test_invoker(generic_lambda_const_noexcept, std::declval<bool>())), lean::prototype<void(bool) const noexcept>*>{}, "");
static_assert(std::is_same<decltype(test_invoker(generic_lambda_const_noexcept, std::declval<bool>(), std::declval<int>())), lean::prototype<void(bool, int) const noexcept>*>{}, "");

#endif
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

namespace suite_remove_all_qualifiers
{

template <typename T>
struct test_remove_qualifiers
    : lean::function_rebind<void(),
                            lean::function_return_t<T>,
                            lean::function_arguments_t<lean::prototype, T>>
{
};

template <typename T>
using test_remove_qualifiers_t = typename test_remove_qualifiers<T>::type;

static_assert(std::is_same<test_remove_qualifiers_t<bool()>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() const>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() const &>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() const &&>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() const volatile>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() const volatile &>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() const volatile &&>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() volatile>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() volatile &>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() volatile &&>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() &>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() &&>, bool() >{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<test_remove_qualifiers_t<bool() noexcept>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() const noexcept>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() const & noexcept>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() const && noexcept>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() const volatile noexcept>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() const volatile & noexcept>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() const volatile && noexcept>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() volatile noexcept>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() volatile & noexcept>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() volatile && noexcept>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() & noexcept>, bool()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<bool() && noexcept>, bool() >{}, "");

#endif

static_assert(std::is_same<test_remove_qualifiers_t<void() const volatile &>, void()>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<void(bool) const volatile &>, void(bool)>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<void(bool, int) const volatile &>, void(bool, int)>{}, "");
static_assert(std::is_same<test_remove_qualifiers_t<void(bool, int, float) const volatile &>, void(bool, int, float)>{}, "");

} // namespace suite_remove_all_qualifiers

//-----------------------------------------------------------------------------

int main()
{
    return 0;
}
