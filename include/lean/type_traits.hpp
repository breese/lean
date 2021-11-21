#ifndef LEAN_TYPE_TRAITS_HPP
#define LEAN_TYPE_TRAITS_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <lean/detail/type_traits.hpp>
#include <lean/detail/member_function_traits.hpp>

namespace lean
{

//-----------------------------------------------------------------------------
// remove_member_pointer customization
//
// Removes pointer from member function type.
//
//   T                               | remove_member_pointer_t<T>
// ----------------------------------+----------------------------
//  bool (*)()                       | bool(*)()
//  bool (cls::*)()                  | bool()
//  bool (cls::*)() const            | bool() const
//  bool (cls::*)() const &          | bool() const &
//  bool (cls::*)() const noexcept   | bool() const noexcept
//  bool (cls::*)() const & noexcept | bool() const & noexcept

template <typename T>
struct remove_member_pointer<T, enable_if_t<std::is_member_function_pointer<T>::value>>
{
    using type = typename v1::detail::member_function_traits<remove_cv_t<T>>::remove_pointer;
};

//-----------------------------------------------------------------------------
// is_mutable_reference

template <typename T>
struct is_mutable_reference : std::false_type {};

template <typename T>
struct is_mutable_reference<T&> : std::true_type {};

template <typename T>
struct is_mutable_reference<const T&> : std::false_type {};

template <typename T>
struct is_mutable_reference<T&&> : std::false_type {};

template <typename T>
struct is_mutable_reference<const T&&> : std::false_type {};

//-----------------------------------------------------------------------------
// Perfect forwarding with trivial type decay

template <typename T>
using decay_forward_t = typename std::conditional<
    std::is_trivial<decay_t<T>>::value && !is_mutable_reference<T>::value,
    decay_t<T>,
    add_rvalue_reference_t<T>
    >::type;

//-----------------------------------------------------------------------------
// Workaround for GCC "forming reference to void" error message

template <typename T>
struct is_trivially_move_constructible
    : public std::is_trivially_move_constructible<T> {};

template <>
struct is_trivially_move_constructible<void>
    : public std::false_type {};

} // namespace lean

//-----------------------------------------------------------------------------
// invoke traits

#if __cpp_lib_is_invocable >= 201703L

namespace lean
{

using std::is_invocable;
using std::is_nothrow_invocable;
using std::invoke_result;
using std::invoke_result_t;

} // namespace lean

#else

#include <lean/detail/invoke_traits.hpp>

namespace lean
{

using v1::is_invocable;
using v1::is_nothrow_invocable;
using v1::invoke_result;
using v1::invoke_result_t;

} // namespace lean

#endif

#endif // LEAN_TYPE_TRAITS_HPP
