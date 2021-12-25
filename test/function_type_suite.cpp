///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <lean/detail/config.hpp> // attributes
#include <lean/function_traits.hpp>

using namespace lean;

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

template <typename F, typename... Args>
constexpr auto test_invoker(F, Args...)
    -> add_pointer_t<prototype<function_type_t<F, Args...>>>
{
    return nullptr;
}

//-----------------------------------------------------------------------------

namespace suite_function_type
{

// Function type

static_assert(is_same<function_type_t<bool()>, bool()>{}, "");
static_assert(is_same<function_type_t<bool() const>, bool() const>{}, "");
static_assert(is_same<function_type_t<bool() const &>, bool() const &>{}, "");
static_assert(is_same<function_type_t<bool() const &&>, bool() const &&>{}, "");
static_assert(is_same<function_type_t<bool() const volatile>, bool() const volatile>{}, "");
static_assert(is_same<function_type_t<bool() const volatile &>, bool() const volatile &>{}, "");
static_assert(is_same<function_type_t<bool() const volatile &&>, bool() const volatile &&>{}, "");
static_assert(is_same<function_type_t<bool() volatile>, bool() volatile>{}, "");
static_assert(is_same<function_type_t<bool() volatile &>, bool() volatile &>{}, "");
static_assert(is_same<function_type_t<bool() volatile &&>, bool() volatile &&>{}, "");
static_assert(is_same<function_type_t<bool() &>, bool() &>{}, "");
static_assert(is_same<function_type_t<bool() &&>, bool() &&>{}, "");

static_assert(is_same<function_type_t<bool(...)>, bool(...)>{}, "");
static_assert(is_same<function_type_t<bool(...) const>, bool(...) const>{}, "");
static_assert(is_same<function_type_t<bool(...) const &>, bool(...) const &>{}, "");
static_assert(is_same<function_type_t<bool(...) const &&>, bool(...) const &&>{}, "");
static_assert(is_same<function_type_t<bool(...) const volatile>, bool(...) const volatile>{}, "");
static_assert(is_same<function_type_t<bool(...) const volatile &>, bool(...) const volatile &>{}, "");
static_assert(is_same<function_type_t<bool(...) const volatile &&>, bool(...) const volatile &&>{}, "");
static_assert(is_same<function_type_t<bool(...) volatile>, bool(...) volatile>{}, "");
static_assert(is_same<function_type_t<bool(...) volatile &>, bool(...) volatile &>{}, "");
static_assert(is_same<function_type_t<bool(...) volatile &&>, bool(...) volatile &&>{}, "");
static_assert(is_same<function_type_t<bool(...) &>, bool(...) &>{}, "");
static_assert(is_same<function_type_t<bool(...) &&>, bool(...) &&>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(is_same<function_type_t<bool() noexcept>, bool() noexcept>{}, "");
static_assert(is_same<function_type_t<bool() const noexcept>, bool() const noexcept>{}, "");
static_assert(is_same<function_type_t<bool() const & noexcept>, bool() const & noexcept>{}, "");
static_assert(is_same<function_type_t<bool() const && noexcept>, bool() const && noexcept>{}, "");
static_assert(is_same<function_type_t<bool() const volatile noexcept>, bool() const volatile noexcept>{}, "");
static_assert(is_same<function_type_t<bool() const volatile & noexcept>, bool() const volatile & noexcept>{}, "");
static_assert(is_same<function_type_t<bool() const volatile && noexcept>, bool() const volatile && noexcept>{}, "");
static_assert(is_same<function_type_t<bool() volatile noexcept>, bool() volatile noexcept>{}, "");
static_assert(is_same<function_type_t<bool() volatile & noexcept>, bool() volatile & noexcept>{}, "");
static_assert(is_same<function_type_t<bool() volatile && noexcept>, bool() volatile && noexcept>{}, "");
static_assert(is_same<function_type_t<bool() & noexcept>, bool() & noexcept>{}, "");
static_assert(is_same<function_type_t<bool() && noexcept>, bool() && noexcept>{}, "");

static_assert(is_same<function_type_t<bool(...) noexcept>, bool(...) noexcept>{}, "");
static_assert(is_same<function_type_t<bool(...) const noexcept>, bool(...) const noexcept>{}, "");
static_assert(is_same<function_type_t<bool(...) const & noexcept>, bool(...) const & noexcept>{}, "");
static_assert(is_same<function_type_t<bool(...) const && noexcept>, bool(...) const && noexcept>{}, "");
static_assert(is_same<function_type_t<bool(...) const volatile noexcept>, bool(...) const volatile noexcept>{}, "");
static_assert(is_same<function_type_t<bool(...) const volatile & noexcept>, bool(...) const volatile & noexcept>{}, "");
static_assert(is_same<function_type_t<bool(...) const volatile && noexcept>, bool(...) const volatile && noexcept>{}, "");
static_assert(is_same<function_type_t<bool(...) volatile noexcept>, bool(...) volatile noexcept>{}, "");
static_assert(is_same<function_type_t<bool(...) volatile & noexcept>, bool(...) volatile & noexcept>{}, "");
static_assert(is_same<function_type_t<bool(...) volatile && noexcept>, bool(...) volatile && noexcept>{}, "");
static_assert(is_same<function_type_t<bool(...) & noexcept>, bool(...) & noexcept>{}, "");
static_assert(is_same<function_type_t<bool(...) && noexcept>, bool(...) && noexcept>{}, "");

#endif

// Function pointer and reference

static_assert(is_same<function_type_t<bool (*)()>, bool()>{}, "");
static_assert(is_same<function_type_t<bool (&)()>, bool()>{}, "");
static_assert(is_same<function_type_t<bool (&&)()>, bool()>{}, "");

static_assert(is_same<function_type_t<bool (*)(...)>, bool(...)>{}, "");
static_assert(is_same<function_type_t<bool (&)(...)>, bool(...)>{}, "");
static_assert(is_same<function_type_t<bool (&&)(...)>, bool(...)>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(is_same<function_type_t<bool (*)() noexcept>, bool() noexcept>{}, "");
static_assert(is_same<function_type_t<bool (&)() noexcept>, bool() noexcept>{}, "");
static_assert(is_same<function_type_t<bool (&&)() noexcept>, bool() noexcept>{}, "");

static_assert(is_same<function_type_t<bool (*)(...) noexcept>, bool(...) noexcept>{}, "");
static_assert(is_same<function_type_t<bool (&)(...) noexcept>, bool(...) noexcept>{}, "");
static_assert(is_same<function_type_t<bool (&&)(...) noexcept>, bool(...) noexcept>{}, "");

#endif

// Function pointer qualifiers

static_assert(is_same<function_type_t<bool (* const)()>, bool()>{}, "");
static_assert(is_same<function_type_t<bool (* const volatile)()>, bool()>{}, "");
static_assert(is_same<function_type_t<bool (* volatile)()>, bool()>{}, "");

// Member function pointer

static_assert(is_same<function_type_t<bool (cls::*)()>, bool()>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() const>, bool() const>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() const &>, bool() const &>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() const &&>, bool() const &&>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() const volatile>, bool() const volatile>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() const volatile &>, bool() const volatile &>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() const volatile &&>, bool() const volatile &&>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() volatile>, bool() volatile>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() volatile &>, bool() volatile &>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() volatile &&>, bool() volatile &&>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() &>, bool() &>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() &&>, bool() &&>{}, "");

static_assert(is_same<function_type_t<bool (cls::*)(...)>, bool(...)>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) const>, bool(...) const>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) const &>, bool(...) const &>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) const &&>, bool(...) const &&>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) const volatile>, bool(...) const volatile>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) const volatile &>, bool(...) const volatile &>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) const volatile &&>, bool(...) const volatile &&>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) volatile>, bool(...) volatile>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) volatile &>, bool(...) volatile &>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) volatile &&>, bool(...) volatile &&>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) &>, bool(...) &>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) &&>, bool(...) &&>{}, "");

