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
// inplace_traits

namespace detail
{

template <typename In, typename T>
struct is_inplace_compatible
    : public std::integral_constant<bool,
                                    (sizeof(In) >= sizeof(T)) && (alignof(In) % alignof(T) == 0)>
{
};

} // namespace detail

template <typename In, typename T, typename... Args>
struct is_inplace_constructible
    : public std::integral_constant<bool,
                                    std::is_constructible<T, Args...>::value &&
                                    detail::is_inplace_compatible<In, T>::value>
{
};

template <typename In, typename T>
struct is_inplace_destructible
    : public std::integral_constant<bool,
                                    std::is_destructible<T>::value &&
                                    detail::is_inplace_compatible<In, T>::value>
{
};

template <typename T>
struct inplace_traits;

//-----------------------------------------------------------------------------
// inplace_storage

template <typename T>
struct inplace_storage {
    using value_type = remove_const_t<T>;

    constexpr inplace_storage() noexcept {};

    template <typename R = value_type>
    constexpr R* data() noexcept
    {
        return reinterpret_cast<R*>(&member.value);
    }

    template <typename R = value_type>
    constexpr const R* data() const noexcept
    {
        return reinterpret_cast<const R*>(&member.value);
    }

private:
    inplace_storage(const inplace_storage&) = delete;
    inplace_storage(inplace_storage&&) = delete;

    // Accessors

    union member {
        constexpr member() noexcept = default;
        constexpr member(const member&) noexcept = default;
        constexpr member(member&&) noexcept = default;

        enum nullable { null } nothing = null;
        value_type value;
    } member;
};

template <typename T>
struct inplace_traits<inplace_storage<T>>
{
    using storage_type = inplace_storage<T>;
    using value_type = typename storage_type::value_type;
    using pointer = add_pointer_t<value_type>;
    using const_pointer = typename std::pointer_traits<pointer>::template rebind<const value_type>;

    // Creates inplace value with given arguments.

    template <typename... Args>
    static constexpr auto construct(storage_type* self,
                                    Args&&... args)
        noexcept(std::is_nothrow_constructible<T, Args...>() &&
                 std::is_nothrow_move_constructible<T>())
        -> enable_if_t<(sizeof...(Args) == 0) ||
                       !std::is_same<storage_type, remove_cvref_t<pack_front<Args...>>>::value>
    {
        // Cannot use constexpr construct_at() before C++20
        *const_cast<add_pointer_t<remove_const_t<T>>>(self->data()) = T(std::forward<Args>(args)...);
    }

    // Creates inplace value by copying.

    template <typename U>
    static constexpr void construct(storage_type* self,
                                    const inplace_storage<U>& other)
        noexcept(std::is_nothrow_copy_constructible<T>())
    {
        construct(self, *other.data());
    }

    // Creates inplace value by moving.

    template <typename U>
    static constexpr void construct(storage_type* self,
                                    inplace_storage<U>&& other)
        noexcept(std::is_nothrow_move_constructible<T>())
    {
        construct(self, std::move(*other.data()));
    }

    static constexpr void destroy(storage_type* self) noexcept(std::is_nothrow_destructible<T>())
    {
        self->data()->~T();
    }
};

} // namespace v1

//-----------------------------------------------------------------------------

using v1::construct_at;
using v1::destroy_at;
using v1::inplace_storage;
using v1::inplace_traits;

} // namespace lean

#endif // LEAN_MEMORY_HPP
