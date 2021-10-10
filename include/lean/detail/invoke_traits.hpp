#ifndef LEAN_DETAIL_INVOKE_HPP
#define LEAN_DETAIL_INVOKE_HPP

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

template <typename, typename = void>
struct has_call_operator : std::false_type {};

template <typename F, typename... Args>
struct has_call_operator<pack<F, Args...>,
                         decltype(std::declval<F>()(std::declval<Args>()...))>
    : std::true_type
{
};

//-----------------------------------------------------------------------------

// If nothing else is matched...

template <typename, typename = void>
struct invoke_traits_fallback
    : public std::false_type
{
    enum : bool { is_nothrow = false };
};

// General traits template (specialized below)

template <typename F, typename... Args>
struct invoke_traits
    : public invoke_traits_fallback<pack<F, Args...>>
{
};

// Function object

template <typename F, typename... Args>
struct invoke_traits_fallback<pack<F, Args...>,
                             enable_if_t<has_call_operator<pack<F, Args...>>::value>>
    : public invoke_traits<decltype(&decay_t<F>::operator()),
                           add_pointer_t<decay_t<F>>,
                           Args...>
{
};

//-----------------------------------------------------------------------------
// R(Args...)

template <typename R, typename... Args>
struct invoke_traits<R(Args...), Args...>
    : public std::true_type
{
    enum : bool { is_nothrow = false };
    using result_type = R;
};

template <typename R, typename... Args>
struct invoke_traits<R(*)(Args...), Args...>
    : public invoke_traits<R(Args...), Args...>
{
};

template <typename R, typename... Args>
struct invoke_traits<R(&)(Args...), Args...>
    : public invoke_traits<R(Args...), Args...>
{
};

template <typename R, typename... Args>
struct invoke_traits<R(&&)(Args...), Args...>
    : public invoke_traits<R(Args...), Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...), Class *, Args...>
    : public invoke_traits<R(Args...), Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) &, Class *, Args...>
    : public invoke_traits<R(Args...), Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...), Class&, Args...>
    : public invoke_traits<R(Args...), Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) &, Class&, Args...>
    : public invoke_traits<R(Args...), Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...), Class&&, Args...>
    : public invoke_traits<R(Args...), Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) &&, Class&&, Args...>
    : public invoke_traits<R(Args...), Args...>
{
};

//-----------------------------------------------------------------------------
// R(Args...) const

template <typename R, typename... Args>
struct invoke_traits<R(Args...) const, Args...>
    : public std::true_type
{
    enum : bool { is_nothrow = false };
    using result_type = R;
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const, Class *, Args...>
    : public invoke_traits<R(Args...) const, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const, const Class *, Args...>
    : public invoke_traits<R(Args...) const, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const &, Class *, Args...>
    : public invoke_traits<R(Args...) const, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const &, const Class *, Args...>
    : public invoke_traits<R(Args...) const, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const, Class&, Args...>
    : public invoke_traits<R(Args...) const, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const &, Class&, Args...>
    : public invoke_traits<R(Args...) const, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const, const Class&, Args...>
    : public invoke_traits<R(Args...) const, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const &, const Class&, Args...>
    : public invoke_traits<R(Args...) const, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const, Class&&, Args...>
    : public invoke_traits<R(Args...) const, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const &&, Class&&, Args...>
    : public invoke_traits<R(Args...) const, Args...>
{
};


template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const, const Class&&, Args...>
    : public invoke_traits<R(Args...) const, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const &&, const Class&&, Args...>
    : public invoke_traits<R(Args...) const, Args...>
{
};

//-----------------------------------------------------------------------------
// R(Args...) noexcept

#if __cpp_noexcept_function_type >= 201510L

template <typename R, typename... Args>
struct invoke_traits<R(Args...) noexcept, Args...>
    : public std::true_type
{
    enum : bool { is_nothrow = true };
    using result_type = R;
};

template <typename R, typename... Args>
struct invoke_traits<R(*)(Args...) noexcept, Args...>
    : public invoke_traits<R(Args...) noexcept, Args...>
{
};

template <typename R, typename... Args>
struct invoke_traits<R(&)(Args...) noexcept, Args...>
    : public invoke_traits<R(Args...) noexcept, Args...>
{
};

template <typename R, typename... Args>
struct invoke_traits<R(&&)(Args...) noexcept, Args...>
    : public invoke_traits<R(Args...) noexcept, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) noexcept, Class *, Args...>
    : public invoke_traits<R(Args...) noexcept, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) & noexcept, Class *, Args...>
    : public invoke_traits<R(Args...) noexcept, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) noexcept, Class&, Args...>
    : public invoke_traits<R(Args...) noexcept, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) & noexcept, Class&, Args...>
    : public invoke_traits<R(Args...) noexcept, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) noexcept, Class&&, Args...>
    : public invoke_traits<R(Args...) noexcept, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) && noexcept, Class&&, Args...>
    : public invoke_traits<R(Args...) noexcept, Args...>
{
};

#endif

//-----------------------------------------------------------------------------
// R(Args...) const noexcept

#if __cpp_noexcept_function_type >= 201510L

template <typename R, typename... Args>
struct invoke_traits<R(Args...) const noexcept, Args...>
    : public std::true_type
{
    enum : bool { is_nothrow = true };
    using result_type = R;
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const noexcept, Class *, Args...>
    : public invoke_traits<R(Args...) const noexcept, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const noexcept, const Class *, Args...>
    : public invoke_traits<R(Args...) const noexcept, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const & noexcept, Class *, Args...>
    : public invoke_traits<R(Args...) const noexcept, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const & noexcept, const Class *, Args...>
    : public invoke_traits<R(Args...) const noexcept, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const noexcept, Class&, Args...>
    : public invoke_traits<R(Args...) const noexcept, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const & noexcept, Class&, Args...>
    : public invoke_traits<R(Args...) const noexcept, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const noexcept, const Class&, Args...>
    : public invoke_traits<R(Args...) const noexcept, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const & noexcept, const Class&, Args...>
    : public invoke_traits<R(Args...) const noexcept, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const noexcept, Class&&, Args...>
    : public invoke_traits<R(Args...) const noexcept, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const && noexcept, Class&&, Args...>
    : public invoke_traits<R(Args...) const noexcept, Args...>
{
};


template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const noexcept, const Class&&, Args...>
    : public invoke_traits<R(Args...) const noexcept, Args...>
{
};

template <typename R, typename Class, typename... Args>
struct invoke_traits<R(Class::*)(Args...) const && noexcept, const Class&&, Args...>
    : public invoke_traits<R(Args...) const noexcept, Args...>
{
};

#endif

} // namespace detail
} // namespace v1
} // namespace lean

#endif // LEAN_DETAIL_INVOKE_HPP
