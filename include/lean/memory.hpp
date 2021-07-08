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

#if __cplusplus >= LEAN_CXX17
# define LEAN_WITH_STD_LAUNDER 1
#endif

#if __cplusplus >= LEAN_CXX20
# define LEAN_WITH_STD_CONSTRUCT_AT 1
#endif

#if __cpp_lib_raw_memory_algorithms >= 201606L
# define LEAN_WITH_STD_DESTROY_AT 1
#endif

#if __cpp_lib_constexpr_dynamic_alloc >= 201811L
# define LEAN_CONSTEXPR_ALLOCATOR constexpr
#else
# define LEAN_CONSTEXPR_ALLOCATOR
#endif

namespace lean
{

//-----------------------------------------------------------------------------

namespace detail
{

template <typename T>
constexpr T* launder(T *ptr) noexcept
{
#if LEAN_WITH_STD_LAUNDER
    return std::launder(ptr);
#else
    return ptr;
#endif
}

template <typename Allocator, typename... Args>
LEAN_CONSTEXPR_ALLOCATOR
void construct_at(Allocator& allocator,
                  typename Allocator::pointer location,
                  Args&&... args)
{
    std::allocator_traits<Allocator>::construct(allocator, location, std::forward<Args>(args)...);
}

template <typename Allocator>
LEAN_CONSTEXPR_ALLOCATOR
void destroy_at(Allocator& allocator,
                typename Allocator::pointer location)
{
    std::allocator_traits<Allocator>::destroy(allocator, location);
}

} // namespace detail

//-----------------------------------------------------------------------------

namespace v1
{

#if LEAN_WITH_STD_CONSTRUCT_AT

using std::construct_at;

#else

template <typename T, typename... Args>
LEAN_CONSTEXPR_ALLOCATOR
T* construct_at(T* ptr, Args&&... args)
{
    std::allocator<T> allocator;
    lean::detail::construct_at(allocator, ptr, std::forward<Args>(args)...);
    return lean::detail::launder(ptr);
}

#endif

#if LEAN_WITH_STD_DESTROY_AT

using std::destroy_at;

#else

template <typename T>
LEAN_CONSTEXPR_ALLOCATOR
void destroy_at(T* ptr)
{
    std::allocator<T> allocator;
    lean::detail::destroy_at(allocator, ptr);
}

#endif

} // namespace v1
} // namespace lean

#endif // LEAN_MEMORY_HPP
