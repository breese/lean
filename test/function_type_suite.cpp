///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <utility> // std::forward
#include <lean/detail/config.hpp> // attributes
#include <lean/function_traits.hpp>
#include <lean/type_traits.hpp>

using namespace lean;

//-----------------------------------------------------------------------------

namespace lean
{
namespace impl
{

template <typename, typename, typename = void>
struct function_type_void
{
    using type = void;
};

template <typename T, typename... Args>
struct function_type_void<T,
                          prototype<Args...>,
                          void_t<function_type_t<T, Args...>>>
    : function_type<T, Args...>
{
};

} // namespace impl

template <typename T, typename... Args>
using function_type_void_t = typename impl::function_type_void<T, prototype<Args...>>::type;

} // namespace lean

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

} // suite_function_type

//-----------------------------------------------------------------------------

namespace suite_function
{

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

} // namespace suite_function

//-----------------------------------------------------------------------------

namespace suite_member_function
{

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

} // namespace suite_member_function

//-----------------------------------------------------------------------------

namespace suite_function_object
{

static_assert(is_same<function_type_t<function_object>, void()>{}, "");
static_assert(is_same<function_type_t<decltype(&function_object::operator())>, void()>{}, "");
static_assert(is_same<function_type_t<decltype(&function_object::invoke)>, void()>{}, "");

struct function_object_mutable
{
    void operator()();
};

struct function_object_lvalue
{
    void operator()() &;
};

struct function_object_rvalue
{
    void operator()() &&;
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

static_assert(is_same<function_type_t<function_object_mutable>, void()>{}, "");
static_assert(is_same<function_type_t<function_object_lvalue>, void() &>{}, "");
static_assert(is_same<function_type_t<function_object_lvalue &>, void() &>{}, "");
static_assert(is_same<function_type_t<function_object_rvalue &&>, void() &&>{}, "");
static_assert(is_same<function_type_t<function_object_const const>, void() const>{}, "");
static_assert(is_same<function_type_t<function_object_const_lvalue const>, void() const &>{}, "");
static_assert(is_same<function_type_t<function_object_const_lvalue const &>, void() const &>{}, "");
static_assert(is_same<function_type_t<function_object_const_rvalue const &&>, void() const &&>{}, "");
static_assert(is_same<function_type_t<function_object_volatile volatile>, void() volatile>{}, "");
static_assert(is_same<function_type_t<function_object_volatile_lvalue volatile>, void() volatile &>{}, "");
static_assert(is_same<function_type_t<function_object_volatile_lvalue volatile &>, void() volatile &>{}, "");
static_assert(is_same<function_type_t<function_object_volatile_rvalue volatile &&>, void() volatile &&>{}, "");
static_assert(is_same<function_type_t<function_object_const_volatile const volatile>, void() const volatile>{}, "");
static_assert(is_same<function_type_t<function_object_const_volatile_lvalue const volatile>, void() const volatile &>{}, "");
static_assert(is_same<function_type_t<function_object_const_volatile_lvalue const volatile &>, void() const volatile &>{}, "");
static_assert(is_same<function_type_t<function_object_const_volatile_rvalue const volatile &&>, void() const volatile &&>{}, "");

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
static_assert(is_same<function_type_t<const function_object_ellipsis_const_lvalue>, void(...) const &>{}, "");
static_assert(is_same<function_type_t<const function_object_ellipsis_const_lvalue&>, void(...) const &>{}, "");
static_assert(is_same<function_type_t<const function_object_ellipsis_const_rvalue&&>, void(...) const &&>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_ellipsis_const_volatile>, void(...) const volatile>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_ellipsis_const_volatile_lvalue>, void(...) const volatile &>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_ellipsis_const_volatile_lvalue&>, void(...) const volatile &>{}, "");
static_assert(is_same<function_type_t<const volatile function_object_ellipsis_const_volatile_rvalue&&>, void(...) const volatile &&>{}, "");
static_assert(is_same<function_type_t<volatile function_object_ellipsis_volatile>, void(...) volatile>{}, "");
static_assert(is_same<function_type_t<volatile function_object_ellipsis_volatile_lvalue>, void(...) volatile &>{}, "");
static_assert(is_same<function_type_t<volatile function_object_ellipsis_volatile_lvalue&>, void(...) volatile &>{}, "");
static_assert(is_same<function_type_t<volatile function_object_ellipsis_volatile_rvalue&&>, void(...) volatile &&>{}, "");
static_assert(is_same<function_type_t<function_object_ellipsis_lvalue>, void(...) &>{}, "");
static_assert(is_same<function_type_t<function_object_ellipsis_lvalue&>, void(...) &>{}, "");
static_assert(is_same<function_type_t<function_object_ellipsis_rvalue&&>, void(...) &&>{}, "");

} // namespace suite_function_object

//-----------------------------------------------------------------------------

namespace suite_function_object_qual
{

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

#endif

} // namespace suite_function_object_qual

//-----------------------------------------------------------------------------

namespace suite_function_object_value
{

// Cannot disambiguate all cases as there is no partial ordering between const
// and volatile [basic.type.qualifier]/5

struct function_object_0000
{
    // void operator()();
    // void operator()() const;
    // void operator()() volatile;
    // void operator()() const volatile;
};

static_assert(is_same<void, function_type_void_t<function_object_0000>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const volatile &&>>{}, "");

struct function_object_0001
{
    void operator()();
    // void operator()() const;
    // void operator()() volatile;
    // void operator()() const volatile;
};

static_assert(is_same<void(), function_type_void_t<function_object_0001>>{}, "");
static_assert(is_same<void(), function_type_void_t<function_object_0001 &>>{}, "");
static_assert(is_same<void(), function_type_void_t<function_object_0001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile &&>>{}, "");

struct function_object_0010
{
    // void operator()();
    void operator()() const;
    // void operator()() volatile;
    // void operator()() const volatile;
};

static_assert(is_same<void() const, function_type_void_t<function_object_0010>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_0010 &>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_0010 &&>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_0010 const>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_0010 const &>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_0010 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile &&>>{}, "");

struct function_object_0011
{
    void operator()();
    void operator()() const;
    // void operator()() volatile;
    // void operator()() const volatile;
};

static_assert(is_same<void(), function_type_void_t<function_object_0011>>{}, "");
static_assert(is_same<void(), function_type_void_t<function_object_0011 &>>{}, "");
static_assert(is_same<void(), function_type_void_t<function_object_0011 &&>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_0011 const>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_0011 const &>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_0011 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile &&>>{}, "");

struct function_object_0100
{
    // void operator()();
    // void operator()() const;
    void operator()() volatile;
    // void operator()() const volatile;
};

static_assert(is_same<void() volatile, function_type_void_t<function_object_0100>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_0100 &>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_0100 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const &&>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_0100 volatile>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_0100 volatile &>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_0100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile &&>>{}, "");

struct function_object_0101
{
    void operator()();
    // void operator()() const;
    void operator()() volatile;
    // void operator()() const volatile;
};

static_assert(is_same<void(), function_type_void_t<function_object_0101>>{}, "");
static_assert(is_same<void(), function_type_void_t<function_object_0101 &>>{}, "");
static_assert(is_same<void(), function_type_void_t<function_object_0101 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const &&>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_0101 volatile>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_0101 volatile &>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_0101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile &&>>{}, "");

struct function_object_0110
{
    // void operator()();
    void operator()() const;
    void operator()() volatile;
    // void operator()() const volatile;
};

static_assert(is_same<void, function_type_void_t<function_object_0110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 &&>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_0110 const>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_0110 const &>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_0110 const &&>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_0110 volatile>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_0110 volatile &>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_0110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile &&>>{}, "");

struct function_object_0111
{
    void operator()();
    void operator()() const;
    void operator()() volatile;
    // void operator()() const volatile;
};

static_assert(is_same<void(), function_type_void_t<function_object_0111>>{}, "");
static_assert(is_same<void(), function_type_void_t<function_object_0111 &>>{}, "");
static_assert(is_same<void(), function_type_void_t<function_object_0111 &&>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_0111 const>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_0111 const &>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_0111 const &&>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_0111 volatile>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_0111 volatile &>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_0111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile &&>>{}, "");

struct function_object_1000
{
    // void operator()();
    // void operator()() const;
    // void operator()() volatile;
    void operator()() const volatile;
};

static_assert(is_same<void() const volatile, function_type_void_t<function_object_1000>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1000 &>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1000 &&>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1000 const>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1000 const &>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1000 const &&>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1000 volatile>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1000 volatile &>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1000 const volatile>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1000 const volatile &&>>{}, "");

struct function_object_1001
{
    void operator()();
    // void operator()() const;
    // void operator()() volatile;
    void operator()() const volatile;
};

static_assert(is_same<void(), function_type_void_t<function_object_1001>>{}, "");
static_assert(is_same<void(), function_type_void_t<function_object_1001 &>>{}, "");
static_assert(is_same<void(), function_type_void_t<function_object_1001 &&>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1001 const>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1001 const &>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1001 const &&>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1001 volatile>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1001 volatile &>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1001 const volatile>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1001 const volatile &&>>{}, "");

struct function_object_1010
{
    // void operator()();
    void operator()() const;
    // void operator()() volatile;
    void operator()() const volatile;
};

static_assert(is_same<void() const, function_type_void_t<function_object_1010>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_1010 &>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_1010 &&>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_1010 const>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_1010 const &>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_1010 const &&>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1010 volatile>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1010 volatile &>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1010 const volatile>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1010 const volatile &&>>{}, "");

struct function_object_1011
{
    void operator()();
    void operator()() const;
    // void operator()() volatile;
    void operator()() const volatile;
};

static_assert(is_same<void(), function_type_void_t<function_object_1011>>{}, "");
static_assert(is_same<void(), function_type_void_t<function_object_1011 &>>{}, "");
static_assert(is_same<void(), function_type_void_t<function_object_1011 &&>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_1011 const>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_1011 const &>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_1011 const &&>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1011 volatile>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1011 volatile &>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1011 const volatile>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1011 const volatile &&>>{}, "");

struct function_object_1100
{
    // void operator()();
    // void operator()() const;
    void operator()() volatile;
    void operator()() const volatile;
};

static_assert(is_same<void() volatile, function_type_void_t<function_object_1100>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_1100 &>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_1100 &&>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1100 const>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1100 const &>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1100 const &&>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_1100 volatile>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_1100 volatile &>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_1100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1100 const volatile>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1100 const volatile &&>>{}, "");


struct function_object_1101
{
    void operator()();
    // void operator()() const;
    void operator()() volatile;
    void operator()() const volatile;
};

static_assert(is_same<void(), function_type_void_t<function_object_1101>>{}, "");
static_assert(is_same<void(), function_type_void_t<function_object_1101 &>>{}, "");
static_assert(is_same<void(), function_type_void_t<function_object_1101 &&>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1101 const>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1101 const &>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1101 const &&>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_1101 volatile>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_1101 volatile &>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_1101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1101 const volatile>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1101 const volatile &&>>{}, "");

struct function_object_1110
{
    // void operator()();
    void operator()() const;
    void operator()() volatile;
    void operator()() const volatile;
};

static_assert(is_same<void, function_type_void_t<function_object_1110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 &&>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_1110 const>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_1110 const &>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_1110 const &&>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_1110 volatile>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_1110 volatile &>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_1110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1110 const volatile>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1110 const volatile &&>>{}, "");

struct function_object_1111
{
    void operator()();
    void operator()() const;
    void operator()() volatile;
    void operator()() const volatile;
};

static_assert(is_same<void(), function_type_void_t<function_object_1111>>{}, "");
static_assert(is_same<void(), function_type_void_t<function_object_1111 &>>{}, "");
static_assert(is_same<void(), function_type_void_t<function_object_1111 &&>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_1111 const>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_1111 const &>>{}, "");
static_assert(is_same<void() const, function_type_void_t<function_object_1111 const &&>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_1111 volatile>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_1111 volatile &>>{}, "");
static_assert(is_same<void() volatile, function_type_void_t<function_object_1111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1111 const volatile>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile, function_type_void_t<function_object_1111 const volatile &&>>{}, "");

} // namespace suite_function_object_value

//-----------------------------------------------------------------------------

namespace suite_function_object_value_ellipsis
{

struct function_object_000
{
    // void operator()(...);
    // void operator()(...) const;
    // void operator()(...) volatile;
    // void operator()(...) const volatile;
};

static_assert(is_same<void, function_type_void_t<function_object_000>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 const volatile &&>>{}, "");

struct function_object_0001
{
    void operator()(...);
    // void operator()(...) const;
    // void operator()(...) volatile;
    // void operator()(...) const volatile;
};

static_assert(is_same<void(...), function_type_void_t<function_object_0001>>{}, "");
static_assert(is_same<void(...), function_type_void_t<function_object_0001 &>>{}, "");
static_assert(is_same<void(...), function_type_void_t<function_object_0001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile &&>>{}, "");

struct function_object_0010
{
    // void operator()(...);
    void operator()(...) const;
    // void operator()(...) volatile;
    // void operator()(...) const volatile;
};

static_assert(is_same<void(...) const, function_type_void_t<function_object_0010>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_0010 &>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_0010 &&>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_0010 const>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_0010 const &>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_0010 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile &&>>{}, "");

struct function_object_0011
{
    void operator()(...);
    void operator()(...) const;
    // void operator()(...) volatile;
    // void operator()(...) const volatile;
};

static_assert(is_same<void(...), function_type_void_t<function_object_0011>>{}, "");
static_assert(is_same<void(...), function_type_void_t<function_object_0011 &>>{}, "");
static_assert(is_same<void(...), function_type_void_t<function_object_0011 &&>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_0011 const>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_0011 const &>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_0011 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile &&>>{}, "");

struct function_object_0100
{
    // void operator()(...);
    // void operator()(...) const;
    void operator()(...) volatile;
    // void operator()(...) const volatile;
};

static_assert(is_same<void(...) volatile, function_type_void_t<function_object_0100>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_0100 &>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_0100 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const &&>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_0100 volatile>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_0100 volatile &>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_0100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile &&>>{}, "");

struct function_object_0101
{
    void operator()(...);
    // void operator()(...) const;
    void operator()(...) volatile;
    // void operator()(...) const volatile;
};

static_assert(is_same<void(...), function_type_void_t<function_object_0101>>{}, "");
static_assert(is_same<void(...), function_type_void_t<function_object_0101 &>>{}, "");
static_assert(is_same<void(...), function_type_void_t<function_object_0101 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const &&>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_0101 volatile>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_0101 volatile &>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_0101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile &&>>{}, "");

struct function_object_0110
{
    // void operator()(...);
    void operator()(...) const;
    void operator()(...) volatile;
    // void operator()(...) const volatile;
};

static_assert(is_same<void, function_type_void_t<function_object_0110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 &&>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_0110 const>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_0110 const &>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_0110 const &&>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_0110 volatile>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_0110 volatile &>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_0110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile &&>>{}, "");

struct function_object_0111
{
    void operator()(...);
    void operator()(...) const;
    void operator()(...) volatile;
    // void operator()(...) const volatile;
};

static_assert(is_same<void(...), function_type_void_t<function_object_0111>>{}, "");
static_assert(is_same<void(...), function_type_void_t<function_object_0111 &>>{}, "");
static_assert(is_same<void(...), function_type_void_t<function_object_0111 &&>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_0111 const>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_0111 const &>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_0111 const &&>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_0111 volatile>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_0111 volatile &>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_0111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile &&>>{}, "");

struct function_object_1000
{
    // void operator()(...);
    // void operator()(...) const;
    // void operator()(...) volatile;
    void operator()(...) const volatile;
};

static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1000>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1000 &>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1000 &&>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1000 const>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1000 const &>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1000 const &&>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1000 volatile>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1000 volatile &>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1000 volatile &&>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1000 const volatile>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1000 const volatile &>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1000 const volatile &&>>{}, "");

struct function_object_1001
{
    void operator()(...);
    // void operator()(...) const;
    // void operator()(...) volatile;
    void operator()(...) const volatile;
};

static_assert(is_same<void(...), function_type_void_t<function_object_1001>>{}, "");
static_assert(is_same<void(...), function_type_void_t<function_object_1001 &>>{}, "");
static_assert(is_same<void(...), function_type_void_t<function_object_1001 &&>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1001 const>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1001 const &>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1001 const &&>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1001 volatile>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1001 volatile &>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1001 volatile &&>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1001 const volatile>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1001 const volatile &>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1001 const volatile &&>>{}, "");

struct function_object_1010
{
    // void operator()(...);
    void operator()(...) const;
    // void operator()(...) volatile;
    void operator()(...) const volatile;
};

static_assert(is_same<void(...) const, function_type_void_t<function_object_1010>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_1010 &>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_1010 &&>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_1010 const>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_1010 const &>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_1010 const &&>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1010 volatile>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1010 volatile &>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1010 volatile &&>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1010 const volatile>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1010 const volatile &>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1010 const volatile &&>>{}, "");

struct function_object_1011
{
    void operator()(...);
    void operator()(...) const;
    // void operator()(...) volatile;
    void operator()(...) const volatile;
};

static_assert(is_same<void(...), function_type_void_t<function_object_1011>>{}, "");
static_assert(is_same<void(...), function_type_void_t<function_object_1011 &>>{}, "");
static_assert(is_same<void(...), function_type_void_t<function_object_1011 &&>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_1011 const>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_1011 const &>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_1011 const &&>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1011 volatile>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1011 volatile &>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1011 volatile &&>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1011 const volatile>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1011 const volatile &>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1011 const volatile &&>>{}, "");

struct function_object_1100
{
    // void operator()(...);
    // void operator()(...) const;
    void operator()(...) volatile;
    void operator()(...) const volatile;
};

static_assert(is_same<void(...) volatile, function_type_void_t<function_object_1100>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_1100 &>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_1100 &&>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1100 const>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1100 const &>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1100 const &&>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_1100 volatile>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_1100 volatile &>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_1100 volatile &&>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1100 const volatile>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1100 const volatile &>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1100 const volatile &&>>{}, "");


struct function_object_1101
{
    void operator()(...);
    // void operator()(...) const;
    void operator()(...) volatile;
    void operator()(...) const volatile;
};

static_assert(is_same<void(...), function_type_void_t<function_object_1101>>{}, "");
static_assert(is_same<void(...), function_type_void_t<function_object_1101 &>>{}, "");
static_assert(is_same<void(...), function_type_void_t<function_object_1101 &&>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1101 const>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1101 const &>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1101 const &&>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_1101 volatile>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_1101 volatile &>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_1101 volatile &&>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1101 const volatile>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1101 const volatile &>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1101 const volatile &&>>{}, "");

struct function_object_1110
{
    // void operator()(...);
    void operator()(...) const;
    void operator()(...) volatile;
    void operator()(...) const volatile;
};

static_assert(is_same<void, function_type_void_t<function_object_1110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 &&>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_1110 const>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_1110 const &>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_1110 const &&>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_1110 volatile>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_1110 volatile &>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_1110 volatile &&>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1110 const volatile>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1110 const volatile &>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1110 const volatile &&>>{}, "");

struct function_object_1111
{
    void operator()(...);
    void operator()(...) const;
    void operator()(...) volatile;
    void operator()(...) const volatile;
};

static_assert(is_same<void(...), function_type_void_t<function_object_1111>>{}, "");
static_assert(is_same<void(...), function_type_void_t<function_object_1111 &>>{}, "");
static_assert(is_same<void(...), function_type_void_t<function_object_1111 &&>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_1111 const>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_1111 const &>>{}, "");
static_assert(is_same<void(...) const, function_type_void_t<function_object_1111 const &&>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_1111 volatile>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_1111 volatile &>>{}, "");
static_assert(is_same<void(...) volatile, function_type_void_t<function_object_1111 volatile &&>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1111 const volatile>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1111 const volatile &>>{}, "");
static_assert(is_same<void(...) const volatile, function_type_void_t<function_object_1111 const volatile &&>>{}, "");

} // namespace suite_function_object_value_ellipsis

