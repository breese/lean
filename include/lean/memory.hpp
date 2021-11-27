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

#include <cstddef> // std::max_align_t
#include <new>
#include <memory>
#include <lean/detail/config.hpp>
#include <lean/detail/type_traits.hpp>

namespace lean
{
namespace v1
{

//-----------------------------------------------------------------------------
// constexpr addressof [P0304]

#if __cpp_lib_addressof_constexpr >= 201603L

using std::addressof;

#else

namespace impl
{

template <typename T, typename = void>
struct is_addressof_overloaded : public std::false_type {};

template <typename T>
struct is_addressof_overloaded<T,
                               void_t<decltype(std::declval<T&>().operator&())>>
    : public std::true_type
{
};

} // namespace impl

template <typename T,
          enable_if_t<!impl::is_addressof_overloaded<T>::value, int> = 0>
constexpr T* addressof(T& value)
{
    return &value;
}

template <typename T,
          enable_if_t<impl::is_addressof_overloaded<T>::value, int> = 0>
T* addressof(T& value)
{
    return std::addressof(value);
}

#endif

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

template <std::size_t Len, std::size_t Align, typename U>
struct is_inplace_storage_compatible
    : std::integral_constant<bool,
                             (Len >= sizeof(U)) && (Align % alignof(U) == 0)>
{
};

template <typename T, typename U>
struct is_inplace_value_compatible
    : is_inplace_storage_compatible<sizeof(T), alignof(T), U>
{
};

} // namespace detail

template <std::size_t Len, std::size_t Align = alignof(std::max_align_t)>
struct inplace_storage {
    using element_type = unsigned char;
    using value_type = element_type[Len];

    constexpr inplace_storage() noexcept = default;

    // Accessors

    template <typename R>
    LEAN_CONSTEXPR_CXX14
    auto data() noexcept
        -> enable_if_t<detail::is_inplace_storage_compatible<Len, Align, R>::value,
                       add_pointer_t<R>>
    {
        return reinterpret_cast<add_pointer_t<R>>(&member.value);
    }

    template <typename R>
    constexpr auto data() const noexcept
        -> enable_if_t<detail::is_inplace_storage_compatible<Len, Align, R>::value,
                       add_pointer_t<add_const_t<R>>>
    {
        return reinterpret_cast<add_pointer_t<add_const_t<R>>>(&member.value);
    }

private:
    alignas (Align) struct member
    {
        constexpr member() noexcept = default;
        constexpr member(const member&) noexcept = delete;
        constexpr member(member&&) noexcept = delete;

        template <typename... Args,
                  typename = enable_if_t<!std::is_same<member, remove_cvref_t<type_front_t<Args...>>>::value>>
        explicit constexpr member(Args&&... args)
            : value(std::forward<Args>(args)...)
        {
        }

        element_type value[Len];
    } member;
};

//-----------------------------------------------------------------------------
// inplace_value

template <typename T>
struct inplace_value {
    using value_type = remove_const_t<T>;

    constexpr inplace_value() noexcept = default;

    template <typename... Args,
              typename = enable_if_t<!std::is_same<inplace_value, remove_cvref_t<type_front_t<Args...>>>::value>>
    explicit constexpr inplace_value(Args&&... args)
        : member(std::forward<Args>(args)...)
    {
    }

    // Accessors

    template <typename R = value_type>
    LEAN_CONSTEXPR_CXX14
    auto data() noexcept
        -> enable_if_t<detail::is_inplace_value_compatible<value_type, R>::value,
                       add_pointer_t<R>>
    {
        return reinterpret_cast<add_pointer_t<R>>(&member.value);
    }

    template <typename R = value_type>
    constexpr auto data() const noexcept
        -> enable_if_t<detail::is_inplace_value_compatible<value_type, R>::value,
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

        template <typename... Args,
                  typename = enable_if_t<!std::is_same<member, remove_cvref_t<type_front_t<Args...>>>::value>>
        explicit constexpr member(Args&&... args)
            : value(std::forward<Args>(args)...)
        {
        }

        // Dummy to prevent value from being default-initialized
        unsigned char dummy {};
        value_type value;
    } member;
};

//-----------------------------------------------------------------------------
// inplace_union

template <typename... Types>
struct inplace_union {
    using value_type = type_max_with_t<type_sizeof, Types...>;

    constexpr inplace_union() noexcept = default;

    template <typename... Args,
              typename = enable_if_t<!std::is_same<inplace_union, remove_cvref_t<type_front_t<Args...>>>::value>>
    explicit constexpr inplace_union(Args&&... args)
        : member(std::forward<Args>(args)...)
    {
    }

    // Accessors

    template <typename R>
    LEAN_CONSTEXPR_CXX14
    auto data() noexcept
        -> enable_if_t<detail::is_inplace_value_compatible<value_type, R>::value &&
                       type_contains<R, Types...>::value,
                       add_pointer_t<R>>
    {
        return member.template data<R>();
    }

    template <typename R>
    constexpr auto data() const noexcept
        -> enable_if_t<detail::is_inplace_value_compatible<value_type, R>::value &&
                       type_contains<R, Types...>::value,
                       add_pointer_t<add_const_t<R>>>
    {
        return member.template data<R>();
    }

private:
    inplace_value<value_type> member;
};

} // namespace v1

//-----------------------------------------------------------------------------

using v1::construct_at;
using v1::destroy_at;
using v1::inplace_storage;
using v1::inplace_value;
using v1::inplace_union;

} // namespace lean

#endif // LEAN_MEMORY_HPP
