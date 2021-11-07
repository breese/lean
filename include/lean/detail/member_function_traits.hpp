#ifndef LEAN_DETAIL_MEMBER_FUNCTION_TRAITS_HPP
#define LEAN_DETAIL_MEMBER_FUNCTION_TRAITS_HPP

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

template <typename>
struct member_function_traits;

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...)>
{
    using remove_pointer = R(Args...);
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) const>
{
    using remove_pointer = R(Args...) const;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) const &>
{
    using remove_pointer = R(Args...) const &;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) const &&>
{
    using remove_pointer = R(Args...) const &&;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) const volatile>
{
    using remove_pointer = R(Args...) const volatile;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) const volatile &>
{
    using remove_pointer = R(Args...) const volatile &;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) const volatile &&>
{
    using remove_pointer = R(Args...) const volatile &&;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) volatile>
{
    using remove_pointer = R(Args...) volatile;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) volatile &>
{
    using remove_pointer = R(Args...) volatile &;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) volatile &&>
{
    using remove_pointer = R(Args...) volatile &&;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) &>
{
    using remove_pointer = R(Args...) &;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) &&>
{
    using remove_pointer = R(Args...) &&;
};

#if __cpp_noexcept_function_type >= 201510L

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) noexcept>
{
    using remove_pointer = R(Args...) noexcept;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) const noexcept>
{
    using remove_pointer = R(Args...) const noexcept;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) const & noexcept>
{
    using remove_pointer = R(Args...) const & noexcept;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) const && noexcept>
{
    using remove_pointer = R(Args...) const && noexcept;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) const volatile noexcept>
{
    using remove_pointer = R(Args...) const volatile noexcept;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) const volatile & noexcept>
{
    using remove_pointer = R(Args...) const volatile & noexcept;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) const volatile && noexcept>
{
    using remove_pointer = R(Args...) const volatile && noexcept;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) volatile noexcept>
{
    using remove_pointer = R(Args...) volatile noexcept;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) volatile & noexcept>
{
    using remove_pointer = R(Args...) volatile & noexcept;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) volatile && noexcept>
{
    using remove_pointer = R(Args...) volatile && noexcept;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) & noexcept>
{
    using remove_pointer = R(Args...) & noexcept;
};

template <typename R, typename Class, typename... Args>
struct member_function_traits<R(Class::*)(Args...) && noexcept>
{
    using remove_pointer = R(Args...) && noexcept;
};

#endif

} // namespace detail
} // namespace v1
} // namespace lean

#endif // LEAN_DETAIL_MEMBER_FUNCTION__TRAITS_HPP