//-----------------------------------------------------------------------------

namespace suite_function_object_value_noexcept
{

#if __cpp_noexcept_function_type >= 201510L

struct function_object_000
{
    // void operator()() noexcept;
    // void operator()() const noexcept;
    // void operator()() volatile noexcept;
    // void operator()() const volatile noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_000>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_000 const volatile &&>>{}, "");

struct function_object_0001
{
    void operator()() noexcept;
    // void operator()() const noexcept;
    // void operator()() volatile noexcept;
    // void operator()() const volatile noexcept;
};

static_assert(is_same<void() noexcept, function_type_void_t<function_object_0001>>{}, "");
static_assert(is_same<void() noexcept, function_type_void_t<function_object_0001 &>>{}, "");
static_assert(is_same<void() noexcept, function_type_void_t<function_object_0001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile &&>>{}, "");

struct function_object_0010
{
    // void operator()() noexcept;
    void operator()() const noexcept;
    // void operator()() volatile noexcept;
    // void operator()() const volatile noexcept;
};

static_assert(is_same<void() const noexcept, function_type_void_t<function_object_0010>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_0010 &>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_0010 &&>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_0010 const>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_0010 const &>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_0010 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile &&>>{}, "");

struct function_object_0011
{
    void operator()() noexcept;
    void operator()() const noexcept;
    // void operator()() volatile noexcept;
    // void operator()() const volatile noexcept;
};

static_assert(is_same<void() noexcept, function_type_void_t<function_object_0011>>{}, "");
static_assert(is_same<void() noexcept, function_type_void_t<function_object_0011 &>>{}, "");
static_assert(is_same<void() noexcept, function_type_void_t<function_object_0011 &&>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_0011 const>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_0011 const &>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_0011 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile &&>>{}, "");

struct function_object_0100
{
    // void operator()() noexcept;
    // void operator()() const noexcept;
    void operator()() volatile noexcept;
    // void operator()() const volatile noexcept;
};

static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_0100>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_0100 &>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_0100 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const &&>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_0100 volatile>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_0100 volatile &>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_0100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile &&>>{}, "");

struct function_object_0101
{
    void operator()() noexcept;
    // void operator()() const noexcept;
    void operator()() volatile noexcept;
    // void operator()() const volatile noexcept;
};

static_assert(is_same<void() noexcept, function_type_void_t<function_object_0101>>{}, "");
static_assert(is_same<void() noexcept, function_type_void_t<function_object_0101 &>>{}, "");
static_assert(is_same<void() noexcept, function_type_void_t<function_object_0101 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const &&>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_0101 volatile>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_0101 volatile &>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_0101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile &&>>{}, "");

struct function_object_0110
{
    // void operator()() noexcept;
    void operator()() const noexcept;
    void operator()() volatile noexcept;
    // void operator()() const volatile noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_0110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 &&>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_0110 const>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_0110 const &>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_0110 const &&>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_0110 volatile>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_0110 volatile &>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_0110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile &&>>{}, "");

struct function_object_0111
{
    void operator()() noexcept;
    void operator()() const noexcept;
    void operator()() volatile noexcept;
    // void operator()() const volatile noexcept;
};

static_assert(is_same<void() noexcept, function_type_void_t<function_object_0111>>{}, "");
static_assert(is_same<void() noexcept, function_type_void_t<function_object_0111 &>>{}, "");
static_assert(is_same<void() noexcept, function_type_void_t<function_object_0111 &&>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_0111 const>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_0111 const &>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_0111 const &&>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_0111 volatile>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_0111 volatile &>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_0111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile &&>>{}, "");

struct function_object_1000
{
    // void operator()() noexcept;
    // void operator()() const noexcept;
    // void operator()() volatile noexcept;
    void operator()() const volatile noexcept;
};

static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1000>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1000 &>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1000 &&>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1000 const>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1000 const &>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1000 const &&>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1000 volatile>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1000 volatile &>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1000 const volatile>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1000 const volatile &&>>{}, "");

struct function_object_1001
{
    void operator()() noexcept;
    // void operator()() const noexcept;
    // void operator()() volatile noexcept;
    void operator()() const volatile noexcept;
};

static_assert(is_same<void() noexcept, function_type_void_t<function_object_1001>>{}, "");
static_assert(is_same<void() noexcept, function_type_void_t<function_object_1001 &>>{}, "");
static_assert(is_same<void() noexcept, function_type_void_t<function_object_1001 &&>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1001 const>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1001 const &>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1001 const &&>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1001 volatile>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1001 volatile &>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1001 const volatile>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1001 const volatile &&>>{}, "");

struct function_object_1010
{
    // void operator()() noexcept;
    void operator()() const noexcept;
    // void operator()() volatile noexcept;
    void operator()() const volatile noexcept;
};

static_assert(is_same<void() const noexcept, function_type_void_t<function_object_1010>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_1010 &>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_1010 &&>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_1010 const>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_1010 const &>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_1010 const &&>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1010 volatile>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1010 volatile &>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1010 const volatile>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1010 const volatile &&>>{}, "");

struct function_object_1011
{
    void operator()() noexcept;
    void operator()() const noexcept;
    // void operator()() volatile noexcept;
    void operator()() const volatile noexcept;
};

static_assert(is_same<void() noexcept, function_type_void_t<function_object_1011>>{}, "");
static_assert(is_same<void() noexcept, function_type_void_t<function_object_1011 &>>{}, "");
static_assert(is_same<void() noexcept, function_type_void_t<function_object_1011 &&>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_1011 const>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_1011 const &>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_1011 const &&>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1011 volatile>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1011 volatile &>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1011 const volatile>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1011 const volatile &&>>{}, "");

struct function_object_1100
{
    // void operator()() noexcept;
    // void operator()() const noexcept;
    void operator()() volatile noexcept;
    void operator()() const volatile noexcept;
};

static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_1100>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_1100 &>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_1100 &&>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1100 const>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1100 const &>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1100 const &&>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_1100 volatile>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_1100 volatile &>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_1100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1100 const volatile>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1100 const volatile &&>>{}, "");


