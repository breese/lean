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

#include <lean/detail/type_traits.hpp>

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
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::false_type;
    using is_volatile = std::false_type;
    using is_lvalue_reference = std::false_type;
    using is_rvalue_reference = std::false_type;

    using remove_const = R(Args...);
    using remove_volatile = R(Args...);
    using remove_reference = R(Args...);
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::true_type;
    using is_volatile = std::false_type;
    using is_lvalue_reference = std::false_type;
    using is_rvalue_reference = std::false_type;

    using remove_const = R(Args...);
    using remove_volatile = R(Args...) const;
    using remove_reference = R(Args...) const;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const &>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::true_type;
    using is_volatile = std::false_type;
    using is_lvalue_reference = std::true_type;
    using is_rvalue_reference = std::false_type;

    using remove_const = R(Args...) &;
    using remove_volatile = R(Args...) const &;
    using remove_reference = R(Args...) const;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const &&>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::true_type;
    using is_volatile = std::false_type;
    using is_lvalue_reference = std::false_type;
    using is_rvalue_reference = std::true_type;

    using remove_const = R(Args...) &&;
    using remove_volatile = R(Args...) const &&;
    using remove_reference = R(Args...) const;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const volatile>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::true_type;
    using is_volatile = std::true_type;
    using is_lvalue_reference = std::false_type;
    using is_rvalue_reference = std::false_type;

    using remove_const = R(Args...) volatile;
    using remove_volatile = R(Args...) const;
    using remove_reference = R(Args...) const volatile;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const volatile &>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::true_type;
    using is_volatile = std::true_type;
    using is_lvalue_reference = std::true_type;
    using is_rvalue_reference = std::false_type;

    using remove_const = R(Args...) volatile &;
    using remove_volatile = R(Args...) const &;
    using remove_reference = R(Args...) const volatile;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const volatile &&>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::true_type;
    using is_volatile = std::true_type;
    using is_lvalue_reference = std::false_type;
    using is_rvalue_reference = std::true_type;

    using remove_const = R(Args...) volatile &&;
    using remove_volatile = R(Args...) const &&;
    using remove_reference = R(Args...) const volatile;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) volatile>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::false_type;
    using is_volatile = std::true_type;
    using is_lvalue_reference = std::false_type;
    using is_rvalue_reference = std::false_type;

    using remove_const = R(Args...) volatile;
    using remove_volatile = R(Args...);
    using remove_reference = R(Args...) volatile;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) volatile &>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::false_type;
    using is_volatile = std::true_type;
    using is_lvalue_reference = std::true_type;
    using is_rvalue_reference = std::false_type;

    using remove_const = R(Args...) volatile &;
    using remove_volatile = R(Args...) &;
    using remove_reference = R(Args...) volatile;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) volatile &&>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::false_type;
    using is_volatile = std::true_type;
    using is_lvalue_reference = std::false_type;
    using is_rvalue_reference = std::true_type;

    using remove_const = R(Args...) volatile &&;
    using remove_volatile = R(Args...) &&;
    using remove_reference = R(Args...) volatile;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) &>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::false_type;
    using is_volatile = std::false_type;
    using is_lvalue_reference = std::true_type;
    using is_rvalue_reference = std::false_type;

    using remove_const = R(Args...) &;
    using remove_volatile = R(Args...) &;
    using remove_reference = R(Args...);
};

template <typename R, typename... Args>
struct function_traits<R(Args...) &&>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::false_type;
    using is_volatile = std::false_type;
    using is_lvalue_reference = std::false_type;
    using is_rvalue_reference = std::true_type;

    using remove_const = R(Args...) &&;
    using remove_volatile = R(Args...) &&;
    using remove_reference = R(Args...);
};

#if __cpp_noexcept_function_type >= 201510L