static_assert(is_same<function_type_t<void (cls::*)(bool)>, void(bool)>{}, "");
static_assert(is_same<function_type_t<void (cls::*)(bool, int)>, void(bool, int)>{}, "");
static_assert(is_same<function_type_t<void (cls::*)(bool, int, float)>, void(bool, int, float)>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(is_same<function_type_t<bool (cls::*)() noexcept>, bool() noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() const noexcept>, bool() const noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() const & noexcept>, bool() const & noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() const && noexcept>, bool() const && noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() const volatile noexcept>, bool() const volatile noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() const volatile & noexcept>, bool() const volatile & noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() const volatile && noexcept>, bool() const volatile && noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() volatile noexcept>, bool() volatile noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() volatile & noexcept>, bool() volatile & noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() volatile && noexcept>, bool() volatile && noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() & noexcept>, bool() & noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)() && noexcept>, bool() && noexcept>{}, "");

static_assert(is_same<function_type_t<bool (cls::*)(...) noexcept>, bool(...) noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) const noexcept>, bool(...) const noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) const & noexcept>, bool(...) const & noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) const && noexcept>, bool(...) const && noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) const volatile noexcept>, bool(...) const volatile noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) const volatile & noexcept>, bool(...) const volatile & noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) const volatile && noexcept>, bool(...) const volatile && noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) volatile noexcept>, bool(...) volatile noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) volatile & noexcept>, bool(...) volatile & noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) volatile && noexcept>, bool(...) volatile && noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) & noexcept>, bool(...) & noexcept>{}, "");
static_assert(is_same<function_type_t<bool (cls::*)(...) && noexcept>, bool(...) && noexcept>{}, "");

