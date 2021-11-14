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

struct trivial
{
    ~trivial() = default;
};

struct nontrivial
{
    ~nontrivial() {};
};

template <std::size_t N>
using constant = lean::integral_constant<std::size_t, N>;

//-----------------------------------------------------------------------------

namespace remove_member_pointer_suite
{

// Non-member (unchanged)

static_assert(std::is_same<lean::remove_member_pointer_t<bool>, bool>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool *>, bool *>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool &>, bool &>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool &&>, bool &&>{}, "");

static_assert(std::is_same<lean::remove_member_pointer_t<bool()>, bool()>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool() const>, bool() const>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool() const &>, bool() const &>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool() const &&>, bool() const &&>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool() const volatile>, bool() const volatile>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool() const volatile &>, bool() const volatile &>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool() const volatile &&>, bool() const volatile &&>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool() volatile>, bool() volatile>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool() volatile &>, bool() volatile &>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool() volatile &&>, bool() volatile &&>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool() &>, bool() &>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool() &&>, bool() &&>{}, "");

static_assert(std::is_same<lean::remove_member_pointer_t<bool(*)()>, bool(*)()>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(* const)()>, bool(* const)()>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(* volatile)()>, bool(* volatile)()>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(* const volatile)()>, bool(* const volatile)()>{}, "");

// Member pointer

static_assert(std::is_same<lean::remove_member_pointer_t<bool trivial::*>, bool>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool trivial::* const>, bool>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool trivial::* const volatile>, bool>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool trivial::* volatile>, bool>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<const bool trivial::*>, const bool>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<const bool trivial::* const>, const bool>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<const bool trivial::* const volatile>, const bool>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<const bool trivial::* volatile>, const bool>{}, "");

static_assert(std::is_same<lean::remove_member_pointer_t<bool trivial::**>, bool trivial::**>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool trivial::* trivial::*>, bool trivial::*>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool trivial::* const trivial::* volatile>, bool trivial::* const>{}, "");

// Member function pointer

static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)()>, bool()>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::* const)()>, bool()>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::* const volatile)()>, bool()>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::* volatile)()>, bool()>{}, "");

static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() const>, bool() const>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() const &>, bool() const &>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() const &&>, bool() const &&>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() const volatile>, bool() const volatile>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() const volatile &>, bool() const volatile &>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() const volatile &&>, bool() const volatile &&>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() volatile>, bool() volatile>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() volatile &>, bool() volatile &>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() volatile &&>, bool() volatile &&>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() &>, bool() &>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() &&>, bool() &&>{}, "");

#if __cpp_noexcept_function_type >= 201510L

static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::* const)() noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::* const volatile)() noexcept>, bool() noexcept>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::* volatile)() noexcept>, bool() noexcept>{}, "");

static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() const noexcept>, bool() const noexcept>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() const & noexcept>, bool() const & noexcept>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() const && noexcept>, bool() const && noexcept>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() const volatile noexcept>, bool() const volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() const volatile & noexcept>, bool() const volatile & noexcept>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() const volatile && noexcept>, bool() const volatile && noexcept>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() volatile noexcept>, bool() volatile noexcept>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() volatile & noexcept>, bool() volatile & noexcept>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() volatile && noexcept>, bool() volatile && noexcept>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() & noexcept>, bool() & noexcept>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::*)() && noexcept>, bool() && noexcept>{}, "");

#endif

static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::**)()>, bool(trivial::**)()>{}, "pointer");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::* trivial::*)()>, bool(trivial::*)()>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::* const trivial::* volatile)()>, bool(trivial::* const)()>{}, "");

// Reference to member function pointer (unchanged)

static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::* &)()>, bool(trivial::* &)()>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::* const &)()>, bool(trivial::* const &)()>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::* const volatile &)()>, bool(trivial::* const volatile &)()>{}, "");
static_assert(std::is_same<lean::remove_member_pointer_t<bool(trivial::* volatile &)()>, bool(trivial::* volatile &)()>{}, "");

} // namespace remove_member_pointer_suite

//-----------------------------------------------------------------------------

