#ifndef LEAN_DETAIL_FUNCTION_TRAITS_HPP
#define LEAN_DETAIL_FUNCTION_TRAITS_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

namespace lean
{
namespace v1
{
namespace detail
{

template <typename>
struct function_traits;

template <typename R, typename... Args>
struct function_traits<R(Args...)>
{
    using remove_const = R(Args...);
    using remove_volatile = R(Args...);
    using remove_reference = R(Args...);
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const>
{
    using remove_const = R(Args...);
    using remove_volatile = R(Args...) const;
    using remove_reference = R(Args...) const;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const &>
{
    using remove_const = R(Args...) &;
    using remove_volatile = R(Args...) const &;
    using remove_reference = R(Args...) const;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const &&>
{
    using remove_const = R(Args...) &&;
    using remove_volatile = R(Args...) const &&;
    using remove_reference = R(Args...) const;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const volatile>
{
    using remove_const = R(Args...) volatile;
    using remove_volatile = R(Args...) const;
    using remove_reference = R(Args...) const volatile;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const volatile &>
{
    using remove_const = R(Args...) volatile &;
    using remove_volatile = R(Args...) const &;
    using remove_reference = R(Args...) const volatile;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const volatile &&>
{
    using remove_const = R(Args...) volatile &&;
    using remove_volatile = R(Args...) const &&;
    using remove_reference = R(Args...) const volatile;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) volatile>
{
    using remove_const = R(Args...) volatile;
    using remove_volatile = R(Args...);
    using remove_reference = R(Args...) volatile;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) volatile &>
{
    using remove_const = R(Args...) volatile &;
    using remove_volatile = R(Args...) &;
    using remove_reference = R(Args...) volatile;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) volatile &&>
{
    using remove_const = R(Args...) volatile &&;
    using remove_volatile = R(Args...) &&;
    using remove_reference = R(Args...) volatile;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) &>
{
    using remove_const = R(Args...) &;
    using remove_volatile = R(Args...) &;
    using remove_reference = R(Args...);
};

template <typename R, typename... Args>
struct function_traits<R(Args...) &&>
{
    using remove_const = R(Args...) &&;
    using remove_volatile = R(Args...) &&;
    using remove_reference = R(Args...);
};

#if __cpp_noexcept_function_type >= 201510L

template <typename R, typename... Args>
struct function_traits<R(Args...) noexcept>
{
    using remove_const = R(Args...) noexcept;
    using remove_volatile = R(Args...) noexcept;
    using remove_reference = R(Args...) noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const noexcept>
{
    using remove_const = R(Args...) noexcept;
    using remove_volatile = R(Args...) const noexcept;
    using remove_reference = R(Args...) const noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const & noexcept>
{
    using remove_const = R(Args...) & noexcept;
    using remove_volatile = R(Args...) const & noexcept;
    using remove_reference = R(Args...) const noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const && noexcept>
{
    using remove_const = R(Args...) && noexcept;
    using remove_volatile = R(Args...) const && noexcept;
    using remove_reference = R(Args...) const noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const volatile noexcept>
{
    using remove_const = R(Args...) volatile noexcept;
    using remove_volatile = R(Args...) const noexcept;
    using remove_reference = R(Args...) const volatile noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const volatile & noexcept>
{
    using remove_const = R(Args...) volatile & noexcept;
    using remove_volatile = R(Args...) const & noexcept;
    using remove_reference = R(Args...) const volatile noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const volatile && noexcept>
{
    using remove_const = R(Args...) volatile && noexcept;
    using remove_volatile = R(Args...) const && noexcept;
    using remove_reference = R(Args...) const volatile noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) volatile noexcept>
{
    using remove_const = R(Args...) volatile noexcept;
    using remove_volatile = R(Args...) noexcept;
    using remove_reference = R(Args...) volatile noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) volatile & noexcept>
{
    using remove_const = R(Args...) volatile & noexcept;
    using remove_volatile = R(Args...) & noexcept;
    using remove_reference = R(Args...) volatile noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) volatile && noexcept>
{
    using remove_const = R(Args...) volatile && noexcept;
    using remove_volatile = R(Args...) && noexcept;
    using remove_reference = R(Args...) volatile noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) & noexcept>
{
    using remove_const = R(Args...) & noexcept;
    using remove_volatile = R(Args...) & noexcept;
    using remove_reference = R(Args...) noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) && noexcept>
{
    using remove_const = R(Args...) && noexcept;
    using remove_volatile = R(Args...) && noexcept;
    using remove_reference = R(Args...) noexcept;
};

#endif

} // namespace detail
} // namespace v1
} // namespace lean

#endif // LEAN_DETAIL_FUNCTION_TRAITS_HPP