struct function_object_1101
{
    void operator()() noexcept;
    // void operator()() const noexcept;
    void operator()() volatile noexcept;
    void operator()() const volatile noexcept;
};

static_assert(is_same<void() noexcept, function_type_void_t<function_object_1101>>{}, "");
static_assert(is_same<void() noexcept, function_type_void_t<function_object_1101 &>>{}, "");
static_assert(is_same<void() noexcept, function_type_void_t<function_object_1101 &&>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1101 const>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1101 const &>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1101 const &&>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_1101 volatile>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_1101 volatile &>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_1101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1101 const volatile>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1101 const volatile &&>>{}, "");

struct function_object_1110
{
    // void operator()() noexcept;
    void operator()() const noexcept;
    void operator()() volatile noexcept;
    void operator()() const volatile noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_1110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 &&>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_1110 const>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_1110 const &>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_1110 const &&>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_1110 volatile>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_1110 volatile &>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_1110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1110 const volatile>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1110 const volatile &&>>{}, "");

struct function_object_1111
{
    void operator()() noexcept;
    void operator()() const noexcept;
    void operator()() volatile noexcept;
    void operator()() const volatile noexcept;
};

static_assert(is_same<void() noexcept, function_type_void_t<function_object_1111>>{}, "");
static_assert(is_same<void() noexcept, function_type_void_t<function_object_1111 &>>{}, "");
static_assert(is_same<void() noexcept, function_type_void_t<function_object_1111 &&>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_1111 const>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_1111 const &>>{}, "");
static_assert(is_same<void() const noexcept, function_type_void_t<function_object_1111 const &&>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_1111 volatile>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_1111 volatile &>>{}, "");
static_assert(is_same<void() volatile noexcept, function_type_void_t<function_object_1111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1111 const volatile>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile noexcept, function_type_void_t<function_object_1111 const volatile &&>>{}, "");

#endif

} // namespace suite_function_object_value_noexcept

//-----------------------------------------------------------------------------

namespace suite_function_object_lvalue
{

struct function_object_0000
{
    // void operator()() &;
    // void operator()() const &;
    // void operator()() volatile &;
    // void operator()() const volatile &;
};

static_assert(is_same<void, function_type_void_t<function_object_0000>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const volatile &&>>{}, "");

struct function_object_0001
{
    void operator()() &;
    // void operator()() const &;
    // void operator()() volatile &;
    // void operator()() const volatile &;
};

static_assert(is_same<void() &, function_type_void_t<function_object_0001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_0001 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile &&>>{}, "");

struct function_object_0010
{
    // void operator()() &;
    void operator()() const &;
    // void operator()() volatile &;
    // void operator()() const volatile &;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_0010>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_0010 &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_0010 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_0010 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_0010 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_0010 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile &&>>{}, "");

struct function_object_0011
{
    void operator()() &;
    void operator()() const &;
    // void operator()() volatile &;
    // void operator()() const volatile &;
};

static_assert(is_same<void() &, function_type_void_t<function_object_0011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_0011 &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_0011 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_0011 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_0011 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_0011 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile &&>>{}, "");

struct function_object_0100
{
    // void operator()() &;
    // void operator()() const &;
    void operator()() volatile &;
    // void operator()() const volatile &;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_0100>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_0100 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_0100 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_0100 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile &&>>{}, "");

struct function_object_0101
{
    void operator()() &;
    // void operator()() const &;
    void operator()() volatile &;
    // void operator()() const volatile &;
};

static_assert(is_same<void() &, function_type_void_t<function_object_0101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_0101 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_0101 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_0101 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile &&>>{}, "");

struct function_object_0110
{
    // void operator()() &;
    void operator()() const &;
    void operator()() volatile &;
    // void operator()() const volatile &;
};

static_assert(is_same<void, function_type_void_t<function_object_0110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_0110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_0110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_0110 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_0110 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_0110 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_0110 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile &&>>{}, "");

struct function_object_0111
{
    void operator()() &;
    void operator()() const &;
    void operator()() volatile &;
    // void operator()() const volatile &;
};

static_assert(is_same<void() &, function_type_void_t<function_object_0111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_0111 &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_0111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_0111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_0111 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_0111 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_0111 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_0111 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile &&>>{}, "");

struct function_object_1000
{
    // void operator()() &;
    // void operator()() const &;
    // void operator()() volatile &;
    void operator()() const volatile &;
};

static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1000>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1000 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1000 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1000 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1000 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1000 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 const volatile &&>>{}, "");

struct function_object_1001
{
    void operator()() &;
    // void operator()() const &;
    // void operator()() volatile &;
    void operator()() const volatile &;
};

static_assert(is_same<void() &, function_type_void_t<function_object_1001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_1001 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1001 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1001 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1001 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1001 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1001 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 const volatile &&>>{}, "");

struct function_object_1010
{
    // void operator()() &;
    void operator()() const &;
    // void operator()() volatile &;
    void operator()() const volatile &;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_1010>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_1010 &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_1010 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_1010 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_1010 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_1010 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1010 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1010 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1010 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1010 const volatile &&>>{}, "");

struct function_object_1011
{
    void operator()() &;
    void operator()() const &;
    // void operator()() volatile &;
    void operator()() const volatile &;
};

static_assert(is_same<void() &, function_type_void_t<function_object_1011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_1011 &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_1011 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_1011 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_1011 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_1011 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1011 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1011 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1011 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1011 const volatile &&>>{}, "");

struct function_object_1100
{
    // void operator()() &;
    // void operator()() const &;
    void operator()() volatile &;
    void operator()() const volatile &;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_1100>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_1100 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1100 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1100 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_1100 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_1100 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1100 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 const volatile &&>>{}, "");


struct function_object_1101
{
    void operator()() &;
    // void operator()() const &;
    void operator()() volatile &;
    void operator()() const volatile &;
};

static_assert(is_same<void() &, function_type_void_t<function_object_1101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_1101 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1101 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1101 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_1101 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_1101 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1101 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 const volatile &&>>{}, "");

struct function_object_1110
{
    // void operator()() &;
    void operator()() const &;
    void operator()() volatile &;
    void operator()() const volatile &;
};

static_assert(is_same<void, function_type_void_t<function_object_1110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_1110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_1110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_1110 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_1110 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_1110 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_1110 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1110 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 const volatile &&>>{}, "");

struct function_object_1111
{
    void operator()() &;
    void operator()() const &;
    void operator()() volatile &;
    void operator()() const volatile &;
};

static_assert(is_same<void() &, function_type_void_t<function_object_1111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_1111 &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_1111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_1111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_1111 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_1111 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_1111 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_1111 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1111 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_1111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1111 const volatile &&>>{}, "");

} // namespace suite_function_object_lvalue

//-----------------------------------------------------------------------------

namespace suite_function_object_lvalue_noexcept
{

#if __cpp_noexcept_function_type >= 201510L

struct function_object_0000
{
    // void operator()() & noexcept;
    // void operator()() const & noexcept;
    // void operator()() volatile & noexcept;
    // void operator()() const volatile & noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_0000>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const volatile &&>>{}, "");

struct function_object_0001
{
    void operator()() & noexcept;
    // void operator()() const & noexcept;
    // void operator()() volatile & noexcept;
    // void operator()() const volatile & noexcept;
};

static_assert(is_same<void() & noexcept, function_type_void_t<function_object_0001>>{}, "");
static_assert(is_same<void() & noexcept, function_type_void_t<function_object_0001 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile &&>>{}, "");

struct function_object_0010
{
    // void operator()() & noexcept;
    void operator()() const & noexcept;
    // void operator()() volatile & noexcept;
    // void operator()() const volatile & noexcept;
};

static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_0010>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_0010 &>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_0010 &&>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_0010 const>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_0010 const &>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_0010 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile &&>>{}, "");

struct function_object_0011
{
    void operator()() & noexcept;
    void operator()() const & noexcept;
    // void operator()() volatile & noexcept;
    // void operator()() const volatile & noexcept;
};

static_assert(is_same<void() & noexcept, function_type_void_t<function_object_0011>>{}, "");
static_assert(is_same<void() & noexcept, function_type_void_t<function_object_0011 &>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_0011 &&>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_0011 const>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_0011 const &>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_0011 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile &&>>{}, "");

struct function_object_0100
{
    // void operator()() & noexcept;
    // void operator()() const & noexcept;
    void operator()() volatile & noexcept;
    // void operator()() const volatile & noexcept;
};

static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_0100>>{}, "");
static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_0100 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const &&>>{}, "");
static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_0100 volatile>>{}, "");
static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_0100 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile &&>>{}, "");

struct function_object_0101
{
    void operator()() & noexcept;
    // void operator()() const & noexcept;
    void operator()() volatile & noexcept;
    // void operator()() const volatile & noexcept;
};

static_assert(is_same<void() & noexcept, function_type_void_t<function_object_0101>>{}, "");
static_assert(is_same<void() & noexcept, function_type_void_t<function_object_0101 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const &&>>{}, "");
static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_0101 volatile>>{}, "");
static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_0101 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile &&>>{}, "");

struct function_object_0110
{
    // void operator()() & noexcept;
    void operator()() const & noexcept;
    void operator()() volatile & noexcept;
    // void operator()() const volatile & noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_0110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 &>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_0110 &&>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_0110 const>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_0110 const &>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_0110 const &&>>{}, "");
static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_0110 volatile>>{}, "");
static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_0110 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile &&>>{}, "");

struct function_object_0111
{
    void operator()() & noexcept;
    void operator()() const & noexcept;
    void operator()() volatile & noexcept;
    // void operator()() const volatile & noexcept;
};

static_assert(is_same<void() & noexcept, function_type_void_t<function_object_0111>>{}, "");
static_assert(is_same<void() & noexcept, function_type_void_t<function_object_0111 &>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_0111 &&>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_0111 const>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_0111 const &>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_0111 const &&>>{}, "");
static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_0111 volatile>>{}, "");
static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_0111 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile &&>>{}, "");