namespace copy_const_suite
{

static_assert(std::is_same<lean::copy_const_t<bool, int>, int>(), "");
static_assert(std::is_same<lean::copy_const_t<const bool, int>, const int>(), "");
static_assert(std::is_same<lean::copy_const_t<const volatile bool, int>, const int>(), "");

static_assert(std::is_same<lean::copy_const_t<bool *, int>, int>(), "");
static_assert(std::is_same<lean::copy_const_t<bool * const, int>, const int>(), "");
static_assert(std::is_same<lean::copy_const_t<bool * volatile, int>, int>(), "");
static_assert(std::is_same<lean::copy_const_t<bool * const volatile, int>, const int>(), "");
static_assert(std::is_same<lean::copy_const_t<const bool *, int>, int>(), "");
static_assert(std::is_same<lean::copy_const_t<const bool * const, int>, const int>(), "");
static_assert(std::is_same<lean::copy_const_t<const bool * volatile, int>, int>(), "");
static_assert(std::is_same<lean::copy_const_t<const bool * const volatile, int>, const int>(), "");
static_assert(std::is_same<lean::copy_const_t<const volatile bool *, int>, int>(), "");
static_assert(std::is_same<lean::copy_const_t<const volatile bool * const, int>, const int>(), "");
static_assert(std::is_same<lean::copy_const_t<const volatile bool * volatile, int>, int>(), "");
static_assert(std::is_same<lean::copy_const_t<const volatile bool * const volatile, int>, const int>(), "");

static_assert(std::is_same<lean::copy_const_t<bool(*)(), int>, int>(), "");
static_assert(std::is_same<lean::copy_const_t<bool(* const)(), int>, const int>(), "");
static_assert(std::is_same<lean::copy_const_t<bool(* volatile)(), int>, int>(), "");
static_assert(std::is_same<lean::copy_const_t<bool(* const volatile)(), int>, const int>(), "");

static_assert(std::is_same<lean::copy_const_t<bool&, int>, int>(), "");
static_assert(std::is_same<lean::copy_const_t<const bool&, int>, int>(), "");
static_assert(std::is_same<lean::copy_const_t<const volatile bool&, int>, int>(), "");

static_assert(std::is_same<lean::copy_const_t<bool&&, int>, int>(), "");
static_assert(std::is_same<lean::copy_const_t<const bool&&, int>, int>(), "");
static_assert(std::is_same<lean::copy_const_t<const volatile bool&&, int>, int>(), "");

static_assert(std::is_same<lean::copy_const_t<bool, const int>, const int>(), "");
static_assert(std::is_same<lean::copy_const_t<const bool, const int>, const int>(), "");

static_assert(std::is_same<lean::copy_const_t<bool(*)(), int(*)()>, int(*)()>(), "");
static_assert(std::is_same<lean::copy_const_t<bool(*)(), int(* const)()>, int(* const)()>(), "");
static_assert(std::is_same<lean::copy_const_t<bool(* const)(), int(*)()>, int(* const)()>(), "");
static_assert(std::is_same<lean::copy_const_t<bool(* const)(), int(* const)()>, int(* const)()>(), "");

static_assert(std::is_same<lean::copy_const_t<bool, int&>, int&>(), "");
static_assert(std::is_same<lean::copy_const_t<bool, const int&>, const int&>(), "");
static_assert(std::is_same<lean::copy_const_t<const bool, int&>, int&>(), "");
static_assert(std::is_same<lean::copy_const_t<const bool, const int&>, const int&>(), "");

static_assert(std::is_same<lean::copy_const_t<bool, int*>, int*>(), "");
static_assert(std::is_same<lean::copy_const_t<bool, const int*>, const int*>(), "");
static_assert(std::is_same<lean::copy_const_t<const bool, int*>, int* const>(), "");
static_assert(std::is_same<lean::copy_const_t<const bool, const int*>, const int* const>(), "");

} // namespace copy_const_suite

//-----------------------------------------------------------------------------

namespace copy_volatile_suite
{

static_assert(std::is_same<lean::copy_volatile_t<bool, int>, int>(), "");
static_assert(std::is_same<lean::copy_volatile_t<bool, volatile int>, volatile int>(), "");
static_assert(std::is_same<lean::copy_volatile_t<volatile bool, int>, volatile int>(), "");
static_assert(std::is_same<lean::copy_volatile_t<volatile bool, volatile int>, volatile int>(), "");

static_assert(std::is_same<lean::copy_volatile_t<bool(*)(), int(*)()>, int(*)()>(), "");
static_assert(std::is_same<lean::copy_volatile_t<bool(*)(), int(* volatile)()>, int(* volatile)()>(), "");
static_assert(std::is_same<lean::copy_volatile_t<bool(* volatile)(), int(*)()>, int(* volatile)()>(), "");
static_assert(std::is_same<lean::copy_volatile_t<bool(* volatile)(), int(* volatile)()>, int(* volatile)()>(), "");

} // namespace copy_volatile_suite

//-----------------------------------------------------------------------------

namespace copy_cv_suite
{

static_assert(std::is_same<lean::copy_cv_t<bool, int>, int>(), "");
static_assert(std::is_same<lean::copy_cv_t<bool, const volatile int>, const volatile int>(), "");
static_assert(std::is_same<lean::copy_cv_t<const volatile bool, int>, const volatile int>(), "");
static_assert(std::is_same<lean::copy_cv_t<const volatile bool, const volatile int>, const volatile int>(), "");

static_assert(std::is_same<lean::copy_cv_t<bool(*)(), int(*)()>, int(*)()>(), "");
static_assert(std::is_same<lean::copy_cv_t<bool(*)(), int(* const volatile)()>, int(* const volatile)()>(), "");
static_assert(std::is_same<lean::copy_cv_t<bool(* const volatile)(), int(*)()>, int(* const volatile)()>(), "");
static_assert(std::is_same<lean::copy_cv_t<bool(* const volatile)(), int(* const volatile)()>, int(* const volatile)()>(), "");

} // namespace copy_cv_suite

//-----------------------------------------------------------------------------