#endif

// Member function pointer qualifiers

static_assert(is_same<function_type_t<bool (cls::* const)()>, bool()>{}, "");
static_assert(is_same<function_type_t<bool (cls::* const volatile)()>, bool()>{}, "");
static_assert(is_same<function_type_t<bool (cls::* volatile)()>, bool()>{}, "");

// Function

constexpr void function(bool);

static_assert(is_same<decltype(test_invoker(function)), prototype<void(bool)>*>{}, "");
static_assert(is_same<decltype(test_invoker(&function)), prototype<void(bool)>*>{}, "");

constexpr bool overloaded_function(bool);
constexpr int overloaded_function(int);

// Overloaded function must be disambiguated manually
static_assert(is_same<decltype(test_invoker(static_cast<bool(&)(bool)>(overloaded_function))), prototype<bool(bool)>*>{}, "");
static_assert(is_same<decltype(test_invoker(static_cast<bool(&)(bool)>(overloaded_function), std::declval<bool>())), prototype<bool(bool)>*>{}, "");
static_assert(is_same<decltype(test_invoker(static_cast<bool(&)(bool)>(overloaded_function), std::declval<int>())), prototype<bool(bool)>*>{}, "");
static_assert(is_same<decltype(test_invoker(static_cast<int(&)(int)>(overloaded_function))), prototype<int(int)>*>{}, "");
static_assert(is_same<decltype(test_invoker(static_cast<int(&)(int)>(overloaded_function), std::declval<int*>())), prototype<int(int)>*>{}, "argument ignored");

#if __cpp_noexcept_function_type >= 201510L

constexpr void function_noexcept(bool) noexcept;

static_assert(is_same<decltype(test_invoker(function_noexcept)), prototype<void(bool) noexcept>*>{}, "");
static_assert(is_same<decltype(test_invoker(&function_noexcept)), prototype<void(bool) noexcept>*>{}, "");

#endif

// Function object

static_assert(is_same<function_type_t<function_object>, void()>{}, "");
static_assert(is_same<function_type_t<decltype(&function_object::operator())>, void()>{}, "");
static_assert(is_same<function_type_t<decltype(&function_object::invoke)>, void()>{}, "");

struct function_object_mutable
{
    void operator()();
};

struct function_object_const
{
    void operator()() const;
};

struct function_object_const_lvalue
{
    void operator()() const &;
};

struct function_object_const_rvalue
{
    void operator()() const &&;
};

struct function_object_const_volatile
{
    void operator()() const volatile;
};

struct function_object_const_volatile_lvalue
{
    void operator()() const volatile &;
};

struct function_object_const_volatile_rvalue
{
    void operator()() const volatile &&;
};

struct function_object_volatile
{
    void operator()() volatile;
};

struct function_object_volatile_lvalue
{
    void operator()() volatile &;
};

struct function_object_volatile_rvalue
{
    void operator()() volatile &&;
};

struct function_object_lvalue
{
    void operator()() &;
};

struct function_object_rvalue
{
    void operator()() &&;
};

static_assert(is_same<function_type_t<function_object_mutable>, void()>{}, "");
static_assert(is_same<function_type_t<const function_object_const>, void() const>{}, "");
static_assert(is_same<function_type_t<const function_object_const_lvalue&>, void() const &>{}, "");
static_assert(is_same<function_type_t<const function_object_const_rvalue&&>, void() const &&>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_const_volatile>, void() const volatile>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_const_volatile_lvalue&>, void() const volatile &>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_const_volatile_rvalue&&>, void() const volatile &&>{}, "");
static_assert(is_same<function_type_t<volatile function_object_volatile>, void() volatile>{}, "");
static_assert(is_same<function_type_t<volatile function_object_volatile_lvalue&>, void() volatile &>{}, "");
static_assert(is_same<function_type_t<volatile function_object_volatile_rvalue&&>, void() volatile &&>{}, "");
static_assert(is_same<function_type_t<function_object_lvalue&>, void() &>{}, "");
static_assert(is_same<function_type_t<function_object_rvalue&&>, void() &&>{}, "");

struct function_object_ellipsis_mutable
{
    void operator()(...);
};

struct function_object_ellipsis_const
{
    void operator()(...) const;
};