struct function_object_1000
{
    // void operator()() & noexcept;
    // void operator()() const & noexcept;
    // void operator()() volatile & noexcept;
    void operator()() const volatile & noexcept;
};

static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1000>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 &&>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1000 const>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1000 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 const &&>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1000 volatile>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1000 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1000 const volatile>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 const volatile &&>>{}, "");

struct function_object_1001
{
    void operator()() & noexcept;
    // void operator()() const & noexcept;
    // void operator()() volatile & noexcept;
    void operator()() const volatile & noexcept;
};

static_assert(is_same<void() & noexcept, function_type_void_t<function_object_1001>>{}, "");
static_assert(is_same<void() & noexcept, function_type_void_t<function_object_1001 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 &&>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1001 const>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1001 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 const &&>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1001 volatile>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1001 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1001 const volatile>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 const volatile &&>>{}, "");

struct function_object_1010
{
    // void operator()() & noexcept;
    void operator()() const & noexcept;
    // void operator()() volatile & noexcept;
    void operator()() const volatile & noexcept;
};

static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_1010>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_1010 &>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_1010 &&>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_1010 const>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_1010 const &>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_1010 const &&>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1010 volatile>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1010 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1010 const volatile>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1010 const volatile &&>>{}, "");

struct function_object_1011
{
    void operator()() & noexcept;
    void operator()() const & noexcept;
    // void operator()() volatile & noexcept;
    void operator()() const volatile & noexcept;
};

static_assert(is_same<void() & noexcept, function_type_void_t<function_object_1011>>{}, "");
static_assert(is_same<void() & noexcept, function_type_void_t<function_object_1011 &>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_1011 &&>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_1011 const>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_1011 const &>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_1011 const &&>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1011 volatile>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1011 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1011 const volatile>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1011 const volatile &&>>{}, "");

struct function_object_1100
{
    // void operator()() & noexcept;
    // void operator()() const & noexcept;
    void operator()() volatile & noexcept;
    void operator()() const volatile & noexcept;
};

static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_1100>>{}, "");
static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_1100 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 &&>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1100 const>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1100 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 const &&>>{}, "");
static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_1100 volatile>>{}, "");
static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_1100 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1100 const volatile>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 const volatile &&>>{}, "");


struct function_object_1101
{
    void operator()() & noexcept;
    // void operator()() const & noexcept;
    void operator()() volatile & noexcept;
    void operator()() const volatile & noexcept;
};

static_assert(is_same<void() & noexcept, function_type_void_t<function_object_1101>>{}, "");
static_assert(is_same<void() & noexcept, function_type_void_t<function_object_1101 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 &&>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1101 const>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1101 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 const &&>>{}, "");
static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_1101 volatile>>{}, "");
static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_1101 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1101 const volatile>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 const volatile &&>>{}, "");

struct function_object_1110
{
    // void operator()() & noexcept;
    void operator()() const & noexcept;
    void operator()() volatile & noexcept;
    void operator()() const volatile & noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_1110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 &>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_1110 &&>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_1110 const>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_1110 const &>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_1110 const &&>>{}, "");
static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_1110 volatile>>{}, "");
static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_1110 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1110 const volatile>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 const volatile &&>>{}, "");

struct function_object_1111
{
    void operator()() & noexcept;
    void operator()() const & noexcept;
    void operator()() volatile & noexcept;
    void operator()() const volatile & noexcept;
};

static_assert(is_same<void() & noexcept, function_type_void_t<function_object_1111>>{}, "");
static_assert(is_same<void() & noexcept, function_type_void_t<function_object_1111 &>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_1111 &&>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_1111 const>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_1111 const &>>{}, "");
static_assert(is_same<void() const & noexcept, function_type_void_t<function_object_1111 const &&>>{}, "");
static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_1111 volatile>>{}, "");
static_assert(is_same<void() volatile & noexcept, function_type_void_t<function_object_1111 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1111 const volatile>>{}, "");
static_assert(is_same<void() const volatile & noexcept, function_type_void_t<function_object_1111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1111 const volatile &&>>{}, "");

#endif

} // namespace suite_function_object_lvalue_noexcept

//-----------------------------------------------------------------------------

namespace suite_function_object_rvalue
{

struct function_object_0000
{
    // void operator()() &&;
    // void operator()() const &&;
    // void operator()() volatile &&;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_0000>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const volatile &&>>{}, "");

struct function_object_0001
{
    void operator()() &&;
    // void operator()() const &&;
    // void operator()() volatile &&;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_0001>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_0001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile &&>>{}, "");

struct function_object_0010
{
    // void operator()() &&;
    void operator()() const &&;
    // void operator()() volatile &&;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_0010>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_0010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_0010 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile &&>>{}, "");

struct function_object_0011
{
    void operator()() &&;
    void operator()() const &&;
    // void operator()() volatile &&;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_0011>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_0011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_0011 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile &&>>{}, "");

struct function_object_0100
{
    // void operator()() &&;
    // void operator()() const &&;
    void operator()() volatile &&;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_0100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_0100 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_0100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile &&>>{}, "");

struct function_object_0101
{
    void operator()() &&;
    // void operator()() const &&;
    void operator()() volatile &&;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_0101>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_0101 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_0101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile &&>>{}, "");

struct function_object_0110
{
    // void operator()() &&;
    void operator()() const &&;
    void operator()() volatile &&;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_0110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_0110 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_0110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile &&>>{}, "");

struct function_object_0111
{
    void operator()() &&;
    void operator()() const &&;
    void operator()() volatile &&;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_0111>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_0111 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_0111 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_0111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile &&>>{}, "");

struct function_object_1000
{
    // void operator()() &&;
    // void operator()() const &&;
    // void operator()() volatile &&;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_1000>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_1000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_1000 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_1000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_1000 const volatile &&>>{}, "");

struct function_object_1001
{
    void operator()() &&;
    // void operator()() const &&;
    // void operator()() volatile &&;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_1001>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_1001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_1001 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_1001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_1001 const volatile &&>>{}, "");

struct function_object_1010
{
    // void operator()() &&;
    void operator()() const &&;
    // void operator()() volatile &&;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_1010>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1010 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_1010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1010 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_1010 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1010 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1010 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_1010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_1010 const volatile &&>>{}, "");

struct function_object_1011
{
    void operator()() &&;
    void operator()() const &&;
    // void operator()() volatile &&;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_1011>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_1011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1011 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_1011 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1011 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1011 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_1011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_1011 const volatile &&>>{}, "");

struct function_object_1100
{
    // void operator()() &&;
    // void operator()() const &&;
    void operator()() volatile &&;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_1100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_1100 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_1100 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_1100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_1100 const volatile &&>>{}, "");


struct function_object_1101
{
    void operator()() &&;
    // void operator()() const &&;
    void operator()() volatile &&;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_1101>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_1101 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_1101 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_1101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_1101 const volatile &&>>{}, "");

struct function_object_1110
{
    // void operator()() &&;
    void operator()() const &&;
    void operator()() volatile &&;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_1110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_1110 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_1110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_1110 const volatile &&>>{}, "");

struct function_object_1111
{
    void operator()() &&;
    void operator()() const &&;
    void operator()() volatile &&;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_1111>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_1111 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1111 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1111 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_1111 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1111 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1111 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_1111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_1111 const volatile &&>>{}, "");

} // namespace suite_function_object_rvalue

//-----------------------------------------------------------------------------

namespace suite_function_object_rvalue_noexcept
{

#if __cpp_noexcept_function_type >= 201510L

struct function_object_0000
{
    // void operator()() && noexcept;
    // void operator()() const && noexcept;
    // void operator()() volatile && noexcept;
    // void operator()() const volatile && noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_0000>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0000 const volatile &&>>{}, "");

struct function_object_0001
{
    void operator()() && noexcept;
    // void operator()() const && noexcept;
    // void operator()() volatile && noexcept;
    // void operator()() const volatile && noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_0001>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 &>>{}, "");
static_assert(is_same<void() && noexcept, function_type_void_t<function_object_0001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0001 const volatile &&>>{}, "");

struct function_object_0010
{
    // void operator()() && noexcept;
    void operator()() const && noexcept;
    // void operator()() volatile && noexcept;
    // void operator()() const volatile && noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_0010>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 &>>{}, "");
static_assert(is_same<void() const && noexcept, function_type_void_t<function_object_0010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const &>>{}, "");
static_assert(is_same<void() const && noexcept, function_type_void_t<function_object_0010 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0010 const volatile &&>>{}, "");

struct function_object_0011
{
    void operator()() && noexcept;
    void operator()() const && noexcept;
    // void operator()() volatile && noexcept;
    // void operator()() const volatile && noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_0011>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 &>>{}, "");
static_assert(is_same<void() && noexcept, function_type_void_t<function_object_0011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const &>>{}, "");
static_assert(is_same<void() const && noexcept, function_type_void_t<function_object_0011 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0011 const volatile &&>>{}, "");

struct function_object_0100
{
    // void operator()() && noexcept;
    // void operator()() const && noexcept;
    void operator()() volatile && noexcept;
    // void operator()() const volatile && noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_0100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 &>>{}, "");
static_assert(is_same<void() volatile && noexcept, function_type_void_t<function_object_0100 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 volatile &>>{}, "");
static_assert(is_same<void() volatile && noexcept, function_type_void_t<function_object_0100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0100 const volatile &&>>{}, "");

struct function_object_0101
{
    void operator()() && noexcept;
    // void operator()() const && noexcept;
    void operator()() volatile && noexcept;
    // void operator()() const volatile && noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_0101>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 &>>{}, "");
static_assert(is_same<void() && noexcept, function_type_void_t<function_object_0101 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 volatile &>>{}, "");
static_assert(is_same<void() volatile && noexcept, function_type_void_t<function_object_0101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0101 const volatile &&>>{}, "");

struct function_object_0110
{
    // void operator()() && noexcept;
    void operator()() const && noexcept;
    void operator()() volatile && noexcept;
    // void operator()() const volatile && noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_0110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const &>>{}, "");
static_assert(is_same<void() const && noexcept, function_type_void_t<function_object_0110 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 volatile &>>{}, "");
static_assert(is_same<void() volatile && noexcept, function_type_void_t<function_object_0110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0110 const volatile &&>>{}, "");

struct function_object_0111
{
    void operator()() && noexcept;
    void operator()() const && noexcept;
    void operator()() volatile && noexcept;
    // void operator()() const volatile && noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_0111>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 &>>{}, "");
static_assert(is_same<void() && noexcept, function_type_void_t<function_object_0111 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const &>>{}, "");
static_assert(is_same<void() const && noexcept, function_type_void_t<function_object_0111 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 volatile &>>{}, "");
static_assert(is_same<void() volatile && noexcept, function_type_void_t<function_object_0111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_0111 const volatile &&>>{}, "");

struct function_object_1000
{
    // void operator()() && noexcept;
    // void operator()() const && noexcept;
    // void operator()() volatile && noexcept;
    void operator()() const volatile && noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_1000>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 &>>{}, "");
static_assert(is_same<void() const volatile && noexcept, function_type_void_t<function_object_1000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 const &>>{}, "");
static_assert(is_same<void() const volatile && noexcept, function_type_void_t<function_object_1000 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 volatile &>>{}, "");
static_assert(is_same<void() const volatile && noexcept, function_type_void_t<function_object_1000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile && noexcept, function_type_void_t<function_object_1000 const volatile &&>>{}, "");

struct function_object_1001
{
    void operator()() && noexcept;
    // void operator()() const && noexcept;
    // void operator()() volatile && noexcept;
    void operator()() const volatile && noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_1001>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 &>>{}, "");
static_assert(is_same<void() && noexcept, function_type_void_t<function_object_1001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 const &>>{}, "");
static_assert(is_same<void() const volatile && noexcept, function_type_void_t<function_object_1001 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 volatile &>>{}, "");
static_assert(is_same<void() const volatile && noexcept, function_type_void_t<function_object_1001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile && noexcept, function_type_void_t<function_object_1001 const volatile &&>>{}, "");

struct function_object_1010
{
    // void operator()() && noexcept;
    void operator()() const && noexcept;
    // void operator()() volatile && noexcept;
    void operator()() const volatile && noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_1010>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1010 &>>{}, "");
static_assert(is_same<void() const && noexcept, function_type_void_t<function_object_1010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1010 const &>>{}, "");
static_assert(is_same<void() const && noexcept, function_type_void_t<function_object_1010 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1010 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1010 volatile &>>{}, "");
static_assert(is_same<void() const volatile && noexcept, function_type_void_t<function_object_1010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile && noexcept, function_type_void_t<function_object_1010 const volatile &&>>{}, "");

struct function_object_1011
{
    void operator()() && noexcept;
    void operator()() const && noexcept;
    // void operator()() volatile && noexcept;
    void operator()() const volatile && noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_1011>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1011 &>>{}, "");
static_assert(is_same<void() && noexcept, function_type_void_t<function_object_1011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1011 const &>>{}, "");
static_assert(is_same<void() const && noexcept, function_type_void_t<function_object_1011 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1011 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1011 volatile &>>{}, "");
static_assert(is_same<void() const volatile && noexcept, function_type_void_t<function_object_1011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile && noexcept, function_type_void_t<function_object_1011 const volatile &&>>{}, "");

struct function_object_1100
{
    // void operator()() && noexcept;
    // void operator()() const && noexcept;
    void operator()() volatile && noexcept;
    void operator()() const volatile && noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_1100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 &>>{}, "");
static_assert(is_same<void() volatile && noexcept, function_type_void_t<function_object_1100 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 const &>>{}, "");
static_assert(is_same<void() const volatile && noexcept, function_type_void_t<function_object_1100 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 volatile &>>{}, "");
static_assert(is_same<void() volatile && noexcept, function_type_void_t<function_object_1100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile && noexcept, function_type_void_t<function_object_1100 const volatile &&>>{}, "");


struct function_object_1101
{
    void operator()() && noexcept;
    // void operator()() const && noexcept;
    void operator()() volatile && noexcept;
    void operator()() const volatile && noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_1101>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 &>>{}, "");
static_assert(is_same<void() && noexcept, function_type_void_t<function_object_1101 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 const &>>{}, "");
static_assert(is_same<void() const volatile && noexcept, function_type_void_t<function_object_1101 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 volatile &>>{}, "");
static_assert(is_same<void() volatile && noexcept, function_type_void_t<function_object_1101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile && noexcept, function_type_void_t<function_object_1101 const volatile &&>>{}, "");

struct function_object_1110
{
    // void operator()() && noexcept;
    void operator()() const && noexcept;
    void operator()() volatile && noexcept;
    void operator()() const volatile && noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_1110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 const &>>{}, "");
static_assert(is_same<void() const && noexcept, function_type_void_t<function_object_1110 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 volatile &>>{}, "");
static_assert(is_same<void() volatile && noexcept, function_type_void_t<function_object_1110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile && noexcept, function_type_void_t<function_object_1110 const volatile &&>>{}, "");

struct function_object_1111
{
    void operator()() && noexcept;
    void operator()() const && noexcept;
    void operator()() volatile && noexcept;
    void operator()() const volatile && noexcept;
};

static_assert(is_same<void, function_type_void_t<function_object_1111>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1111 &>>{}, "");
static_assert(is_same<void() && noexcept, function_type_void_t<function_object_1111 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1111 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1111 const &>>{}, "");
static_assert(is_same<void() const && noexcept, function_type_void_t<function_object_1111 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1111 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1111 volatile &>>{}, "");
static_assert(is_same<void() volatile && noexcept, function_type_void_t<function_object_1111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_1111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile && noexcept, function_type_void_t<function_object_1111 const volatile &&>>{}, "");

#endif

} // namespace suite_function_object_rvalue_noexcept

//-----------------------------------------------------------------------------

namespace suite_function_object_overload_mixed
{

struct function_object_00000000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_00000000>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000000 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000000 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000000 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000000 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000000 const volatile &&>>{}, "");

struct function_object_00000001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00000001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00000001 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000001 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000001 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000001 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000001 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000001 const volatile &&>>{}, "");

struct function_object_00000010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_00000010>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00000010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000010 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000010 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000010 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000010 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000010 const volatile &&>>{}, "");

struct function_object_00000011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00000011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00000011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00000011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000011 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000011 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000011 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000011 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000011 const volatile &&>>{}, "");

struct function_object_00000100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_00000100>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00000100 &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00000100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00000100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00000100 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00000100 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000100 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000100 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000100 const volatile &&>>{}, "");

struct function_object_00000101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00000101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00000101 &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00000101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00000101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00000101 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00000101 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000101 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000101 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000101 const volatile &&>>{}, "");

struct function_object_00000110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_00000110>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00000110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00000110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00000110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00000110 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00000110 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000110 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000110 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000110 const volatile &&>>{}, "");

struct function_object_00000111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00000111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00000111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00000111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00000111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00000111 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00000111 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000111 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000111 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00000111 const volatile &&>>{}, "");

struct function_object_00001000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_00001000>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001000 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00001000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001000 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00001000 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001000 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001000 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001000 const volatile &&>>{}, "");

struct function_object_00001001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00001001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00001001 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00001001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001001 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00001001 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001001 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001001 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001001 const volatile &&>>{}, "");

struct function_object_00001010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_00001010>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00001010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001010 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00001010 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001010 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001010 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001010 const volatile &&>>{}, "");

struct function_object_00001011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00001011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00001011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00001011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001011 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00001011 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001011 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001011 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001011 const volatile &&>>{}, "");

struct function_object_00001100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_00001100>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00001100 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00001100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00001100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00001100 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00001100 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001100 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001100 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001100 const volatile &&>>{}, "");

struct function_object_00001101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00001101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00001101 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00001101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00001101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00001101 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00001101 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001101 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001101 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001101 const volatile &&>>{}, "");

struct function_object_00001110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_00001110>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00001110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00001110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00001110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00001110 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00001110 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001110 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001110 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001110 const volatile &&>>{}, "");

struct function_object_00001111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00001111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00001111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00001111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00001111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00001111 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00001111 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001111 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001111 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00001111 const volatile &&>>{}, "");

struct function_object_00010000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010000>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010000 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010000 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010000 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010000 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010000 const volatile &&>>{}, "");