namespace copy_reference_suite
{

static_assert(std::is_same<lean::copy_reference_t<bool, int>, int>(), "");
static_assert(std::is_same<lean::copy_reference_t<bool, int&>, int&>(), "");
static_assert(std::is_same<lean::copy_reference_t<bool&, int>, int&>(), "");
static_assert(std::is_same<lean::copy_reference_t<bool&, int&>, int&>(), "");

static_assert(std::is_same<lean::copy_reference_t<bool(*)(), int(*)()>, int(*)()>(), "");
static_assert(std::is_same<lean::copy_reference_t<bool(*)(), int(* &)()>, int(* &)()>(), "");
static_assert(std::is_same<lean::copy_reference_t<bool(* &)(), int(*)()>, int(* &)()>(), "");
static_assert(std::is_same<lean::copy_reference_t<bool(* &)(), int(* &)()>, int(* &)()>(), "");

static_assert(std::is_same<lean::copy_reference_t<bool, int>, int>(), "");
static_assert(std::is_same<lean::copy_reference_t<bool, int&&>, int&&>(), "");
static_assert(std::is_same<lean::copy_reference_t<bool&&, int>, int&&>(), "");
static_assert(std::is_same<lean::copy_reference_t<bool&&, int&&>, int&&>(), "");

static_assert(std::is_same<lean::copy_reference_t<bool(*)(), int(*)()>, int(*)()>(), "");
static_assert(std::is_same<lean::copy_reference_t<bool(*)(), int(* &&)()>, int(* &&)()>(), "");
static_assert(std::is_same<lean::copy_reference_t<bool(* &&)(), int(*)()>, int(* &&)()>(), "");
static_assert(std::is_same<lean::copy_reference_t<bool(* &&)(), int(* &&)()>, int(* &&)()>(), "");

} // namespace copy_reference_suite

//-----------------------------------------------------------------------------

namespace copy_cvref_suite
{

static_assert(std::is_same<lean::copy_cvref_t<const volatile bool, int>, const volatile int>(), "");
static_assert(std::is_same<lean::copy_cvref_t<const volatile bool, int*>, int* const volatile>(), "");
static_assert(std::is_same<lean::copy_cvref_t<const volatile bool*, int>, int>(), "");
static_assert(std::is_same<lean::copy_cvref_t<const volatile bool*, int*>, int*>(), "");
static_assert(std::is_same<lean::copy_cvref_t<bool* const volatile, int>, const volatile int>(), "");
static_assert(std::is_same<lean::copy_cvref_t<bool* const volatile, int*>, int* const volatile>(), "");

static_assert(std::is_same<lean::copy_cvref_t<const volatile bool, int>, const volatile int>(), "");
static_assert(std::is_same<lean::copy_cvref_t<const volatile bool, int&>, const volatile int&>(), "");
static_assert(std::is_same<lean::copy_cvref_t<const volatile bool&, int>, const volatile int&>(), "");
static_assert(std::is_same<lean::copy_cvref_t<const volatile bool&, int&>, const volatile int&>(), "");

static_assert(std::is_same<lean::copy_cvref_t<bool(* const volatile)(), int(*)()>, int(* const volatile)()>(), "");
static_assert(std::is_same<lean::copy_cvref_t<bool(* const volatile)(), int(* &)()>, int(* const volatile &)()>(), "");
static_assert(std::is_same<lean::copy_cvref_t<bool(* const volatile &)(), int(*)()>, int(* const volatile &)()>(), "");
static_assert(std::is_same<lean::copy_cvref_t<bool(* const volatile &)(), int(* &)()>, int(* const volatile &)()>(), "");

static_assert(std::is_same<lean::copy_cvref_t<const volatile bool, int>, const volatile int>(), "");
static_assert(std::is_same<lean::copy_cvref_t<const volatile bool, int&&>, const volatile int&&>(), "");
static_assert(std::is_same<lean::copy_cvref_t<const volatile bool&&, int>, const volatile int&&>(), "");
static_assert(std::is_same<lean::copy_cvref_t<const volatile bool&&, int&&>, const volatile int&&>(), "");

static_assert(std::is_same<lean::copy_cvref_t<bool(* const volatile)(), int(*)()>, int(* const volatile)()>(), "");
static_assert(std::is_same<lean::copy_cvref_t<bool(* const volatile)(), int(* &&)()>, int(* const volatile &&)()>(), "");
static_assert(std::is_same<lean::copy_cvref_t<bool(* const volatile &&)(), int(*)()>, int(* const volatile &&)()>(), "");
static_assert(std::is_same<lean::copy_cvref_t<bool(* const volatile &&)(), int(* &&)()>, int(* const volatile &&)()>(), "");

} // namespace copy_cvref_suite

//-----------------------------------------------------------------------------

namespace negation_suite
{

static_assert(lean::negation<std::false_type>() == true, "");
static_assert(lean::negation<std::true_type>() == false, "");

} // namespace negation_suite

//-----------------------------------------------------------------------------

