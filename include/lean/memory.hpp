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

} // namespace v1

using v1::construct_at;
using v1::destroy_at;

} // namespace lean

#endif // LEAN_MEMORY_HPP