struct function_object_00010001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00010001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00010001 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010001 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010001 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010001 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010001 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010001 const volatile &&>>{}, "");

struct function_object_00010010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010010>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00010010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010010 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010010 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010010 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010010 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010010 const volatile &&>>{}, "");

struct function_object_00010011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00010011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00010011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00010011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010011 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010011 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010011 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010011 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010011 const volatile &&>>{}, "");

struct function_object_00010100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_00010100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010100 &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00010100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00010100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00010100 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00010100 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010100 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010100 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010100 const volatile &&>>{}, "");

struct function_object_00010101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00010101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00010101 &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00010101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00010101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00010101 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00010101 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010101 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010101 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010101 const volatile &&>>{}, "");

struct function_object_00010110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_00010110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00010110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00010110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00010110 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00010110 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010110 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010110 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010110 const volatile &&>>{}, "");

struct function_object_00010111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00010111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00010111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00010111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00010111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00010111 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00010111 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010111 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00010111 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00010111 const volatile &&>>{}, "");

struct function_object_00011000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011000>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011000 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00011000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011000 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00011000 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011000 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011000 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011000 const volatile &&>>{}, "");

struct function_object_00011001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00011001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00011001 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00011001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011001 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00011001 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011001 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011001 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011001 const volatile &&>>{}, "");

struct function_object_00011010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011010>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00011010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011010 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00011010 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011010 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011010 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011010 const volatile &&>>{}, "");

struct function_object_00011011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00011011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00011011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00011011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011011 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00011011 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011011 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011011 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011011 const volatile &&>>{}, "");

struct function_object_00011100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_00011100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011100 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00011100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00011100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00011100 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00011100 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011100 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011100 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011100 const volatile &&>>{}, "");

struct function_object_00011101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00011101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00011101 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00011101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00011101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00011101 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00011101 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011101 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011101 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011101 const volatile &&>>{}, "");

struct function_object_00011110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_00011110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00011110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00011110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00011110 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00011110 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011110 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011110 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011110 const volatile &&>>{}, "");

struct function_object_00011111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00011111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00011111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00011111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00011111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00011111 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00011111 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011111 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00011111 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00011111 const volatile &&>>{}, "");

struct function_object_00100000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_00100000>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100000 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00100000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100000 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100000 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100000 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100000 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00100000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100000 const volatile &&>>{}, "");

struct function_object_00100001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00100001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00100001 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00100001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100001 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100001 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100001 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100001 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00100001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100001 const volatile &&>>{}, "");

struct function_object_00100010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_00100010>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00100010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100010 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100010 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100010 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100010 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00100010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100010 const volatile &&>>{}, "");

struct function_object_00100011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00100011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00100011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00100011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100011 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100011 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100011 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100011 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00100011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100011 const volatile &&>>{}, "");

struct function_object_00100100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_00100100>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00100100 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00100100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00100100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00100100 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00100100 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100100 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100100 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00100100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100100 const volatile &&>>{}, "");

struct function_object_00100101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00100101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00100101 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00100101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00100101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00100101 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00100101 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100101 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100101 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00100101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100101 const volatile &&>>{}, "");

struct function_object_00100110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_00100110>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00100110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00100110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00100110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00100110 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00100110 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100110 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100110 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00100110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100110 const volatile &&>>{}, "");

struct function_object_00100111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00100111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00100111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00100111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00100111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00100111 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00100111 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100111 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100111 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00100111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00100111 const volatile &&>>{}, "");

struct function_object_00101000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_00101000>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101000 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00101000 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101000 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101000 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00101000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101000 const volatile &&>>{}, "");

struct function_object_00101001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00101001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00101001 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101001 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00101001 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101001 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101001 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00101001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101001 const volatile &&>>{}, "");

struct function_object_00101010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_00101010>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00101010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101010 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00101010 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101010 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101010 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00101010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101010 const volatile &&>>{}, "");

struct function_object_00101011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00101011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00101011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00101011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101011 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00101011 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101011 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101011 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00101011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101011 const volatile &&>>{}, "");

struct function_object_00101100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_00101100>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00101100 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00101100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00101100 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00101100 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101100 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101100 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00101100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101100 const volatile &&>>{}, "");

struct function_object_00101101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00101101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00101101 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00101101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00101101 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00101101 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101101 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101101 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00101101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101101 const volatile &&>>{}, "");

struct function_object_00101110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_00101110>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00101110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00101110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00101110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00101110 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00101110 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101110 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101110 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00101110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101110 const volatile &&>>{}, "");

struct function_object_00101111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00101111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00101111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00101111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00101111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00101111 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00101111 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101111 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101111 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00101111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00101111 const volatile &&>>{}, "");

struct function_object_00110000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110000>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110000 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00110000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110000 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110000 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110000 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110000 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00110000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110000 const volatile &&>>{}, "");

struct function_object_00110001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00110001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00110001 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00110001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110001 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110001 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110001 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110001 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00110001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110001 const volatile &&>>{}, "");

struct function_object_00110010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110010>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00110010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110010 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110010 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110010 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110010 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00110010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110010 const volatile &&>>{}, "");

struct function_object_00110011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00110011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00110011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00110011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110011 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110011 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110011 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110011 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00110011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110011 const volatile &&>>{}, "");

struct function_object_00110100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_00110100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110100 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00110100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00110100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00110100 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00110100 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110100 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110100 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00110100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110100 const volatile &&>>{}, "");

struct function_object_00110101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00110101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00110101 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00110101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00110101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00110101 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00110101 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110101 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110101 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00110101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110101 const volatile &&>>{}, "");

struct function_object_00110110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_00110110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00110110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00110110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00110110 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00110110 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110110 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110110 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00110110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110110 const volatile &&>>{}, "");

struct function_object_00110111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00110111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00110111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00110111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00110111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00110111 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00110111 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110111 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00110111 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00110111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00110111 const volatile &&>>{}, "");

