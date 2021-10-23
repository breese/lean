#ifndef LEAN_MEMORY_HPP
#define LEAN_MEMORY_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <new>
#include <memory>
#include <lean/detail/config.hpp>
#include <lean/detail/type_traits.hpp>
#include <lean/pack.hpp>

namespace lean
{
namespace v1
{

//-----------------------------------------------------------------------------
// construct_at

#if __cpp_lib_constexpr_dynamic_alloc >= 201811L

using std::construct_at;

#else

template <typename T, typename... Args>
T* construct_at(T* ptr, Args&&... args) noexcept(std::is_nothrow_constructible<T, Args...>())
{
    return ::new (const_cast<void*>(static_cast<const volatile void*>(ptr))) T{ std::forward<Args>(args)... };
}

#endif

//-----------------------------------------------------------------------------
// destroy_at

#if __cpp_lib_raw_memory_algorithms >= 201606L

using std::destroy_at;

#else

template <typename T>
void destroy_at(T* ptr)
{
    ptr->~T();
}

#endif

//-----------------------------------------------------------------------------
// inplace_storage

namespace detail
{

template <typename In, typename T>
struct is_inplace_compatible
    : public std::integral_constant<bool,
                                    (sizeof(In) >= sizeof(T)) && (alignof(In) % alignof(T) == 0)>
{
};

} // namespace detail

template <typename T>
struct inplace_storage {
    using value_type = remove_const_t<T>;

    constexpr inplace_storage() noexcept = default;

    template <typename Arg0,
              typename... Args,
              typename = enable_if_t<!std::is_same<inplace_storage, remove_cvref_t<Arg0>>::value>>
    explicit constexpr inplace_storage(Arg0&& arg0, Args&&... args)
        : member(std::forward<Arg0>(arg0), std::forward<Args>(args)...)
    {
    }

    // Accessors

    template <typename R = value_type>
    LEAN_CONSTEXPR_CXX14
    auto data() noexcept
        -> enable_if_t<detail::is_inplace_compatible<value_type, R>::value,
                       add_pointer_t<R>>
    {
        return reinterpret_cast<add_pointer_t<R>>(&member.value);
    }

    template <typename R = value_type>
    constexpr auto data() const noexcept
        -> enable_if_t<detail::is_inplace_compatible<value_type, R>::value,
                       add_pointer_t<add_const_t<R>>>
    {
        return reinterpret_cast<add_pointer_t<add_const_t<R>>>(&member.value);
    }

private:
    union member
    {
        constexpr member() noexcept = default;
        constexpr member(const member&) noexcept = delete;
        constexpr member(member&&) noexcept = delete;

        template <typename Arg0,
                  typename... Args,
                  typename = enable_if_t<!std::is_same<member, remove_cvref_t<Arg0>>::value>>
        explicit constexpr member(Arg0&& arg0, Args&&... args)
            : value(std::forward<Arg0>(arg0), std::forward<Args>(args)...)
        {
        }

        // Dummy to prevent value from being default-initialized
        unsigned char dummy {};
        value_type value;
    } member;
};

template <typename... Types>
struct inplace_union {
    template <typename Lhs, typename Rhs>
    struct greater_sizeof : public type_greater_with<type_sizeof, Lhs, Rhs> {};

    using value_type = pack_fold<pack<Types...>, greater_sizeof>;

    constexpr inplace_union() noexcept = default;

    template <typename Arg0,
              typename... Args,
              typename = enable_if_t<!std::is_same<inplace_union, remove_cvref_t<Arg0>>::value>>
    explicit constexpr inplace_union(Arg0&& arg0, Args&&... args)
        : member(std::forward<Arg0>(arg0), std::forward<Args>(args)...)
    {
    }

    // Accessors

    template <typename R>
    LEAN_CONSTEXPR_CXX14
    auto data() noexcept
        -> enable_if_t<detail::is_inplace_compatible<value_type, R>::value &&
                       pack_contains<pack<Types...>, R>::value,
                       add_pointer_t<R>>
    {
        return member.template data<R>();
    }

    template <typename R>
    constexpr auto data() const noexcept
        -> enable_if_t<detail::is_inplace_compatible<value_type, R>::value &&
                       pack_contains<pack<Types...>, R>::value,
                       add_pointer_t<add_const_t<R>>>
    {
        return member.template data<R>();
    }

private:
    inplace_storage<value_type> member;
};

} // namespace v1

//-----------------------------------------------------------------------------

using v1::construct_at;
using v1::destroy_at;
using v1::inplace_storage;
using v1::inplace_union;

} // namespace lean

#endif // LEAN_MEMORY_HPP