namespace conjunction_suite
{

static_assert( lean::conjunction<>(), "");
static_assert(!lean::conjunction<std::false_type>(), "");
static_assert( lean::conjunction<std::true_type>(), "");

static_assert(!lean::conjunction<std::false_type, std::false_type>(), "");
static_assert(!lean::conjunction<std::false_type, std::true_type>(), "");
static_assert(!lean::conjunction<std::true_type, std::false_type>::value, "");
static_assert( lean::conjunction<std::true_type, std::true_type>(), "");

static_assert(!lean::conjunction<std::false_type, std::false_type, std::false_type>(), "");
static_assert(!lean::conjunction<std::false_type, std::false_type, std::true_type>(), "");
static_assert(!lean::conjunction<std::false_type, std::true_type, std::false_type>(), "");
static_assert(!lean::conjunction<std::false_type, std::true_type, std::true_type>(), "");
static_assert(!lean::conjunction<std::true_type, std::false_type, std::false_type>(), "");
static_assert(!lean::conjunction<std::true_type, std::false_type, std::true_type>(), "");
static_assert(!lean::conjunction<std::true_type, std::true_type, std::false_type>(), "");
static_assert( lean::conjunction<std::true_type, std::true_type, std::true_type>(), "");

static_assert(lean::conjunction<std::integral_constant<int, 0>>() == 0, "");
static_assert(lean::conjunction<std::integral_constant<int, 1>>() == 1, "");
static_assert(lean::conjunction<std::integral_constant<int, 2>>() == 2, "");

static_assert(lean::conjunction<std::integral_constant<int, 0>, std::integral_constant<int, 0>>() == 0, "");
static_assert(lean::conjunction<std::integral_constant<int, 0>, std::integral_constant<int, 1>>() == 0, "");
static_assert(lean::conjunction<std::integral_constant<int, 1>, std::integral_constant<int, 0>>() == 0, "");
static_assert(lean::conjunction<std::integral_constant<int, 1>, std::integral_constant<int, 1>>() == 1, "");

static_assert(lean::conjunction<std::integral_constant<int, 1>, std::integral_constant<int, 2>>() == 2, "");
static_assert(lean::conjunction<std::integral_constant<int, 2>, std::integral_constant<int, 1>>() == 1, "");

} // namespace conjunction_suite

//-----------------------------------------------------------------------------

namespace disjunction_suite
{

static_assert(!lean::disjunction<>(), "");
static_assert(!lean::disjunction<std::false_type>(), "");
static_assert( lean::disjunction<std::true_type>(), "");

static_assert(!lean::disjunction<std::false_type, std::false_type>(), "");
static_assert( lean::disjunction<std::false_type, std::true_type>(), "");
static_assert( lean::disjunction<std::true_type, std::false_type>::value, "");
static_assert( lean::disjunction<std::true_type, std::true_type>(), "");

static_assert(!lean::disjunction<std::false_type, std::false_type, std::false_type>(), "");
static_assert( lean::disjunction<std::false_type, std::false_type, std::true_type>(), "");
static_assert( lean::disjunction<std::false_type, std::true_type, std::false_type>(), "");
static_assert( lean::disjunction<std::false_type, std::true_type, std::true_type>(), "");
static_assert( lean::disjunction<std::true_type, std::false_type, std::false_type>(), "");
static_assert( lean::disjunction<std::true_type, std::false_type, std::true_type>(), "");
static_assert( lean::disjunction<std::true_type, std::true_type, std::false_type>(), "");
static_assert( lean::disjunction<std::true_type, std::true_type, std::true_type>(), "");

static_assert(lean::disjunction<std::integral_constant<int, 0>>() == 0, "");
static_assert(lean::disjunction<std::integral_constant<int, 1>>() == 1, "");
static_assert(lean::disjunction<std::integral_constant<int, 2>>() == 2, "");

static_assert(lean::disjunction<std::integral_constant<int, 0>, std::integral_constant<int, 0>>() == 0, "");
static_assert(lean::disjunction<std::integral_constant<int, 0>, std::integral_constant<int, 1>>() == 1, "");
static_assert(lean::disjunction<std::integral_constant<int, 1>, std::integral_constant<int, 0>>() == 1, "");
static_assert(lean::disjunction<std::integral_constant<int, 1>, std::integral_constant<int, 1>>() == 1, "");

static_assert(lean::disjunction<std::integral_constant<int, 1>, std::integral_constant<int, 2>>() == 1, "");
static_assert(lean::disjunction<std::integral_constant<int, 2>, std::integral_constant<int, 1>>() == 2, "");

} // namespace disjunction_suite

//-----------------------------------------------------------------------------

namespace type_identity_suite
{

static_assert(std::is_same<lean::type_identity_t<void>, void>(), "");

static_assert(std::is_same<lean::type_identity_t<int>, int>(), "");
static_assert(std::is_same<lean::type_identity_t<int&>, int&>(), "");
static_assert(std::is_same<lean::type_identity_t<int&&>, int&&>(), "");
static_assert(std::is_same<lean::type_identity_t<const int>, const int>(), "");
static_assert(std::is_same<lean::type_identity_t<const int&>, const int&>(), "");
static_assert(std::is_same<lean::type_identity_t<const int&&>, const int&&>(), "");

static_assert(!std::is_same<lean::type_identity_t<int>, void>(), "");
static_assert(!std::is_same<lean::type_identity_t<void>, int>(), "");

} // namespace type_identity_suite

//-----------------------------------------------------------------------------

namespace type_front_suite
{

static_assert(std::is_same<lean::type_front_t<bool>, bool>(), "");
static_assert(std::is_same<lean::type_front_t<bool, int>, bool>(), "");
static_assert(std::is_same<lean::type_front_t<bool, int, float>, bool>(), "");

static_assert(std::is_same<lean::type_front_t<bool&>, bool&>(), "");
static_assert(std::is_same<lean::type_front_t<bool&&>, bool&&>(), "");
static_assert(std::is_same<lean::type_front_t<const bool&>, const bool&>(), "");

} // namespace type_front_suite

//-----------------------------------------------------------------------------