struct function_object_ellipsis_const_lvalue
{
    void operator()(...) const &;
};

struct function_object_ellipsis_const_rvalue
{
    void operator()(...) const &&;
};

struct function_object_ellipsis_const_volatile
{
    void operator()(...) const volatile;
};

struct function_object_ellipsis_const_volatile_lvalue
{
    void operator()(...) const volatile &;
};

struct function_object_ellipsis_const_volatile_rvalue
{
    void operator()(...) const volatile &&;
};

struct function_object_ellipsis_volatile
{
    void operator()(...) volatile;
};

struct function_object_ellipsis_volatile_lvalue
{
    void operator()(...) volatile &;
};

struct function_object_ellipsis_volatile_rvalue
{
    void operator()(...) volatile &&;
};

struct function_object_ellipsis_lvalue
{
    void operator()(...) &;
};

struct function_object_ellipsis_rvalue
{
    void operator()(...) &&;
};

static_assert(is_same<function_type_t<function_object_ellipsis_mutable>, void(...)>{}, "");
static_assert(is_same<function_type_t<const function_object_ellipsis_const>, void(...) const>{}, "");
static_assert(is_same<function_type_t<const function_object_ellipsis_const_lvalue&>, void(...) const &>{}, "");
static_assert(is_same<function_type_t<const function_object_ellipsis_const_rvalue&&>, void(...) const &&>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_ellipsis_const_volatile>, void(...) const volatile>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_ellipsis_const_volatile_lvalue&>, void(...) const volatile &>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_ellipsis_const_volatile_rvalue&&>, void(...) const volatile &&>{}, "");
static_assert(is_same<function_type_t<volatile function_object_ellipsis_volatile>, void(...) volatile>{}, "");
static_assert(is_same<function_type_t<volatile function_object_ellipsis_volatile_lvalue&>, void(...) volatile &>{}, "");
static_assert(is_same<function_type_t<volatile function_object_ellipsis_volatile_rvalue&&>, void(...) volatile &&>{}, "");
static_assert(is_same<function_type_t<function_object_ellipsis_lvalue&>, void(...) &>{}, "");
static_assert(is_same<function_type_t<function_object_ellipsis_rvalue&&>, void(...) &&>{}, "");

struct function_object_overload_1
{
    // No reference qualifiers
    void operator()();
    void operator()() const;
    void operator()() const volatile;
    void operator()() volatile;
};

static_assert(is_same<function_type_t<function_object_overload_1>, void()>{}, "");
static_assert(is_same<function_type_t<const function_object_overload_1>, void() const>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_overload_1>, void() const volatile>{}, "");
static_assert(is_same<function_type_t<volatile function_object_overload_1>, void() volatile>{}, "");

struct function_object_ellipsis_overload_1
{
    // No reference qualifiers
    void operator()(...);
    void operator()(...) const;
    void operator()(...) const volatile;
    void operator()(...) volatile;
};

static_assert(is_same<function_type_t<function_object_ellipsis_overload_1>, void(...)>{}, "");
static_assert(is_same<function_type_t<const function_object_ellipsis_overload_1>, void(...) const>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_ellipsis_overload_1>, void(...) const volatile>{}, "");
static_assert(is_same<function_type_t<volatile function_object_ellipsis_overload_1>, void(...) volatile>{}, "");

struct function_object_overload_2
{
    // Lvalue-reference qualifiers
    void operator()() &;
    void operator()() const &;
    void operator()() const volatile &;
    void operator()() volatile &;
};

static_assert(is_same<function_type_t<function_object_overload_2&>, void() &>{}, "");
static_assert(is_same<function_type_t<const function_object_overload_2&>, void() const &>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_overload_2&>, void() const volatile &>{}, "");
static_assert(is_same<function_type_t<volatile function_object_overload_2&>, void() volatile &>{}, "");

struct function_object_ellipsis_overload_2
{
    // Lvalue-reference qualifiers
    void operator()(...) &;
    void operator()(...) const &;
    void operator()(...) const volatile &;
    void operator()(...) volatile &;
};

static_assert(is_same<function_type_t<function_object_ellipsis_overload_2&>, void(...) &>{}, "");
static_assert(is_same<function_type_t<const function_object_ellipsis_overload_2&>, void(...) const &>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_ellipsis_overload_2&>, void(...) const volatile &>{}, "");
static_assert(is_same<function_type_t<volatile function_object_ellipsis_overload_2&>, void(...) volatile &>{}, "");

struct function_object_overload_3
{
    // Rvalue-reference qualifiers
    void operator()() &&;
    void operator()() const &&;
    void operator()() const volatile &&;
    void operator()() volatile &&;
};