template <typename R, typename... Args>
struct function_traits<R(Args...) noexcept>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::false_type;
    using is_volatile = std::false_type;
    using is_lvalue_reference = std::false_type;
    using is_rvalue_reference = std::false_type;

    using remove_const = R(Args...) noexcept;
    using remove_volatile = R(Args...) noexcept;
    using remove_reference = R(Args...) noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const noexcept>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::true_type;
    using is_volatile = std::false_type;
    using is_lvalue_reference = std::false_type;
    using is_rvalue_reference = std::false_type;

    using remove_const = R(Args...) noexcept;
    using remove_volatile = R(Args...) const noexcept;
    using remove_reference = R(Args...) const noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const & noexcept>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::true_type;
    using is_volatile = std::false_type;
    using is_lvalue_reference = std::true_type;
    using is_rvalue_reference = std::false_type;

    using remove_const = R(Args...) & noexcept;
    using remove_volatile = R(Args...) const & noexcept;
    using remove_reference = R(Args...) const noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const && noexcept>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::true_type;
    using is_volatile = std::false_type;
    using is_lvalue_reference = std::false_type;
    using is_rvalue_reference = std::true_type;

    using remove_const = R(Args...) && noexcept;
    using remove_volatile = R(Args...) const && noexcept;
    using remove_reference = R(Args...) const noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const volatile noexcept>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::true_type;
    using is_volatile = std::true_type;
    using is_lvalue_reference = std::false_type;
    using is_rvalue_reference = std::false_type;

    using remove_const = R(Args...) volatile noexcept;
    using remove_volatile = R(Args...) const noexcept;
    using remove_reference = R(Args...) const volatile noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const volatile & noexcept>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::true_type;
    using is_volatile = std::true_type;
    using is_lvalue_reference = std::true_type;
    using is_rvalue_reference = std::false_type;

    using remove_const = R(Args...) volatile & noexcept;
    using remove_volatile = R(Args...) const & noexcept;
    using remove_reference = R(Args...) const volatile noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) const volatile && noexcept>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::true_type;
    using is_volatile = std::true_type;
    using is_lvalue_reference = std::false_type;
    using is_rvalue_reference = std::true_type;

    using remove_const = R(Args...) volatile && noexcept;
    using remove_volatile = R(Args...) const && noexcept;
    using remove_reference = R(Args...) const volatile noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) volatile noexcept>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::false_type;
    using is_volatile = std::true_type;
    using is_lvalue_reference = std::false_type;
    using is_rvalue_reference = std::false_type;

    using remove_const = R(Args...) volatile noexcept;
    using remove_volatile = R(Args...) noexcept;
    using remove_reference = R(Args...) volatile noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) volatile & noexcept>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::false_type;
    using is_volatile = std::true_type;
    using is_lvalue_reference = std::true_type;
    using is_rvalue_reference = std::false_type;

    using remove_const = R(Args...) volatile & noexcept;
    using remove_volatile = R(Args...) & noexcept;
    using remove_reference = R(Args...) volatile noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) volatile && noexcept>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::false_type;
    using is_volatile = std::true_type;
    using is_lvalue_reference = std::false_type;
    using is_rvalue_reference = std::true_type;

    using remove_const = R(Args...) volatile && noexcept;
    using remove_volatile = R(Args...) && noexcept;
    using remove_reference = R(Args...) volatile noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) & noexcept>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::false_type;
    using is_volatile = std::false_type;
    using is_lvalue_reference = std::true_type;
    using is_rvalue_reference = std::false_type;

    using remove_const = R(Args...) & noexcept;
    using remove_volatile = R(Args...) & noexcept;
    using remove_reference = R(Args...) noexcept;
};

template <typename R, typename... Args>
struct function_traits<R(Args...) && noexcept>
{
    using return_type = R;
    using arguments = proto<Args...>;

    using is_const = std::false_type;
    using is_volatile = std::false_type;
    using is_lvalue_reference = std::false_type;
    using is_rvalue_reference = std::true_type;

    using remove_const = R(Args...) && noexcept;
    using remove_volatile = R(Args...) && noexcept;
    using remove_reference = R(Args...) noexcept;
};

#endif

} // namespace detail
} // namespace v1
} // namespace lean

#endif // LEAN_DETAIL_FUNCTION_TRAITS_HPP