namespace type_element_suite
{

static_assert(std::is_same<lean::type_element_t<0, bool>, bool>(), "");
static_assert(std::is_same<lean::type_element_t<0, bool, int>, bool>(), "");
static_assert(std::is_same<lean::type_element_t<1, bool, int>, int>(), "");
static_assert(std::is_same<lean::type_element_t<0, bool, int, float>, bool>(), "");
static_assert(std::is_same<lean::type_element_t<1, bool, int, float>, int>(), "");
static_assert(std::is_same<lean::type_element_t<2, bool, int, float>, float>(), "");

static_assert(std::is_same<lean::type_element_t<0, bool&>, bool&>(), "");
static_assert(std::is_same<lean::type_element_t<0, bool&&>, bool&&>(), "");
static_assert(std::is_same<lean::type_element_t<0, const bool&>, const bool&>(), "");

} // namespace type_element_suite

//-----------------------------------------------------------------------------

namespace type_sizeof_suite
{

static_assert(lean::type_sizeof<int>() == sizeof(int), "");
static_assert(lean::type_sizeof<int&>() == sizeof(int&), "");
static_assert(lean::type_sizeof<int&&>() == sizeof(int&&), "");
static_assert(lean::type_sizeof<const int>() == sizeof(const int), "");
static_assert(lean::type_sizeof<const int&>() == sizeof(const int&), "");
static_assert(lean::type_sizeof<const int&&>() == sizeof(const int&&), "");

static_assert(lean::type_sizeof<int[2]>() == sizeof(int[2]), "");
static_assert(lean::type_sizeof<int[2]>() != sizeof(int[1]), "");

} // namespace type_sizeof_suite

//-----------------------------------------------------------------------------

namespace type_predicate_min_suite
{

static_assert(std::is_same<lean::type_predicate_min_t<constant<0>, constant<0>>, constant<0>>(), "");
static_assert(std::is_same<lean::type_predicate_min_t<constant<1>, constant<0>>, constant<0>>(), "");
static_assert(std::is_same<lean::type_predicate_min_t<constant<0>, constant<1>>, constant<0>>(), "");
static_assert(std::is_same<lean::type_predicate_min_t<constant<1>, constant<1>>, constant<1>>(), "");

static_assert(std::is_same<lean::type_predicate_min_with_t<lean::type_sizeof, int[1], int[1]>, int[1]>(), "");
static_assert(std::is_same<lean::type_predicate_min_with_t<lean::type_sizeof, int[2], int[1]>, int[1]>(), "");
static_assert(std::is_same<lean::type_predicate_min_with_t<lean::type_sizeof, int[1], int[2]>, int[1]>(), "");
static_assert(std::is_same<lean::type_predicate_min_with_t<lean::type_sizeof, int[2], int[2]>, int[2]>(), "");

static_assert(std::is_same<lean::type_predicate_min_with_t<lean::type_sizeof, int, int>, int>(), "");
static_assert(std::is_same<lean::type_predicate_min_with_t<lean::type_sizeof, char, int>, char>(), "");

} // namespace type_predicate_min_suite

//-----------------------------------------------------------------------------

namespace type_predicate_max_suite
{

static_assert(std::is_same<lean::type_predicate_max_t<constant<0>, constant<0>>, constant<0>>(), "");
static_assert(std::is_same<lean::type_predicate_max_t<constant<1>, constant<0>>, constant<1>>(), "");
static_assert(std::is_same<lean::type_predicate_max_t<constant<0>, constant<1>>, constant<1>>(), "");
static_assert(std::is_same<lean::type_predicate_max_t<constant<1>, constant<1>>, constant<1>>(), "");

static_assert(std::is_same<lean::type_predicate_max_with_t<lean::type_sizeof, int[1], int[1]>, int[1]>(), "");
static_assert(std::is_same<lean::type_predicate_max_with_t<lean::type_sizeof, int[2], int[1]>, int[2]>(), "");
static_assert(std::is_same<lean::type_predicate_max_with_t<lean::type_sizeof, int[1], int[2]>, int[2]>(), "");
static_assert(std::is_same<lean::type_predicate_max_with_t<lean::type_sizeof, int[2], int[2]>, int[2]>(), "");

static_assert(std::is_same<lean::type_predicate_max_with_t<lean::type_sizeof, int, int>, int>(), "");
static_assert(std::is_same<lean::type_predicate_max_with_t<lean::type_sizeof, char, int>, int>(), "");

} // namespace type_predicate_max_suite

//-----------------------------------------------------------------------------

namespace type_contains_suite
{

static_assert(!lean::type_contains<bool>(), "");
static_assert( lean::type_contains<bool, bool>(), "");
static_assert( lean::type_contains<bool, bool, int>(), "");
static_assert( lean::type_contains<bool, int, bool>(), "");
static_assert( lean::type_contains<bool, bool, bool>(), "");

static_assert(!lean::type_contains<float, bool>(), "");
static_assert(!lean::type_contains<float, bool, int>(), "");

static_assert( lean::type_contains<int, int>(), "");
static_assert(!lean::type_contains<int, int&>(), "");
static_assert(!lean::type_contains<int, int&&>(), "");
static_assert(!lean::type_contains<int, const int>(), "");
static_assert(!lean::type_contains<int, const int&>(), "");
static_assert(!lean::type_contains<int, const int&&>(), "");

static_assert(!lean::type_contains<bool, int>(), "");
static_assert(!lean::type_contains<bool, int&>(), "");
static_assert(!lean::type_contains<bool, int&&>(), "");
static_assert(!lean::type_contains<bool, const int>(), "");
static_assert(!lean::type_contains<bool, const int&>(), "");
static_assert(!lean::type_contains<bool, const int&&>(), "");

static_assert( lean::type_contains<int, int>(), "");
static_assert(!lean::type_contains<int&, int>(), "");
static_assert(!lean::type_contains<int&&, int>(), "");
static_assert(!lean::type_contains<const int, int>(), "");
static_assert(!lean::type_contains<const int&, int>(), "");
static_assert(!lean::type_contains<const int&&, int>(), "");

static_assert(!lean::type_contains<int, int&, int&&, const int, const int&, const int&&>(), "");
static_assert( lean::type_contains<int&, int&, int&&, const int, const int&, const int&&>(), "");
static_assert( lean::type_contains<int&&, int&, int&&, const int, const int&, const int&&>(), "");
static_assert( lean::type_contains<const int, int&, int&&, const int, const int&, const int&&>(), "");
static_assert( lean::type_contains<const int&, int&, int&&, const int, const int&, const int&&>(), "");
static_assert( lean::type_contains<const int&&, int&, int&&, const int, const int&, const int&&>(), "");

} // namespace type_contains_suite