static_assert(is_same<function_type_t<function_object_overload_3&&>, void() &&>{}, "");
static_assert(is_same<function_type_t<const function_object_overload_3&&>, void() const &&>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_overload_3&&>, void() const volatile &&>{}, "");
static_assert(is_same<function_type_t<volatile function_object_overload_3&&>, void() volatile &&>{}, "");

struct function_object_ellipsis_overload_3
{
    // Rvalue-reference qualifiers
    void operator()(...) &&;
    void operator()(...) const &&;
    void operator()(...) const volatile &&;
    void operator()(...) volatile &&;
};

static_assert(is_same<function_type_t<function_object_ellipsis_overload_3&&>, void(...) &&>{}, "");
static_assert(is_same<function_type_t<const function_object_ellipsis_overload_3&&>, void(...) const &&>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_ellipsis_overload_3&&>, void(...) const volatile &&>{}, "");
static_assert(is_same<function_type_t<volatile function_object_ellipsis_overload_3&&>, void(...) volatile &&>{}, "");

struct function_object_overload_4
{
    // Reference qualifiers
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
    void operator()() volatile &;
    void operator()() volatile &&;
};

static_assert(is_same<function_type_t<function_object_overload_4&>, void() &>{}, "");
static_assert(is_same<function_type_t<function_object_overload_4&&>, void() &&>{}, "");
static_assert(is_same<function_type_t<const function_object_overload_4&>, void() const &>{}, "");
static_assert(is_same<function_type_t<const function_object_overload_4&&>, void() const &&>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_overload_4&>, void() const volatile &>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_overload_4&&>, void() const volatile &&>{}, "");
static_assert(is_same<function_type_t<volatile function_object_overload_4&>, void() volatile &>{}, "");
static_assert(is_same<function_type_t<volatile function_object_overload_4&&>, void() volatile &&>{}, "");

struct function_object_ellipsis_overload_4
{
    // Reference qualifiers
    void operator()(...) &;
    void operator()(...) &&;
    void operator()(...) const &;
    void operator()(...) const &&;
    void operator()(...) const volatile &;
    void operator()(...) const volatile &&;
    void operator()(...) volatile &;
    void operator()(...) volatile &&;
};

static_assert(is_same<function_type_t<function_object_ellipsis_overload_4&>, void(...) &>{}, "");
static_assert(is_same<function_type_t<function_object_ellipsis_overload_4&&>, void(...) &&>{}, "");
static_assert(is_same<function_type_t<const function_object_ellipsis_overload_4&>, void(...) const &>{}, "");
static_assert(is_same<function_type_t<const function_object_ellipsis_overload_4&&>, void(...) const &&>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_ellipsis_overload_4&>, void(...) const volatile &>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_ellipsis_overload_4&&>, void(...) const volatile &&>{}, "");
static_assert(is_same<function_type_t<volatile function_object_ellipsis_overload_4&>, void(...) volatile &>{}, "");
static_assert(is_same<function_type_t<volatile function_object_ellipsis_overload_4&&>, void(...) volatile &&>{}, "");

struct function_object_overload_arg
{
    void operator()(bool);
    void operator()(bool, int);
    void operator()(int);
};

static_assert(is_same<function_type_t<function_object_overload_arg, bool>, void(bool)>{}, "");
static_assert(is_same<function_type_t<function_object_overload_arg, bool, int>, void(bool, int)>{}, "");
static_assert(is_same<function_type_t<function_object_overload_arg, int>, void(int)>{}, "");

struct templated_function_object
{
    template <typename... Args>
    void operator()(Args...);
};

