#ifndef LEAN_DETAIL_FUNCTION_TYPE_HPP
#define LEAN_DETAIL_FUNCTION_TYPE_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <lean/type_traits.hpp>

namespace lean
{
namespace v1
{
namespace detail
{

//-----------------------------------------------------------------------------

template <typename, typename...>
struct function_traits;

template <typename R, typename... Args>
struct function_traits<R(Args...)>
{
    static constexpr bool is_const = false;
    static constexpr bool is_noexcept = false;

    using type = R(Args...);
    using result_type = R;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const>
{
    static constexpr bool is_const = true;
    static constexpr bool is_noexcept = false;

    using type = R(Args...) const;
    using result_type = R;
};

#if __cpp_noexcept_function_type

template <typename R, typename... Args>
struct function_traits<R(Args...) noexcept>
{
    static constexpr bool is_const = false;
    static constexpr bool is_noexcept = true;

    using type = R(Args...) noexcept;
    using result_type = R;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const noexcept>
{
    static constexpr bool is_const = true;
    static constexpr bool is_noexcept = true;

    using type = R(Args...) const noexcept;
    using result_type = R;
};

#endif

//-----------------------------------------------------------------------------
// Function object

template <typename F, typename... Args>
struct function_type
    : public function_type<decltype(&decay_t<F>::operator()), add_pointer_t<decay_t<F>>, Args...>
{
};

//-----------------------------------------------------------------------------
// R(Args...)

template <typename R, typename... Args>
struct function_type<R(Args...)>
    : public function_traits<R(Args...)>
{
};

template <typename R, typename... Args>
struct function_type<R(Args...) &, Args...>
    : function_traits<R(Args...)>
{
};

template <typename R, typename... Args>
struct function_type<R(Args...) &&, Args...>
    : function_traits<R(Args...)>
{
};

template <typename R, typename... Args>
struct function_type<R(*)(Args...), Args...>
    : function_traits<R(Args...)>
{
};

template <typename R, typename Class, typename... Args>
struct function_type<R(Class::*)(Args...), Class *, Args...>
    : function_traits<R(Args...)>
{
};

template <typename R, typename Class, typename... Args>
struct function_type<R(Class::*)(Args...) &, Class *, Args...>
    : function_traits<R(Args...)>
{
};

template <typename R, typename Class, typename... Args>
struct function_type<R(Class::*)(Args...) &&, Class *, Args...>
    : function_traits<R(Args...)>
{
};

template <typename R, typename... Args>
struct function_type<R(&)(Args...), Args...>
    : function_traits<R(Args...)>
{
};

template <typename R, typename... Args>
struct function_type<R(&&)(Args...), Args...>
    : function_traits<R(Args...)>
{
};

//-----------------------------------------------------------------------------
// R(Args...) const

template <typename R, typename... Args>
struct function_type<R(Args...) const, Args...>
    : public function_traits<R(Args...) const>
{
};

template <typename R, typename... Args>
struct function_type<R(Args...) const &, Args...>
    : function_traits<R(Args...) const>
{
};

template <typename R, typename... Args>
struct function_type<R(Args...) const &&, Args...>
    : function_traits<R(Args...) const>
{
};

template <typename R, typename Class, typename... Args>
struct function_type<R(Class::*)(Args...) const, Class *, Args...>
    : function_traits<R(Args...) const>
{
};

template <typename R, typename Class, typename... Args>
struct function_type<R(Class::*)(Args...) const, const Class *, Args...>
    : function_traits<R(Args...) const>
{
};

template <typename R, typename Class, typename... Args>
struct function_type<R(Class::*)(Args...) const &, Class *, Args...>
    : function_traits<R(Args...) const>
{
};

template <typename R, typename Class, typename... Args>
struct function_type<R(Class::*)(Args...) const &, const Class *, Args...>
    : function_traits<R(Args...) const>
{
};

template <typename R, typename Class, typename... Args>
struct function_type<R(Class::*)(Args...) const &&, Class *, Args...>
    : function_traits<R(Args...) const>
{
};

template <typename R, typename Class, typename... Args>
struct function_type<R(Class::*)(Args...) const &&, const Class *, Args...>
    : function_traits<R(Args...) const>
{
};

//-----------------------------------------------------------------------------
// R(Args...) noexcept

#if __cpp_noexcept_function_type

template <typename R, typename... Args>
struct function_type<R(Args...) noexcept, Args...>
    : function_traits<R(Args...) noexcept>
{
};

template <typename R, typename... Args>
struct function_type<R(Args...) & noexcept, Args...>
    : function_traits<R(Args...) noexcept>
{
};

template <typename R, typename... Args>
struct function_type<R(Args...) && noexcept, Args...>
    : function_traits<R(Args...) noexcept>
{
};

template <typename R, typename... Args>
struct function_type<R(*)(Args...) noexcept, Args...>
    : function_traits<R(Args...) noexcept>
{
};

template <typename R, typename... Args>
struct function_type<R(&)(Args...) noexcept, Args...>
    : function_traits<R(Args...) noexcept>
{
};

template <typename R, typename... Args>
struct function_type<R(&&)(Args...) noexcept, Args...>
    : function_traits<R(Args...) noexcept>
{
};

template <typename R, typename Class, typename... Args>
struct function_type<R(Class::*)(Args...) noexcept, Class *, Args...>
    : function_traits<R(Args...) noexcept>
{
};

template <typename R, typename Class, typename... Args>
struct function_type<R(Class::*)(Args...) & noexcept, Class *, Args...>
    : function_traits<R(Args...) noexcept>
{
};

template <typename R, typename Class, typename... Args>
struct function_type<R(Class::*)(Args...) && noexcept, Class *, Args...>
    : function_traits<R(Args...) noexcept>
{
};

#endif

//-----------------------------------------------------------------------------
// R(Args...) const noexcept

#if __cpp_noexcept_function_type

template <typename R, typename... Args>
struct function_type<R(Args...) const noexcept, Args...>
    : function_traits<R(Args...) const noexcept>
{
};

template <typename R, typename... Args>
struct function_type<R(Args...) const & noexcept, Args...>
    : function_traits<R(Args...) const noexcept>
{
};

template <typename R, typename... Args>
struct function_type<R(Args...) const && noexcept, Args...>
    : function_traits<R(Args...) const noexcept>
{
};

template <typename R, typename Class, typename... Args>
struct function_type<R(Class::*)(Args...) const noexcept, Class *, Args...>
    : function_traits<R(Args...) const noexcept>
{
};

template <typename R, typename Class, typename... Args>
struct function_type<R(Class::*)(Args...) const noexcept, const Class *, Args...>
    : function_traits<R(Args...) const noexcept>
{
};

template <typename R, typename Class, typename... Args>
struct function_type<R(Class::*)(Args...) const & noexcept, Class *, Args...>
    : function_traits<R(Args...) const noexcept>
{
};

template <typename R, typename Class, typename... Args>
struct function_type<R(Class::*)(Args...) const & noexcept, const Class *, Args...>
    : function_traits<R(Args...) const noexcept>
{
};

template <typename R, typename Class, typename... Args>
struct function_type<R(Class::*)(Args...) const && noexcept, Class *, Args...>
    : function_traits<R(Args...) const noexcept>
{
};

template <typename R, typename Class, typename... Args>
struct function_type<R(Class::*)(Args...) const && noexcept, const Class *, Args...>
    : function_traits<R(Args...) const noexcept>
{
};

#endif

//-----------------------------------------------------------------------------
// Convenience

template <typename F, typename... Args>
using function_type_t = typename function_type<F, Args...>::type;

template <typename F, typename... Args>
using result_type_t = typename function_type<F, Args...>::result_type;

template <typename F, typename... Args>
struct is_noexcept
    : public std::integral_constant<bool, function_type<F, Args...>::is_noexcept>
{
};

template <typename F, typename... Args>
struct is_const
    : public std::integral_constant<bool, function_type<F, Args...>::is_const>
{
};

} // namespace detail
} // namespace v1
} // namespace lean

#endif // LEAN_DETAIL_FUNCTION_TYPE_HPP