//-----------------------------------------------------------------------------

namespace type_fold_left_suite
{

static_assert(std::is_same<lean::type_fold_left_t<lean::type_predicate_min, constant<1>>, constant<1>>(), "");
static_assert(std::is_same<lean::type_fold_left_t<lean::type_predicate_min, constant<1>, constant<2>>, constant<1>>(), "");

static_assert(std::is_same<lean::type_fold_left_t<lean::type_predicate_min, constant<1>, constant<2>, constant<3>>, constant<1>>(), "");
static_assert(std::is_same<lean::type_fold_left_t<lean::type_predicate_min, constant<2>, constant<3>, constant<1>>, constant<1>>(), "");
static_assert(std::is_same<lean::type_fold_left_t<lean::type_predicate_min, constant<3>, constant<1>, constant<2>>, constant<1>>(), "");

static_assert(std::is_same<lean::type_fold_left_t<lean::type_predicate_max, constant<1>, constant<2>, constant<3>>, constant<3>>(), "");
static_assert(std::is_same<lean::type_fold_left_t<lean::type_predicate_max, constant<2>, constant<3>, constant<1>>, constant<3>>(), "");
static_assert(std::is_same<lean::type_fold_left_t<lean::type_predicate_max, constant<3>, constant<1>, constant<2>>, constant<3>>(), "");

template <typename Lhs, typename Rhs>
struct type_predicate_min_sizeof : public lean::type_predicate_min_with<lean::type_sizeof, Lhs, Rhs> {};

static_assert(std::is_same<lean::type_fold_left_t<type_predicate_min_sizeof, int[1]>, int[1]>(), "");
static_assert(std::is_same<lean::type_fold_left_t<type_predicate_min_sizeof, int[1], int[2]>, int[1]>(), "");

static_assert(std::is_same<lean::type_fold_left_t<type_predicate_min_sizeof, int[1], int[2], int[3]>, int[1]>(), "");
static_assert(std::is_same<lean::type_fold_left_t<type_predicate_min_sizeof, int[2], int[3], int[1]>, int[1]>(), "");
static_assert(std::is_same<lean::type_fold_left_t<type_predicate_min_sizeof, int[3], int[1], int[2]>, int[1]>(), "");

// Indices

static_assert(lean::type_fold_left<lean::type_predicate_min, constant<1>, constant<2>, constant<3>>() == 0, "");
static_assert(lean::type_fold_left<lean::type_predicate_min, constant<2>, constant<3>, constant<1>>() == 2, "");
static_assert(lean::type_fold_left<lean::type_predicate_min, constant<3>, constant<1>, constant<2>>() == 1, "");

} // namespace type_fold_left_suite

//-----------------------------------------------------------------------------

namespace type_min_suite
{

static_assert(std::is_same<lean::type_min_with_t<lean::type_sizeof, int[1], int[2], int[3]>, int[1]>(), "");
static_assert(std::is_same<lean::type_min_with_t<lean::type_sizeof, int[3], int[1], int[2]>, int[1]>(), "");
static_assert(std::is_same<lean::type_min_with_t<lean::type_sizeof, int[3], int[2], int[1]>, int[1]>(), "");

static_assert(lean::type_find_min_with<lean::type_sizeof, int[1], int[2], int[3]>() == 0, "");
static_assert(lean::type_find_min_with<lean::type_sizeof, int[2], int[3], int[1]>() == 2, "");
static_assert(lean::type_find_min_with<lean::type_sizeof, int[3], int[1], int[2]>() == 1, "");

static_assert(lean::type_find_min<constant<1>, constant<2>, constant<3>>() == 0, "");
static_assert(lean::type_find_min<constant<2>, constant<3>, constant<1>>() == 2, "");
static_assert(lean::type_find_min<constant<3>, constant<1>, constant<2>>() == 1, "");

} // namespace type_min_suite

//-----------------------------------------------------------------------------