struct function_object_00111000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111000>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111000 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00111000 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111000 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111000 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00111000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111000 const volatile &&>>{}, "");

struct function_object_00111001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00111001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00111001 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111001 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00111001 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111001 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111001 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00111001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111001 const volatile &&>>{}, "");

struct function_object_00111010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111010>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00111010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111010 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00111010 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111010 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111010 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00111010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111010 const volatile &&>>{}, "");

struct function_object_00111011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00111011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00111011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00111011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111011 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00111011 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111011 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111011 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00111011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111011 const volatile &&>>{}, "");

struct function_object_00111100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_00111100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111100 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00111100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00111100 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00111100 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111100 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111100 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00111100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111100 const volatile &&>>{}, "");

struct function_object_00111101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00111101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00111101 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00111101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00111101 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00111101 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111101 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111101 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00111101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111101 const volatile &&>>{}, "");

struct function_object_00111110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_00111110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00111110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00111110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00111110 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00111110 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111110 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111110 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00111110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111110 const volatile &&>>{}, "");

struct function_object_00111111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_00111111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_00111111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_00111111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00111111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_00111111 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_00111111 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111111 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_00111111 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_00111111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_00111111 const volatile &&>>{}, "");

struct function_object_01000000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000000>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000000 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000000 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000000 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000000 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000000 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000000 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000000 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000000 const volatile &&>>{}, "");

struct function_object_01000001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01000001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01000001 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000001 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000001 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000001 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000001 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000001 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000001 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000001 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000001 const volatile &&>>{}, "");

struct function_object_01000010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000010>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01000010 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000010 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000010 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000010 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000010 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000010 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000010 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000010 const volatile &&>>{}, "");

struct function_object_01000011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01000011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01000011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01000011 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000011 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000011 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000011 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000011 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000011 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000011 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000011 const volatile &&>>{}, "");

struct function_object_01000100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_01000100>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01000100 &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01000100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01000100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01000100 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01000100 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000100 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000100 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000100 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000100 const volatile &&>>{}, "");

struct function_object_01000101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01000101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01000101 &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01000101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01000101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01000101 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01000101 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000101 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000101 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000101 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000101 const volatile &&>>{}, "");

struct function_object_01000110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_01000110>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01000110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01000110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01000110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01000110 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01000110 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000110 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000110 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000110 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000110 const volatile &&>>{}, "");

struct function_object_01000111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01000111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01000111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01000111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01000111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01000111 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01000111 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000111 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000111 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000111 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01000111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01000111 const volatile &&>>{}, "");

struct function_object_01001000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001000>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001000 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01001000 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001000 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001000 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01001000 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001000 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001000 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01001000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001000 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01001000 const volatile &&>>{}, "");

struct function_object_01001001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01001001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01001001 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01001001 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001001 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001001 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01001001 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001001 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001001 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01001001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001001 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01001001 const volatile &&>>{}, "");

struct function_object_01001010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001010>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01001010 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001010 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001010 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01001010 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001010 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001010 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01001010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001010 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01001010 const volatile &&>>{}, "");

struct function_object_01001011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01001011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01001011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01001011 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001011 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001011 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01001011 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001011 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001011 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01001011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001011 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01001011 const volatile &&>>{}, "");

struct function_object_01001100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_01001100>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01001100 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01001100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01001100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01001100 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01001100 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001100 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001100 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01001100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001100 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01001100 const volatile &&>>{}, "");

struct function_object_01001101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01001101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01001101 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01001101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01001101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01001101 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01001101 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001101 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001101 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01001101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001101 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01001101 const volatile &&>>{}, "");

struct function_object_01001110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_01001110>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01001110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01001110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01001110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01001110 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01001110 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001110 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001110 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01001110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001110 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01001110 const volatile &&>>{}, "");

struct function_object_01001111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01001111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01001111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01001111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01001111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01001111 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01001111 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001111 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001111 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01001111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001111 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01001111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01001111 const volatile &&>>{}, "");

struct function_object_01010000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010000>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010000 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010000 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010000 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010000 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010000 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010000 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010000 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010000 const volatile &&>>{}, "");

struct function_object_01010001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01010001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01010001 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010001 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010001 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010001 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010001 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010001 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010001 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010001 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010001 const volatile &&>>{}, "");

struct function_object_01010010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010010>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01010010 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010010 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010010 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010010 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010010 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010010 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010010 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010010 const volatile &&>>{}, "");

struct function_object_01010011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01010011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01010011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01010011 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010011 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010011 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010011 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010011 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010011 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010011 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010011 const volatile &&>>{}, "");

struct function_object_01010100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_01010100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010100 &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01010100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01010100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01010100 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01010100 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010100 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010100 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010100 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010100 const volatile &&>>{}, "");

struct function_object_01010101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01010101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01010101 &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01010101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01010101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01010101 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01010101 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010101 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010101 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010101 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010101 const volatile &&>>{}, "");

struct function_object_01010110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_01010110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01010110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01010110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01010110 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01010110 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010110 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010110 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010110 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010110 const volatile &&>>{}, "");

struct function_object_01010111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01010111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01010111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01010111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01010111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01010111 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01010111 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010111 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01010111 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010111 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01010111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01010111 const volatile &&>>{}, "");

struct function_object_01011000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011000>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011000 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01011000 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011000 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011000 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01011000 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011000 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011000 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01011000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011000 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01011000 const volatile &&>>{}, "");

struct function_object_01011001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01011001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01011001 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01011001 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011001 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011001 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01011001 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011001 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011001 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01011001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011001 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01011001 const volatile &&>>{}, "");

struct function_object_01011010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011010>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01011010 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011010 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011010 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01011010 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011010 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011010 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01011010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011010 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01011010 const volatile &&>>{}, "");

struct function_object_01011011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01011011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01011011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01011011 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011011 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011011 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01011011 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011011 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011011 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01011011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011011 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01011011 const volatile &&>>{}, "");

struct function_object_01011100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_01011100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01011100 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01011100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01011100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01011100 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01011100 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011100 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011100 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01011100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011100 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01011100 const volatile &&>>{}, "");

struct function_object_01011101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01011101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01011101 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01011101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01011101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01011101 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01011101 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011101 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011101 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01011101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011101 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01011101 const volatile &&>>{}, "");

struct function_object_01011110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_01011110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01011110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01011110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01011110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01011110 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01011110 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011110 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011110 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01011110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011110 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01011110 const volatile &&>>{}, "");

struct function_object_01011111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01011111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01011111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01011111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01011111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01011111 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01011111 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011111 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01011111 volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01011111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011111 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01011111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01011111 const volatile &&>>{}, "");

struct function_object_01100000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100000>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100000 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01100000 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100000 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100000 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01100000 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100000 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100000 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01100000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100000 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01100000 const volatile &&>>{}, "");

struct function_object_01100001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01100001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01100001 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01100001 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100001 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100001 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01100001 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100001 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100001 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01100001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100001 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01100001 const volatile &&>>{}, "");

struct function_object_01100010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100010>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01100010 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100010 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100010 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01100010 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100010 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100010 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01100010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100010 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01100010 const volatile &&>>{}, "");

struct function_object_01100011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01100011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01100011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01100011 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100011 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100011 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01100011 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100011 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100011 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01100011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100011 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01100011 const volatile &&>>{}, "");

struct function_object_01100100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_01100100>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01100100 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01100100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01100100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01100100 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01100100 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100100 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100100 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01100100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100100 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01100100 const volatile &&>>{}, "");

struct function_object_01100101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01100101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01100101 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01100101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01100101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01100101 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01100101 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100101 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100101 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01100101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100101 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01100101 const volatile &&>>{}, "");

struct function_object_01100110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_01100110>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01100110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01100110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01100110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01100110 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01100110 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100110 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100110 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01100110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100110 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01100110 const volatile &&>>{}, "");

struct function_object_01100111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01100111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01100111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01100111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01100111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01100111 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01100111 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100111 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100111 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01100111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100111 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01100111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01100111 const volatile &&>>{}, "");

struct function_object_01101000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101000>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01101000 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101000 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101000 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01101000 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101000 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101000 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01101000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101000 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01101000 const volatile &&>>{}, "");

struct function_object_01101001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01101001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01101001 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01101001 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101001 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101001 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01101001 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101001 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101001 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01101001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101001 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01101001 const volatile &&>>{}, "");

struct function_object_01101010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101010>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01101010 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101010 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101010 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01101010 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101010 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101010 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01101010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101010 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01101010 const volatile &&>>{}, "");

struct function_object_01101011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01101011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01101011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01101011 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101011 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101011 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01101011 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101011 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101011 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01101011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101011 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01101011 const volatile &&>>{}, "");

struct function_object_01101100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_01101100>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01101100 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01101100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01101100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01101100 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01101100 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101100 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101100 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01101100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101100 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01101100 const volatile &&>>{}, "");

struct function_object_01101101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01101101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01101101 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01101101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01101101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01101101 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01101101 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101101 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101101 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01101101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101101 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01101101 const volatile &&>>{}, "");

struct function_object_01101110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_01101110>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01101110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01101110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01101110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01101110 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01101110 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101110 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101110 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01101110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101110 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01101110 const volatile &&>>{}, "");

struct function_object_01101111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01101111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01101111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01101111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01101111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01101111 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01101111 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101111 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101111 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01101111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101111 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01101111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01101111 const volatile &&>>{}, "");

struct function_object_01110000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110000>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110000 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01110000 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110000 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110000 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01110000 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110000 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110000 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01110000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110000 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01110000 const volatile &&>>{}, "");

struct function_object_01110001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01110001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01110001 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01110001 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110001 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110001 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01110001 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110001 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110001 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01110001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110001 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01110001 const volatile &&>>{}, "");

struct function_object_01110010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110010>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01110010 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110010 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110010 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01110010 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110010 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110010 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01110010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110010 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01110010 const volatile &&>>{}, "");

struct function_object_01110011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01110011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01110011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01110011 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110011 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110011 const &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01110011 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110011 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110011 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01110011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110011 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01110011 const volatile &&>>{}, "");

struct function_object_01110100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_01110100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01110100 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01110100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01110100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01110100 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01110100 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110100 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110100 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01110100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110100 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01110100 const volatile &&>>{}, "");

struct function_object_01110101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01110101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01110101 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01110101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01110101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01110101 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01110101 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110101 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110101 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01110101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110101 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01110101 const volatile &&>>{}, "");

struct function_object_01110110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_01110110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01110110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01110110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01110110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01110110 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01110110 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110110 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110110 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01110110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110110 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01110110 const volatile &&>>{}, "");

struct function_object_01110111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01110111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01110111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01110111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01110111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01110111 const &>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01110111 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110111 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01110111 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01110111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110111 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01110111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01110111 const volatile &&>>{}, "");

struct function_object_01111000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111000>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01111000 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111000 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111000 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01111000 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111000 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111000 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01111000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111000 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111000 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01111000 const volatile &&>>{}, "");

struct function_object_01111001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01111001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01111001 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01111001 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111001 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111001 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01111001 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111001 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111001 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01111001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111001 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111001 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01111001 const volatile &&>>{}, "");

struct function_object_01111010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111010>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01111010 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111010 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111010 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01111010 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111010 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111010 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01111010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111010 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111010 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01111010 const volatile &&>>{}, "");

struct function_object_01111011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01111011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01111011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01111011 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111011 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111011 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01111011 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111011 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111011 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01111011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111011 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111011 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01111011 const volatile &&>>{}, "");

struct function_object_01111100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_01111100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01111100 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01111100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01111100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01111100 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01111100 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111100 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111100 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01111100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111100 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111100 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01111100 const volatile &&>>{}, "");

struct function_object_01111101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01111101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01111101 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01111101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01111101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01111101 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01111101 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111101 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111101 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01111101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111101 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111101 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01111101 const volatile &&>>{}, "");

struct function_object_01111110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_01111110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01111110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01111110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01111110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01111110 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01111110 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111110 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111110 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01111110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111110 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111110 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01111110 const volatile &&>>{}, "");