static_assert(is_same<function_type_t<templated_function_object>, void()>{}, "");
static_assert(is_same<function_type_t<templated_function_object, bool>, void(bool)>{}, "");
static_assert(is_same<function_type_t<templated_function_object, bool, int>, void(bool, int)>{}, "");
static_assert(is_same<function_type_t<templated_function_object, bool, int, float>, void(bool, int, float)>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(is_same<function_type_t<function_object_noexcept>, void() noexcept>{}, "");
static_assert(is_same<function_type_t<decltype(&function_object_noexcept::operator())>, void() noexcept>{}, "");
static_assert(is_same<function_type_t<decltype(&function_object_noexcept::invoke)>, void() noexcept>{}, "");

struct function_object_mutable_noexcept
{
    void operator()() noexcept;
};

struct function_object_const_noexcept
{
    void operator()() const noexcept;
};

struct function_object_const_lvalue_noexcept
{
    void operator()() const & noexcept;
};

struct function_object_const_rvalue_noexcept
{
    void operator()() const && noexcept;
};

struct function_object_const_volatile_noexcept
{
    void operator()() const volatile noexcept;
};

struct function_object_const_volatile_lvalue_noexcept
{
    void operator()() const volatile & noexcept;
};

struct function_object_const_volatile_rvalue_noexcept
{
    void operator()() const volatile && noexcept;
};

struct function_object_volatile_noexcept
{
    void operator()() volatile noexcept;
};

struct function_object_volatile_lvalue_noexcept
{
    void operator()() volatile & noexcept;
};

struct function_object_volatile_rvalue_noexcept
{
    void operator()() volatile && noexcept;
};

struct function_object_lvalue_noexcept
{
    void operator()() & noexcept;
};

struct function_object_rvalue_noexcept
{
    void operator()() && noexcept;
};

static_assert(is_same<function_type_t<function_object_mutable_noexcept>, void() noexcept>{}, "");
static_assert(is_same<function_type_t<const function_object_const_noexcept>, void() const noexcept>{}, "");
static_assert(is_same<function_type_t<const function_object_const_lvalue_noexcept&>, void() const & noexcept>{}, "");
static_assert(is_same<function_type_t<const function_object_const_rvalue_noexcept&&>, void() const && noexcept>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_const_volatile_noexcept>, void() const volatile noexcept>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_const_volatile_lvalue_noexcept&>, void() const volatile & noexcept>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_const_volatile_rvalue_noexcept&&>, void() const volatile && noexcept>{}, "");
static_assert(is_same<function_type_t<volatile function_object_volatile_noexcept>, void() volatile noexcept>{}, "");
static_assert(is_same<function_type_t<volatile function_object_volatile_lvalue_noexcept&>, void() volatile & noexcept>{}, "");
static_assert(is_same<function_type_t<volatile function_object_volatile_rvalue_noexcept&&>, void() volatile && noexcept>{}, "");
static_assert(is_same<function_type_t<function_object_lvalue_noexcept&>, void() & noexcept>{}, "");
static_assert(is_same<function_type_t<function_object_rvalue_noexcept&&>, void() && noexcept>{}, "");

struct function_object_ellipsis_mutable_noexcept
{
    void operator()(...) noexcept;
};

struct function_object_ellipsis_const_noexcept
{
    void operator()(...) const noexcept;
};

struct function_object_ellipsis_const_lvalue_noexcept
{
    void operator()(...) const & noexcept;
};

struct function_object_ellipsis_const_rvalue_noexcept
{
    void operator()(...) const && noexcept;
};

struct function_object_ellipsis_const_volatile_noexcept
{
    void operator()(...) const volatile noexcept;
};

struct function_object_ellipsis_const_volatile_lvalue_noexcept
{
    void operator()(...) const volatile & noexcept;
};

struct function_object_ellipsis_const_volatile_rvalue_noexcept
{
    void operator()(...) const volatile && noexcept;
};

struct function_object_ellipsis_volatile_noexcept
{
    void operator()(...) volatile noexcept;
};

struct function_object_ellipsis_volatile_lvalue_noexcept
{
    void operator()(...) volatile & noexcept;
};

struct function_object_ellipsis_volatile_rvalue_noexcept
{
    void operator()(...) volatile && noexcept;
};

struct function_object_ellipsis_lvalue_noexcept
{
    void operator()(...) & noexcept;
};

struct function_object_ellipsis_rvalue_noexcept
{
    void operator()(...) && noexcept;
};

static_assert(is_same<function_type_t<function_object_ellipsis_mutable_noexcept>, void(...) noexcept>{}, "");
static_assert(is_same<function_type_t<const function_object_ellipsis_const_noexcept>, void(...) const noexcept>{}, "");
static_assert(is_same<function_type_t<const function_object_ellipsis_const_lvalue_noexcept&>, void(...) const & noexcept>{}, "");
static_assert(is_same<function_type_t<const function_object_ellipsis_const_rvalue_noexcept&&>, void(...) const && noexcept>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_ellipsis_const_volatile_noexcept>, void(...) const volatile noexcept>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_ellipsis_const_volatile_lvalue_noexcept&>, void(...) const volatile & noexcept>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_ellipsis_const_volatile_rvalue_noexcept&&>, void(...) const volatile && noexcept>{}, "");
static_assert(is_same<function_type_t<volatile function_object_ellipsis_volatile_noexcept>, void(...) volatile noexcept>{}, "");
static_assert(is_same<function_type_t<volatile function_object_ellipsis_volatile_lvalue_noexcept&>, void(...) volatile & noexcept>{}, "");
static_assert(is_same<function_type_t<volatile function_object_ellipsis_volatile_rvalue_noexcept&&>, void(...) volatile && noexcept>{}, "");
static_assert(is_same<function_type_t<function_object_ellipsis_lvalue_noexcept&>, void(...) & noexcept>{}, "");
static_assert(is_same<function_type_t<function_object_ellipsis_rvalue_noexcept&&>, void(...) && noexcept>{}, "");

struct function_object_noexcept_overload_1
{
    void operator()() noexcept;
    void operator()() const noexcept;
    void operator()() const volatile noexcept;
    void operator()() volatile noexcept;
};

static_assert(is_same<function_type_t<function_object_noexcept_overload_1>, void() noexcept>{}, "");
static_assert(is_same<function_type_t<const function_object_noexcept_overload_1>, void() const noexcept>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_noexcept_overload_1>, void() const volatile noexcept>{}, "");
static_assert(is_same<function_type_t<volatile function_object_noexcept_overload_1>, void() volatile noexcept>{}, "");

struct function_object_noexcept_overload_2
{
    void operator()() & noexcept;
    void operator()() const & noexcept;
    void operator()() const volatile & noexcept;
    void operator()() volatile & noexcept;
};

static_assert(is_same<function_type_t<function_object_noexcept_overload_2&>, void() & noexcept>{}, "");
static_assert(is_same<function_type_t<const function_object_noexcept_overload_2&>, void() const & noexcept>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_noexcept_overload_2&>, void() const volatile & noexcept>{}, "");
static_assert(is_same<function_type_t<volatile function_object_noexcept_overload_2&>, void() volatile & noexcept>{}, "");

struct function_object_noexcept_overload_3
{
    void operator()() && noexcept;
    void operator()() const && noexcept;
    void operator()() const volatile && noexcept;
    void operator()() volatile && noexcept;
};

static_assert(is_same<function_type_t<function_object_noexcept_overload_3&&>, void() && noexcept>{}, "");
static_assert(is_same<function_type_t<const function_object_noexcept_overload_3&&>, void() const && noexcept>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_noexcept_overload_3&&>, void() const volatile && noexcept>{}, "");
static_assert(is_same<function_type_t<volatile function_object_noexcept_overload_3&&>, void() volatile && noexcept>{}, "");

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

static_assert(is_same<function_type_t<function_object_noexcept_overload_4&>, void() & noexcept>{}, "");
static_assert(is_same<function_type_t<function_object_noexcept_overload_4&&>, void() && noexcept>{}, "");
static_assert(is_same<function_type_t<const function_object_noexcept_overload_4&>, void() const & noexcept>{}, "");
static_assert(is_same<function_type_t<const function_object_noexcept_overload_4&&>, void() const && noexcept>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_noexcept_overload_4&>, void() const volatile & noexcept>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_noexcept_overload_4&&>, void() const volatile && noexcept>{}, "");
static_assert(is_same<function_type_t<volatile function_object_noexcept_overload_4&>, void() volatile & noexcept>{}, "");
static_assert(is_same<function_type_t<volatile function_object_noexcept_overload_4&&>, void() volatile && noexcept>{}, "");

struct function_object_noexcept_overload_arg
{
    void operator()(bool) noexcept;
    void operator()(bool, int) noexcept;
    void operator()(int) noexcept;
};

static_assert(is_same<function_type_t<function_object_noexcept_overload_arg, bool>, void(bool) noexcept>{}, "");
static_assert(is_same<function_type_t<function_object_noexcept_overload_arg, bool, int>, void(bool, int) noexcept>{}, "");
static_assert(is_same<function_type_t<function_object_noexcept_overload_arg, int>, void(int) noexcept>{}, "");

struct templated_function_object_noexcept
{
    template <typename... Args>
    void operator()(Args...) noexcept;
};

static_assert(is_same<function_type_t<templated_function_object_noexcept>, void() noexcept>{}, "");
static_assert(is_same<function_type_t<templated_function_object_noexcept, bool>, void(bool) noexcept>{}, "");
static_assert(is_same<function_type_t<templated_function_object_noexcept, bool, int>, void(bool, int) noexcept>{}, "");
static_assert(is_same<function_type_t<templated_function_object_noexcept, bool, int, float>, void(bool, int, float) noexcept>{}, "");

#endif

// Lamdba

LEAN_ATTRIBUTE_UNUSED auto lambda_const = [] {};
LEAN_ATTRIBUTE_UNUSED auto lambda_mutable = [] () mutable {};

static_assert(is_same<function_type_t<decltype(lambda_const)>, void() const>{}, "");
static_assert(is_same<function_type_t<decltype(lambda_mutable)>, void()>{}, "");

#if __cpp_noexcept_function_type >= 201510L

LEAN_ATTRIBUTE_UNUSED auto lambda_const_noexcept = [] () noexcept {};
LEAN_ATTRIBUTE_UNUSED auto lambda_mutable_noexcept = [] () mutable noexcept {};

static_assert(is_same<function_type_t<decltype(lambda_const_noexcept)>, void() const noexcept>{}, "");
static_assert(is_same<function_type_t<decltype(lambda_mutable_noexcept)>, void() noexcept>{}, "");

#endif

// Generic lambda

#if __cpp_generic_lambdas >= 201304L

LEAN_ATTRIBUTE_UNUSED auto generic_lambda_const = [] (auto...) {};
LEAN_ATTRIBUTE_UNUSED auto generic_lambda_mutable = [] (auto...) mutable {};

static_assert(is_same<function_type_t<decltype(generic_lambda_mutable)>, void()>{}, "");
static_assert(is_same<function_type_t<decltype(generic_lambda_mutable), bool>, void(bool)>{}, "");
static_assert(is_same<function_type_t<decltype(generic_lambda_mutable), bool, int>, void(bool, int)>{}, "");

static_assert(is_same<decltype(test_invoker(generic_lambda_mutable)), prototype<void()>*>{}, "");
static_assert(is_same<decltype(test_invoker(generic_lambda_mutable, std::declval<bool>())), prototype<void(bool)>*>{}, "");
static_assert(is_same<decltype(test_invoker(generic_lambda_mutable, std::declval<bool>(), std::declval<int>())), prototype<void(bool, int)>*>{}, "");

static_assert(is_same<function_type_t<decltype(generic_lambda_const)>, void() const>{}, "");
static_assert(is_same<function_type_t<decltype(generic_lambda_const), bool>, void(bool) const>{}, "");
static_assert(is_same<function_type_t<decltype(generic_lambda_const), bool, int>, void(bool, int) const>{}, "");

static_assert(is_same<decltype(test_invoker(generic_lambda_const)), prototype<void() const>*>{}, "");
static_assert(is_same<decltype(test_invoker(generic_lambda_const, std::declval<bool>())), prototype<void(bool) const>*>{}, "");
static_assert(is_same<decltype(test_invoker(generic_lambda_const, std::declval<bool>(), std::declval<int>())), prototype<void(bool, int) const>*>{}, "");

#if __cpp_noexcept_function_type >= 201510L

LEAN_ATTRIBUTE_UNUSED auto generic_lambda_const_noexcept = [] (auto...) noexcept {};
LEAN_ATTRIBUTE_UNUSED auto generic_lambda_mutable_noexcept = [] (auto...) mutable noexcept {};

static_assert(is_same<function_type_t<decltype(generic_lambda_mutable_noexcept)>, void() noexcept>{}, "");
static_assert(is_same<function_type_t<decltype(generic_lambda_mutable_noexcept), bool>, void(bool) noexcept>{}, "");
static_assert(is_same<function_type_t<decltype(generic_lambda_mutable_noexcept), bool, int>, void(bool, int) noexcept>{}, "");
static_assert(is_same<function_type_t<decltype(generic_lambda_const_noexcept)>, void() const noexcept>{}, "");
static_assert(is_same<function_type_t<decltype(generic_lambda_const_noexcept), bool>, void(bool) const noexcept>{}, "");
static_assert(is_same<function_type_t<decltype(generic_lambda_const_noexcept), bool, int>, void(bool, int) const noexcept>{}, "");

static_assert(is_same<decltype(test_invoker(generic_lambda_mutable_noexcept)), prototype<void() noexcept>*>{}, "");
static_assert(is_same<decltype(test_invoker(generic_lambda_mutable_noexcept, std::declval<bool>())), prototype<void(bool) noexcept>*>{}, "");
static_assert(is_same<decltype(test_invoker(generic_lambda_mutable_noexcept, std::declval<bool>(), std::declval<int>())), prototype<void(bool, int) noexcept>*>{}, "");

static_assert(is_same<decltype(test_invoker(generic_lambda_const_noexcept)), prototype<void() const noexcept>*>{}, "");
static_assert(is_same<decltype(test_invoker(generic_lambda_const_noexcept, std::declval<bool>())), prototype<void(bool) const noexcept>*>{}, "");
static_assert(is_same<decltype(test_invoker(generic_lambda_const_noexcept, std::declval<bool>(), std::declval<int>())), prototype<void(bool, int) const noexcept>*>{}, "");

#endif
#endif

} // namespace suite_function_type

//-----------------------------------------------------------------------------

int main()
{
    return 0;
}