namespace type_max_suite
{

static_assert(std::is_same<lean::type_max_with_t<lean::type_sizeof, int[1], int[2], int[3]>, int[3]>(), "");
static_assert(std::is_same<lean::type_max_with_t<lean::type_sizeof, int[3], int[1], int[2]>, int[3]>(), "");
static_assert(std::is_same<lean::type_max_with_t<lean::type_sizeof, int[3], int[2], int[1]>, int[3]>(), "");

static_assert(lean::type_find_max_with<lean::type_sizeof, int[1], int[2], int[3]>() == 2, "");
static_assert(lean::type_find_max_with<lean::type_sizeof, int[2], int[3], int[1]>() == 1, "");
static_assert(lean::type_find_max_with<lean::type_sizeof, int[3], int[1], int[2]>() == 0, "");

static_assert(lean::type_find_max<constant<1>, constant<2>, constant<3>>() == 2, "");
static_assert(lean::type_find_max<constant<2>, constant<3>, constant<1>>() == 1, "");
static_assert(lean::type_find_max<constant<3>, constant<1>, constant<2>>() == 0, "");

} // namespace type_max_suite

//-----------------------------------------------------------------------------

namespace pack_rebind_suite
{

template <typename...> struct test_pack;

static_assert(std::is_same<lean::pack_rebind_t<test_pack<>, lean::pack<>>, test_pack<>>{}, "");
static_assert(std::is_same<lean::pack_rebind_t<test_pack<>, lean::pack<bool>>, test_pack<bool>>{}, "");
static_assert(std::is_same<lean::pack_rebind_t<test_pack<>, lean::pack<bool, int>>, test_pack<bool, int>>{}, "");
static_assert(std::is_same<lean::pack_rebind_t<test_pack<>, lean::pack<bool, int, float>>, test_pack<bool, int, float>>{}, "");

static_assert(std::is_same<lean::pack_rebind_t<test_pack<bool>, lean::pack<>>, test_pack<>>{}, "");
static_assert(std::is_same<lean::pack_rebind_t<test_pack<bool, int>, lean::pack<>>, test_pack<>>{}, "");
static_assert(std::is_same<lean::pack_rebind_t<test_pack<bool, int, float>, lean::pack<>>, test_pack<>>{}, "");

} // namespace pack_rebind_suite

//-----------------------------------------------------------------------------

namespace is_complete_suite
{

static_assert(lean::is_complete<int>::value, "");
static_assert(lean::is_complete<trivial>::value, "");
static_assert(lean::is_complete<nontrivial>::value, "");

struct undef;

static_assert(!lean::is_complete<undef>::value, "");

} // namespace is_complete_suite

//-----------------------------------------------------------------------------

namespace is_mutable_reference_suite
{

static_assert(!lean::is_mutable_reference<int>::value, "no");
static_assert( lean::is_mutable_reference<int&>::value, "yes");
static_assert(!lean::is_mutable_reference<int&&>::value, "no");
static_assert(!lean::is_mutable_reference<const int>::value, "no");
static_assert(!lean::is_mutable_reference<const int&>::value, "no");
static_assert(!lean::is_mutable_reference<const int&&>::value, "no");

static_assert(!lean::is_mutable_reference<int[]>::value, "no");
static_assert( lean::is_mutable_reference<int(&)[]>::value, "yes");
static_assert(!lean::is_mutable_reference<int(&&)[]>::value, "no");
static_assert(!lean::is_mutable_reference<const int[]>::value, "no");
static_assert(!lean::is_mutable_reference<const int(&)[]>::value, "no");
static_assert(!lean::is_mutable_reference<const int(&&)[]>::value, "no");

static_assert(!lean::is_mutable_reference<int[4]>::value, "no");
static_assert( lean::is_mutable_reference<int(&)[4]>::value, "yes");
static_assert(!lean::is_mutable_reference<int(&&)[4]>::value, "no");
static_assert(!lean::is_mutable_reference<const int[4]>::value, "no");
static_assert(!lean::is_mutable_reference<const int(&)[4]>::value, "no");
static_assert(!lean::is_mutable_reference<const int(&&)[4]>::value, "no");

static_assert(!lean::is_mutable_reference<trivial>::value, "no");
static_assert( lean::is_mutable_reference<trivial&>::value, "yes");
static_assert(!lean::is_mutable_reference<trivial&&>::value, "no");
static_assert(!lean::is_mutable_reference<const trivial>::value, "no");
static_assert(!lean::is_mutable_reference<const trivial&>::value, "no");
static_assert(!lean::is_mutable_reference<const trivial&&>::value, "no");

static_assert(!lean::is_mutable_reference<trivial[]>::value, "no");
static_assert( lean::is_mutable_reference<trivial(&)[]>::value, "yes");
static_assert(!lean::is_mutable_reference<trivial(&&)[]>::value, "no");
static_assert(!lean::is_mutable_reference<const trivial[]>::value, "no");
static_assert(!lean::is_mutable_reference<const trivial(&)[]>::value, "no");
static_assert(!lean::is_mutable_reference<const trivial(&&)[]>::value, "no");

static_assert(!lean::is_mutable_reference<trivial[4]>::value, "no");
static_assert( lean::is_mutable_reference<trivial(&)[4]>::value, "yes");
static_assert(!lean::is_mutable_reference<trivial(&&)[4]>::value, "no");
static_assert(!lean::is_mutable_reference<const trivial[4]>::value, "no");
static_assert(!lean::is_mutable_reference<const trivial(&)[4]>::value, "no");
static_assert(!lean::is_mutable_reference<const trivial(&&)[4]>::value, "no");

static_assert(!lean::is_mutable_reference<nontrivial>::value, "no");
static_assert( lean::is_mutable_reference<nontrivial&>::value, "yes");
static_assert(!lean::is_mutable_reference<nontrivial&&>::value, "no");
static_assert(!lean::is_mutable_reference<const nontrivial>::value, "no");
static_assert(!lean::is_mutable_reference<const nontrivial&>::value, "no");
static_assert(!lean::is_mutable_reference<const nontrivial&&>::value, "no");

static_assert(!lean::is_mutable_reference<nontrivial[]>::value, "no");
static_assert( lean::is_mutable_reference<nontrivial(&)[]>::value, "yes");
static_assert(!lean::is_mutable_reference<nontrivial(&&)[]>::value, "no");
static_assert(!lean::is_mutable_reference<const nontrivial[]>::value, "no");
static_assert(!lean::is_mutable_reference<const nontrivial(&)[]>::value, "no");
static_assert(!lean::is_mutable_reference<const nontrivial(&&)[]>::value, "no");

static_assert(!lean::is_mutable_reference<nontrivial[4]>::value, "no");
static_assert( lean::is_mutable_reference<nontrivial(&)[4]>::value, "yes");
static_assert(!lean::is_mutable_reference<nontrivial(&&)[4]>::value, "no");
static_assert(!lean::is_mutable_reference<const nontrivial[4]>::value, "no");
static_assert(!lean::is_mutable_reference<const nontrivial(&)[4]>::value, "no");
static_assert(!lean::is_mutable_reference<const nontrivial(&&)[4]>::value, "no");

} // namespace is_mutable_reference_suite