struct function_object_01111111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    // void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_01111111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_01111111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_01111111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01111111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_01111111 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_01111111 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111111 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_01111111 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_01111111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111111 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_01111111 const volatile &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_01111111 const volatile &&>>{}, "");

struct function_object_10000000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_10000000>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000000 &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000000 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000000 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000000 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000000 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000000 const volatile &&>>{}, "");

struct function_object_10000001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10000001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10000001 &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000001 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000001 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000001 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000001 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000001 const volatile &&>>{}, "");

struct function_object_10000010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_10000010>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10000010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000010 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000010 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000010 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000010 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000010 const volatile &&>>{}, "");

struct function_object_10000011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10000011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10000011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10000011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000011 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000011 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000011 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000011 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000011 const volatile &&>>{}, "");

struct function_object_10000100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_10000100>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10000100 &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10000100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10000100 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000100 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000100 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000100 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000100 const volatile &&>>{}, "");

struct function_object_10000101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10000101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10000101 &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10000101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10000101 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000101 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000101 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000101 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000101 const volatile &&>>{}, "");

struct function_object_10000110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_10000110>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10000110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10000110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10000110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10000110 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000110 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000110 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000110 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000110 const volatile &&>>{}, "");

struct function_object_10000111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10000111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10000111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10000111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10000111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10000111 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000111 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000111 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000111 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10000111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10000111 const volatile &&>>{}, "");

struct function_object_10001000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_10001000>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001000 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10001000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001000 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10001000 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001000 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001000 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10001000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10001000 const volatile &&>>{}, "");

struct function_object_10001001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10001001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10001001 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10001001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001001 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10001001 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001001 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001001 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10001001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10001001 const volatile &&>>{}, "");

struct function_object_10001010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_10001010>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10001010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001010 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10001010 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001010 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001010 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10001010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10001010 const volatile &&>>{}, "");

struct function_object_10001011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10001011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10001011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10001011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001011 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10001011 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001011 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001011 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10001011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10001011 const volatile &&>>{}, "");

struct function_object_10001100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_10001100>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10001100 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10001100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10001100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10001100 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10001100 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001100 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001100 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10001100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10001100 const volatile &&>>{}, "");

struct function_object_10001101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10001101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10001101 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10001101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10001101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10001101 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10001101 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001101 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001101 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10001101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10001101 const volatile &&>>{}, "");

struct function_object_10001110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_10001110>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10001110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10001110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10001110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10001110 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10001110 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001110 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001110 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10001110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10001110 const volatile &&>>{}, "");

struct function_object_10001111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10001111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10001111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10001111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10001111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10001111 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10001111 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001111 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001111 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10001111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10001111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10001111 const volatile &&>>{}, "");

struct function_object_10010000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010000>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010000 &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010000 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010000 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010000 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010000 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010000 const volatile &&>>{}, "");

struct function_object_10010001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10010001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10010001 &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010001 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010001 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010001 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010001 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010001 const volatile &&>>{}, "");

struct function_object_10010010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010010>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10010010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010010 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010010 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010010 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010010 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010010 const volatile &&>>{}, "");

struct function_object_10010011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10010011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10010011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10010011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010011 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010011 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010011 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010011 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010011 const volatile &&>>{}, "");

struct function_object_10010100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_10010100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010100 &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10010100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10010100 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010100 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010100 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010100 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010100 const volatile &&>>{}, "");

struct function_object_10010101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10010101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10010101 &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10010101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10010101 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010101 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010101 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010101 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010101 const volatile &&>>{}, "");

struct function_object_10010110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_10010110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10010110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10010110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10010110 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010110 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010110 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010110 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010110 const volatile &&>>{}, "");

struct function_object_10010111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10010111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10010111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10010111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10010111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10010111 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010111 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010111 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10010111 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10010111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10010111 const volatile &&>>{}, "");

struct function_object_10011000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011000>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011000 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10011000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011000 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10011000 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011000 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011000 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10011000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10011000 const volatile &&>>{}, "");

struct function_object_10011001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10011001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10011001 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10011001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011001 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10011001 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011001 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011001 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10011001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10011001 const volatile &&>>{}, "");

struct function_object_10011010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011010>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10011010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011010 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10011010 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011010 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011010 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10011010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10011010 const volatile &&>>{}, "");

struct function_object_10011011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10011011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10011011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10011011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011011 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10011011 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011011 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011011 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10011011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10011011 const volatile &&>>{}, "");

struct function_object_10011100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_10011100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011100 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10011100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10011100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10011100 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10011100 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011100 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011100 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10011100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10011100 const volatile &&>>{}, "");

struct function_object_10011101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10011101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10011101 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10011101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10011101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10011101 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10011101 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011101 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011101 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10011101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10011101 const volatile &&>>{}, "");

struct function_object_10011110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_10011110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10011110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10011110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10011110 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10011110 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011110 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011110 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10011110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10011110 const volatile &&>>{}, "");

struct function_object_10011111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10011111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10011111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10011111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10011111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10011111 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10011111 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011111 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10011111 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10011111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10011111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10011111 const volatile &&>>{}, "");

struct function_object_10100000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_10100000>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100000 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10100000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100000 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10100000 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100000 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100000 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10100000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10100000 const volatile &&>>{}, "");

struct function_object_10100001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10100001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10100001 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10100001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100001 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10100001 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100001 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100001 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10100001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10100001 const volatile &&>>{}, "");

struct function_object_10100010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_10100010>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10100010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100010 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10100010 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100010 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100010 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10100010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10100010 const volatile &&>>{}, "");

struct function_object_10100011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10100011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10100011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10100011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100011 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10100011 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100011 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100011 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10100011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10100011 const volatile &&>>{}, "");

struct function_object_10100100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_10100100>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10100100 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10100100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10100100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10100100 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10100100 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100100 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100100 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10100100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10100100 const volatile &&>>{}, "");

struct function_object_10100101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10100101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10100101 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10100101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10100101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10100101 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10100101 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100101 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100101 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10100101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10100101 const volatile &&>>{}, "");

struct function_object_10100110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_10100110>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10100110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10100110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10100110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10100110 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10100110 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100110 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100110 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10100110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10100110 const volatile &&>>{}, "");

struct function_object_10100111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10100111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10100111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10100111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10100111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10100111 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10100111 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100111 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100111 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10100111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10100111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10100111 const volatile &&>>{}, "");

struct function_object_10101000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_10101000>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101000 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10101000 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101000 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101000 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10101000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10101000 const volatile &&>>{}, "");

struct function_object_10101001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10101001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10101001 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101001 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10101001 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101001 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101001 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10101001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10101001 const volatile &&>>{}, "");

struct function_object_10101010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_10101010>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10101010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101010 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10101010 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101010 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101010 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10101010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10101010 const volatile &&>>{}, "");

struct function_object_10101011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10101011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10101011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10101011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101011 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10101011 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101011 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101011 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10101011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10101011 const volatile &&>>{}, "");

struct function_object_10101100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_10101100>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10101100 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10101100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10101100 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10101100 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101100 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101100 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10101100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10101100 const volatile &&>>{}, "");

struct function_object_10101101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10101101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10101101 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10101101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10101101 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10101101 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101101 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101101 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10101101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10101101 const volatile &&>>{}, "");

struct function_object_10101110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_10101110>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10101110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10101110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10101110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10101110 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10101110 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101110 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101110 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10101110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10101110 const volatile &&>>{}, "");

struct function_object_10101111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10101111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10101111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10101111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10101111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10101111 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10101111 const &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101111 volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101111 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10101111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10101111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10101111 const volatile &&>>{}, "");

struct function_object_10110000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110000>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110000 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10110000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110000 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10110000 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110000 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110000 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10110000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10110000 const volatile &&>>{}, "");

struct function_object_10110001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10110001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10110001 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10110001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110001 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10110001 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110001 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110001 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10110001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10110001 const volatile &&>>{}, "");

struct function_object_10110010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110010>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10110010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110010 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10110010 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110010 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110010 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10110010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10110010 const volatile &&>>{}, "");

struct function_object_10110011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10110011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10110011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10110011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110011 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10110011 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110011 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110011 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10110011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10110011 const volatile &&>>{}, "");

struct function_object_10110100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_10110100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110100 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10110100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10110100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10110100 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10110100 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110100 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110100 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10110100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10110100 const volatile &&>>{}, "");

struct function_object_10110101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10110101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10110101 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10110101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10110101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10110101 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10110101 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110101 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110101 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10110101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10110101 const volatile &&>>{}, "");

struct function_object_10110110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_10110110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10110110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10110110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10110110 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10110110 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110110 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110110 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10110110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10110110 const volatile &&>>{}, "");

struct function_object_10110111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10110111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10110111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10110111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10110111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10110111 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10110111 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110111 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10110111 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10110111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10110111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10110111 const volatile &&>>{}, "");

struct function_object_10111000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111000>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111000 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111000 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111000 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10111000 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111000 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111000 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10111000 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111000 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10111000 const volatile &&>>{}, "");

struct function_object_10111001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10111001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10111001 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111001 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111001 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111001 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10111001 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111001 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111001 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10111001 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111001 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10111001 const volatile &&>>{}, "");

struct function_object_10111010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111010>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10111010 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111010 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111010 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10111010 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111010 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111010 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10111010 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111010 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10111010 const volatile &&>>{}, "");

struct function_object_10111011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10111011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10111011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10111011 &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111011 const>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111011 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10111011 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111011 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111011 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10111011 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111011 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10111011 const volatile &&>>{}, "");

struct function_object_10111100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_10111100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111100 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10111100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10111100 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10111100 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111100 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111100 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10111100 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111100 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10111100 const volatile &&>>{}, "");

struct function_object_10111101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10111101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10111101 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10111101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10111101 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10111101 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111101 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111101 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10111101 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111101 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10111101 const volatile &&>>{}, "");

struct function_object_10111110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_10111110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10111110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10111110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10111110 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10111110 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111110 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111110 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10111110 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111110 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10111110 const volatile &&>>{}, "");

struct function_object_10111111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    // void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_10111111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_10111111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_10111111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10111111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_10111111 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_10111111 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111111 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_10111111 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_10111111 volatile &&>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111111 const volatile>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_10111111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_10111111 const volatile &&>>{}, "");

struct function_object_11000000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000000>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000000 &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000000 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000000 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000000 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000000 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000000 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000000 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000000 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000000 const volatile &&>>{}, "");

struct function_object_11000001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11000001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11000001 &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000001 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000001 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000001 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000001 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000001 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000001 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000001 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000001 const volatile &&>>{}, "");

struct function_object_11000010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000010>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11000010 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000010 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000010 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000010 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000010 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000010 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000010 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000010 const volatile &&>>{}, "");

struct function_object_11000011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11000011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11000011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11000011 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000011 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000011 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000011 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000011 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000011 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000011 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000011 const volatile &&>>{}, "");

struct function_object_11000100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_11000100>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11000100 &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11000100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11000100 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000100 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000100 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000100 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000100 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000100 const volatile &&>>{}, "");

struct function_object_11000101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11000101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11000101 &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11000101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11000101 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000101 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000101 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000101 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000101 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000101 const volatile &&>>{}, "");

struct function_object_11000110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_11000110>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11000110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11000110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11000110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11000110 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000110 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000110 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000110 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000110 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000110 const volatile &&>>{}, "");

struct function_object_11000111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11000111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11000111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11000111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11000111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11000111 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000111 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000111 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000111 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000111 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11000111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11000111 const volatile &&>>{}, "");

struct function_object_11001000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001000>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001000 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11001000 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001000 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001000 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11001000 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001000 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001000 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11001000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001000 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11001000 const volatile &&>>{}, "");

struct function_object_11001001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11001001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11001001 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11001001 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001001 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001001 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11001001 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001001 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001001 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11001001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001001 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11001001 const volatile &&>>{}, "");

struct function_object_11001010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001010>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11001010 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001010 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001010 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11001010 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001010 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001010 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11001010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001010 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11001010 const volatile &&>>{}, "");

struct function_object_11001011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11001011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11001011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11001011 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001011 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001011 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11001011 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001011 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001011 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11001011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001011 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11001011 const volatile &&>>{}, "");

