#ifndef LEAN_DETAIL_CALL_TRAITS_HPP
#define LEAN_DETAIL_CALL_TRAITS_HPP

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

namespace lean
{
namespace v1
{
namespace detail
{

//-----------------------------------------------------------------------------

template <typename>
struct call_traits_overload;

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...)>
{
    using remove_pointer = R(Args...);
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) const>
{
    using remove_pointer = R(Args...) const;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) const &>
{
    using remove_pointer = R(Args...) const &;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) const &&>
{
    using remove_pointer = R(Args...) const &&;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) const volatile>
{
    using remove_pointer = R(Args...) const volatile;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) const volatile &>
{
    using remove_pointer = R(Args...) const volatile &;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) const volatile &&>
{
    using remove_pointer = R(Args...) const volatile &&;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) volatile>
{
    using remove_pointer = R(Args...) volatile;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) volatile &>
{
    using remove_pointer = R(Args...) volatile &;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) volatile &&>
{
    using remove_pointer = R(Args...) volatile &&;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) &>
{
    using remove_pointer = R(Args...) &;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) &&>
{
    using remove_pointer = R(Args...) &&;
};

#if __cpp_noexcept_function_type >= 201510L

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) noexcept>
{
    using remove_pointer = R(Args...) noexcept;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) const noexcept>
{
    using remove_pointer = R(Args...) const noexcept;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) const & noexcept>
{
    using remove_pointer = R(Args...) const & noexcept;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) const && noexcept>
{
    using remove_pointer = R(Args...) const && noexcept;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) const volatile noexcept>
{
    using remove_pointer = R(Args...) const volatile noexcept;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) const volatile & noexcept>
{
    using remove_pointer = R(Args...) const volatile & noexcept;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) const volatile && noexcept>
{
    using remove_pointer = R(Args...) const volatile && noexcept;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) volatile noexcept>
{
    using remove_pointer = R(Args...) volatile noexcept;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) volatile & noexcept>
{
    using remove_pointer = R(Args...) volatile & noexcept;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) volatile && noexcept>
{
    using remove_pointer = R(Args...) volatile && noexcept;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) & noexcept>
{
    using remove_pointer = R(Args...) & noexcept;
};

template <typename R, typename Class, typename... Args>
struct call_traits_overload<R(Class::*)(Args...) && noexcept>
{
    using remove_pointer = R(Args...) && noexcept;
};

#endif

//-----------------------------------------------------------------------------

template <typename, typename = void>
struct call_traits;

// Member function pointer

template <typename F>
struct call_traits<F, enable_if_t<std::is_member_function_pointer<F>::value>>
{
private:
    using traits = call_traits_overload<remove_cv_t<F>>;
public:
    using remove_pointer = typename traits::remove_pointer;
};

} // namespace detail
} // namespace v1

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
    using type = typename v1::detail::call_traits<T>::remove_pointer;
};

} // namespace lean

#endif // LEAN_DETAIL_CALL_TRAITS_HPP