//-----------------------------------------------------------------------------

namespace decay_forward_suite
{

static_assert(std::is_same<lean::decay_forward_t<int>, int>::value, "value");
static_assert(std::is_same<lean::decay_forward_t<int&>, int&>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<int&&>, int>::value, "value");
static_assert(std::is_same<lean::decay_forward_t<const int>, int>::value, "value");
static_assert(std::is_same<lean::decay_forward_t<const int&>, int>::value, "value");
static_assert(std::is_same<lean::decay_forward_t<const int&&>, int>::value, "value");

static_assert(std::is_same<lean::decay_forward_t<int[]>, int *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<int(&)[]>, int(&)[]>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<int(&&)[]>, int *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const int[]>, const int *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const int(&)[]>, const int *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const int(&&)[]>, const int *>::value, "pointer");

static_assert(std::is_same<lean::decay_forward_t<int[4]>, int *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<int(&)[4]>, int(&)[4]>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<int(&&)[4]>, int *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const int[4]>, const int *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const int(&)[4]>, const int *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const int(&&)[4]>, const int *>::value, "pointer");

static_assert(std::is_same<lean::decay_forward_t<int *>, int *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const int *>, const int *>::value, "pointer");

static_assert(std::is_same<lean::decay_forward_t<trivial>, trivial>::value, "value");
static_assert(std::is_same<lean::decay_forward_t<trivial&>, trivial&>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<trivial&&>, trivial>::value, "value");
static_assert(std::is_same<lean::decay_forward_t<const trivial>, trivial>::value, "value");
static_assert(std::is_same<lean::decay_forward_t<const trivial&>, trivial>::value, "value");
static_assert(std::is_same<lean::decay_forward_t<const trivial&&>, trivial>::value, "value");

static_assert(std::is_same<lean::decay_forward_t<trivial[]>, trivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<trivial(&)[]>, trivial(&)[]>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<trivial(&&)[]>, trivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const trivial[]>, const trivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const trivial(&)[]>, const trivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const trivial(&&)[]>, const trivial *>::value, "pointer");

static_assert(std::is_same<lean::decay_forward_t<trivial[4]>, trivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<trivial(&)[4]>, trivial(&)[4]>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<trivial(&&)[4]>, trivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const trivial[4]>, const trivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const trivial(&)[4]>, const trivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const trivial(&&)[4]>, const trivial *>::value, "pointer");

static_assert(std::is_same<lean::decay_forward_t<trivial *>, trivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const trivial *>, const trivial *>::value, "pointer");

static_assert(std::is_same<lean::decay_forward_t<nontrivial>, nontrivial&&>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<nontrivial&>, nontrivial&>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<nontrivial&&>, nontrivial&&>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial>, const  nontrivial&&>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial&>, const nontrivial&>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial&&>, const nontrivial&&>::value, "reference");

static_assert(std::is_same<lean::decay_forward_t<nontrivial[]>, nontrivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<nontrivial(&)[]>, nontrivial(&)[]>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<nontrivial(&&)[]>, nontrivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial[]>, const nontrivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial(&)[]>, const nontrivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial(&&)[]>, const nontrivial *>::value, "pointer");

static_assert(std::is_same<lean::decay_forward_t<nontrivial[4]>, nontrivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<nontrivial(&)[4]>, nontrivial(&)[4]>::value, "reference");
static_assert(std::is_same<lean::decay_forward_t<nontrivial(&&)[4]>, nontrivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial[4]>, const nontrivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial(&)[4]>, const nontrivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial(&&)[4]>, const nontrivial *>::value, "pointer");

static_assert(std::is_same<lean::decay_forward_t<nontrivial *>, nontrivial *>::value, "pointer");
static_assert(std::is_same<lean::decay_forward_t<const nontrivial *>, const nontrivial *>::value, "pointer");

} // namespace decay_forward_suite

//-----------------------------------------------------------------------------

int main()
{
    return 0;
}