struct function_object_11001100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_11001100>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11001100 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11001100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11001100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11001100 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11001100 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001100 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001100 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11001100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001100 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11001100 const volatile &&>>{}, "");

struct function_object_11001101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11001101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11001101 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11001101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11001101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11001101 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11001101 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001101 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001101 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11001101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001101 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11001101 const volatile &&>>{}, "");

struct function_object_11001110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_11001110>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11001110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11001110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11001110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11001110 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11001110 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001110 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001110 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11001110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001110 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11001110 const volatile &&>>{}, "");

struct function_object_11001111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11001111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11001111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11001111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11001111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11001111 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11001111 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001111 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001111 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11001111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001111 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11001111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11001111 const volatile &&>>{}, "");

struct function_object_11010000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010000>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010000 &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010000 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010000 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010000 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010000 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010000 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010000 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010000 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010000 const volatile &&>>{}, "");

struct function_object_11010001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11010001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11010001 &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010001 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010001 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010001 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010001 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010001 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010001 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010001 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010001 const volatile &&>>{}, "");

struct function_object_11010010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010010>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11010010 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010010 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010010 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010010 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010010 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010010 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010010 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010010 const volatile &&>>{}, "");

struct function_object_11010011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11010011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11010011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11010011 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010011 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010011 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010011 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010011 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010011 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010011 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010011 const volatile &&>>{}, "");

struct function_object_11010100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_11010100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_11010100 &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11010100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11010100 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010100 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010100 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010100 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010100 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010100 const volatile &&>>{}, "");

struct function_object_11010101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11010101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11010101 &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11010101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11010101 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010101 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010101 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010101 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010101 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010101 const volatile &&>>{}, "");

struct function_object_11010110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_11010110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_11010110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11010110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11010110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11010110 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010110 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010110 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010110 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010110 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010110 const volatile &&>>{}, "");

struct function_object_11010111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11010111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11010111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11010111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11010111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11010111 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010111 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010111 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11010111 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010111 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11010111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11010111 const volatile &&>>{}, "");

struct function_object_11011000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011000>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011000 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11011000 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011000 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011000 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11011000 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011000 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011000 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11011000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011000 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11011000 const volatile &&>>{}, "");

struct function_object_11011001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11011001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11011001 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11011001 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011001 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011001 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11011001 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011001 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011001 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11011001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011001 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11011001 const volatile &&>>{}, "");

struct function_object_11011010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011010>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11011010 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011010 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011010 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11011010 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011010 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011010 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11011010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011010 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11011010 const volatile &&>>{}, "");

struct function_object_11011011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11011011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11011011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11011011 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011011 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011011 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11011011 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011011 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011011 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11011011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011011 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11011011 const volatile &&>>{}, "");

struct function_object_11011100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_11011100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_11011100 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11011100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11011100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11011100 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11011100 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011100 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011100 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11011100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011100 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11011100 const volatile &&>>{}, "");

struct function_object_11011101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11011101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11011101 &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11011101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11011101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11011101 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11011101 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011101 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011101 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11011101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011101 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11011101 const volatile &&>>{}, "");

struct function_object_11011110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_11011110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_11011110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11011110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11011110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11011110 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11011110 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011110 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011110 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11011110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011110 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11011110 const volatile &&>>{}, "");

struct function_object_11011111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    // void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11011111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11011111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11011111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11011111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11011111 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11011111 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011111 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11011111 volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11011111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011111 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11011111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11011111 const volatile &&>>{}, "");

struct function_object_11100000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100000>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100000 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11100000 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100000 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100000 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11100000 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100000 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100000 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11100000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100000 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11100000 const volatile &&>>{}, "");

struct function_object_11100001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11100001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11100001 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11100001 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100001 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100001 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11100001 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100001 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100001 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11100001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100001 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11100001 const volatile &&>>{}, "");

struct function_object_11100010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100010>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11100010 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100010 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100010 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11100010 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100010 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100010 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11100010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100010 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11100010 const volatile &&>>{}, "");

struct function_object_11100011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11100011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11100011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11100011 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100011 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100011 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11100011 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100011 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100011 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11100011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100011 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11100011 const volatile &&>>{}, "");

struct function_object_11100100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_11100100>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11100100 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11100100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11100100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11100100 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11100100 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100100 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100100 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11100100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100100 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11100100 const volatile &&>>{}, "");

struct function_object_11100101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11100101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11100101 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11100101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11100101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11100101 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11100101 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100101 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100101 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11100101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100101 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11100101 const volatile &&>>{}, "");

struct function_object_11100110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_11100110>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11100110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11100110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11100110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11100110 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11100110 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100110 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100110 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11100110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100110 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11100110 const volatile &&>>{}, "");

struct function_object_11100111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11100111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11100111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11100111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11100111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11100111 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11100111 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100111 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100111 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11100111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100111 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11100111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11100111 const volatile &&>>{}, "");

struct function_object_11101000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101000>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_11101000 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101000 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101000 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11101000 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101000 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101000 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11101000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101000 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11101000 const volatile &&>>{}, "");

struct function_object_11101001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11101001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11101001 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_11101001 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101001 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101001 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11101001 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101001 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101001 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11101001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101001 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11101001 const volatile &&>>{}, "");

struct function_object_11101010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101010>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11101010 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101010 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101010 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11101010 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101010 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101010 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11101010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101010 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11101010 const volatile &&>>{}, "");

struct function_object_11101011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11101011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11101011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11101011 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101011 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101011 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11101011 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101011 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101011 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11101011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101011 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11101011 const volatile &&>>{}, "");

struct function_object_11101100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_11101100>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11101100 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_11101100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11101100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11101100 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11101100 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101100 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101100 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11101100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101100 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11101100 const volatile &&>>{}, "");

struct function_object_11101101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11101101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11101101 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_11101101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11101101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11101101 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11101101 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101101 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101101 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11101101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101101 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11101101 const volatile &&>>{}, "");

struct function_object_11101110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() const &, function_type_void_t<function_object_11101110>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11101110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11101110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11101110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11101110 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11101110 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101110 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101110 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11101110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101110 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11101110 const volatile &&>>{}, "");

struct function_object_11101111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    // void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11101111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11101111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11101111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11101111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11101111 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11101111 const &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101111 volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101111 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11101111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101111 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11101111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11101111 const volatile &&>>{}, "");

struct function_object_11110000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110000>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110000 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11110000 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110000 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110000 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11110000 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110000 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110000 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11110000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110000 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11110000 const volatile &&>>{}, "");

struct function_object_11110001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11110001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11110001 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11110001 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110001 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110001 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11110001 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110001 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110001 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11110001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110001 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11110001 const volatile &&>>{}, "");

struct function_object_11110010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110010>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11110010 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110010 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110010 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11110010 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110010 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110010 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11110010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110010 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11110010 const volatile &&>>{}, "");

struct function_object_11110011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11110011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11110011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11110011 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110011 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110011 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11110011 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110011 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110011 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11110011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110011 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11110011 const volatile &&>>{}, "");

struct function_object_11110100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_11110100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_11110100 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11110100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11110100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11110100 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11110100 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110100 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110100 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11110100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110100 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11110100 const volatile &&>>{}, "");

struct function_object_11110101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11110101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11110101 &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11110101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11110101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11110101 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11110101 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110101 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110101 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11110101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110101 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11110101 const volatile &&>>{}, "");

struct function_object_11110110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_11110110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_11110110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11110110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11110110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11110110 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11110110 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110110 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110110 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11110110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110110 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11110110 const volatile &&>>{}, "");

struct function_object_11110111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    // void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11110111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11110111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11110111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11110111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11110111 const &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11110111 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110111 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11110111 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11110111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110111 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11110111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11110111 const volatile &&>>{}, "");

struct function_object_11111000
{
    // void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111000>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111000 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_11111000 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111000 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111000 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11111000 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111000 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111000 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11111000 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111000 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111000 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11111000 const volatile &&>>{}, "");

struct function_object_11111001
{
    void operator()() &;
    // void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11111001>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11111001 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_11111001 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111001 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111001 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11111001 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111001 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111001 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11111001 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111001 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111001 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11111001 const volatile &&>>{}, "");

struct function_object_11111010
{
    // void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111010>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111010 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11111010 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111010 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111010 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11111010 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111010 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111010 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11111010 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111010 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111010 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11111010 const volatile &&>>{}, "");

struct function_object_11111011
{
    void operator()() &;
    void operator()() &&;
    // void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11111011>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11111011 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11111011 &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111011 const>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111011 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11111011 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111011 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111011 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11111011 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111011 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111011 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11111011 const volatile &&>>{}, "");

struct function_object_11111100
{
    // void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_11111100>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_11111100 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_11111100 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11111100 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11111100 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11111100 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111100 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111100 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11111100 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111100 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111100 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11111100 const volatile &&>>{}, "");

struct function_object_11111101
{
    void operator()() &;
    // void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11111101>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11111101 &>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_11111101 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11111101 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11111101 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11111101 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111101 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111101 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11111101 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111101 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111101 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11111101 const volatile &&>>{}, "");

struct function_object_11111110
{
    // void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void, function_type_void_t<function_object_11111110>>{}, "");
static_assert(is_same<void, function_type_void_t<function_object_11111110 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11111110 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11111110 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11111110 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11111110 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111110 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111110 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11111110 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111110 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111110 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11111110 const volatile &&>>{}, "");

struct function_object_11111111
{
    void operator()() &;
    void operator()() &&;
    void operator()() const &;
    void operator()() const &&;
    void operator()() volatile &;
    void operator()() volatile &&;
    void operator()() const volatile &;
    void operator()() const volatile &&;
};

static_assert(is_same<void() &, function_type_void_t<function_object_11111111>>{}, "");
static_assert(is_same<void() &, function_type_void_t<function_object_11111111 &>>{}, "");
static_assert(is_same<void() &&, function_type_void_t<function_object_11111111 &&>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11111111 const>>{}, "");
static_assert(is_same<void() const &, function_type_void_t<function_object_11111111 const &>>{}, "");
static_assert(is_same<void() const &&, function_type_void_t<function_object_11111111 const &&>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111111 volatile>>{}, "");
static_assert(is_same<void() volatile &, function_type_void_t<function_object_11111111 volatile &>>{}, "");
static_assert(is_same<void() volatile &&, function_type_void_t<function_object_11111111 volatile &&>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111111 const volatile>>{}, "");
static_assert(is_same<void() const volatile &, function_type_void_t<function_object_11111111 const volatile &>>{}, "");
static_assert(is_same<void() const volatile &&, function_type_void_t<function_object_11111111 const volatile &&>>{}, "");

} // namespace suite_function_object_overload_mixed

//-----------------------------------------------------------------------------

namespace suite_function_object_argument
{

struct function_object_overload_arg
{
    void operator()(bool);
    void operator()(bool, int);
    void operator()(int);
};

static_assert(is_same<function_type_t<function_object_overload_arg, bool>, void(bool)>{}, "");
static_assert(is_same<function_type_t<function_object_overload_arg, bool, int>, void(bool, int)>{}, "");
static_assert(is_same<function_type_t<function_object_overload_arg, int>, void(int)>{}, "");

#if __cpp_noexcept_function_type >= 201510L

struct function_object_noexcept_overload_arg
{
    void operator()(bool) noexcept;
    void operator()(bool, int) noexcept;
    void operator()(int) noexcept;
};

static_assert(is_same<function_type_t<function_object_noexcept_overload_arg, bool>, void(bool) noexcept>{}, "");
static_assert(is_same<function_type_t<function_object_noexcept_overload_arg, bool, int>, void(bool, int) noexcept>{}, "");
static_assert(is_same<function_type_t<function_object_noexcept_overload_arg, int>, void(int) noexcept>{}, "");

#endif

} // namespace suite_function_object_argument

//-----------------------------------------------------------------------------

namespace suite_function_object_template
{

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

} // namespace suite_function_object_template

//-----------------------------------------------------------------------------

namespace suite_lambda
{

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

} // namespace suite_lambda

//-----------------------------------------------------------------------------

int main()
{
    return 0;
}
