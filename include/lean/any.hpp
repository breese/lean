#ifndef LEAN_ANY_HPP
#define LEAN_ANY_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <lean/memory.hpp>
#include <lean/utility.hpp>
#include <lean/type_traits.hpp>

namespace lean
{
namespace v1
{

//! @brief Move-only type-safe variable for containing value of any type.
//!
//! No support for type()
//! No support for initializer_list

class unique_any
{
public:
    //! @brief Creates empty object.

    constexpr unique_any() noexcept {};

    //! @brief Creates object by moving.
    //!
    //! @post other is in a moved-from state.

    unique_any(unique_any&& other) noexcept
    {
        swap(other);
    }

    //! @brief Creates object with given value.

    template <typename T,
              typename DecayT = decay_t<T>,
              typename = enable_if_t<!std::is_same<unique_any, DecayT>::value>>
    unique_any(T&& value)
        : interface(&table<DecayT>::instance())
    {
        overload<DecayT>::create(storage, std::forward<T>(value));
    }

#if LEAN_HAS_IN_PLACE_TYPE

    //! @brief Creates object with in-place construction of value.
    template <typename T,
              typename... Args,
              typename DecayT = decay_t<T>,
              typename = enable_if_t<std::is_constructible<DecayT, Args...>::value>>
    explicit unique_any(lean::in_place_type_t<T>, Args&&... args)
        : interface(&table<DecayT>::instance())
    {
        overload<DecayT>::create(storage, std::forward<Args>(args)...);
    }

#endif

    //! @brief Destroys object.

    ~unique_any()
    {
        if (has_value())
        {
            interface->destroy(storage);
        }
    }

    //! @brief Recreates object by moving.

    unique_any& operator=(unique_any&& other) noexcept
    {
        unique_any(std::move(other)).swap(*this);
        return *this;
    }

    //! @brief Assigns given value of deduced type.

    template <typename T,
              typename DecayT = decay_t<T>,
              typename = enable_if_t<!std::is_same<unique_any, DecayT>::value &&
                                     std::is_copy_constructible<DecayT>::value>>
    unique_any& operator=(T&& value)
    {
        unique_any(std::forward<T>(value)).swap(*this);
        return *this;
    }

    //! @brief Checks if object has a stored value.

    bool has_value() const noexcept
    {
        return static_cast<bool>(interface);
    }

    //! @brief Checks if stored value has type T.
    //!
    //! holds<void>() checks if the object has no value.

    template <typename T>
    bool holds() const noexcept
    {
        return overload<decay_t<T>>::holds(*this);
    }

    //! @brief Recreates object

    template <typename T,
              typename... Args,
              typename DecayT = decay_t<T>>
    DecayT& emplace(Args&&... args)
    {
        unique_any(T{ std::forward<Args>(args)... }).swap(*this);
        return *overload<DecayT>::cast(storage);
    }

    //! @brief Resets object to default constructed state.

    void reset() noexcept
    {
        unique_any().swap(*this);
    }

    //! @brief Exchanges typed values.

    unique_any& swap(unique_any& other) noexcept
    {
        std::swap(interface, other.interface);
        std::swap(storage, other.storage);
        return *this;
    }

protected:
    template <typename T>
    friend const T * any_cast(const unique_any *) noexcept;

    template <typename T>
    friend T * any_cast(unique_any *) noexcept;

    union storage_type
    {
        constexpr storage_type() noexcept = default;
        // storage is trivially moveable
        storage_type(storage_type&&) noexcept = default;
        storage_type& operator=(storage_type&&) noexcept = default;

        // Allocated alternative
        void *pointer = nullptr;

        // In-place alternative
        alignas(decltype(pointer)) unsigned char buffer[sizeof(pointer)];
    } storage;

    // Type-erased interface points to dispatch table for overload<T>
    struct interface
    {
        void (*destroy)(storage_type&);
    }  const *interface = nullptr;

    // Allocated storage
    template <typename T, typename = void>
    struct overload
    {
        static T* cast(storage_type& self) noexcept
        {
            return static_cast<T*>(self.pointer);
        }

        static const T* cast(const storage_type& self) noexcept
        {
            return static_cast<const T*>(self.pointer);
        }

        template <typename... Args>
        static void create(storage_type& self, Args&&... args) noexcept(std::is_nothrow_constructible<T, Args...>::value)
        {
            self.pointer = new (std::nothrow_t{}) T{ std::forward<Args>(args)... };
        }

        static void destroy(storage_type& self)
        {
            delete cast(self);
        }

        static bool holds(const unique_any& self) noexcept
        {
            return self.interface == &table<T>::instance();
        }
    };

    // In-place storage for small-object optimization
    template <typename T>
    struct overload<T,
                    enable_if_t<(sizeof(T) <= sizeof(storage.buffer)) && is_trivially_move_constructible<T>::value>>
    {
        static T* cast(storage_type& self) noexcept
        {
            return &reinterpret_cast<T&>(self.buffer);
        }

        static const T* cast(const storage_type& self) noexcept
        {
            return &reinterpret_cast<const T&>(self.buffer);
        }

        template <typename... Args>
        static void create(storage_type& self, Args&&... args) noexcept(std::is_nothrow_constructible<T, Args...>::value)
        {
            construct_at(cast(self), std::forward<Args>(args)...);
        }

        static void destroy(storage_type& self)
        {
            destroy_at(cast(self));
        }

        static bool holds(const unique_any& self) noexcept
        {
            return self.interface == &table<T>::instance();
        }
    };

    // Specialization for holds<void>

    template <typename Unused>
    struct overload<void, Unused>
    {
        static void * cast(storage_type&) noexcept
        {
            return nullptr;
        }

        static const void * cast(const storage_type&) noexcept
        {
            return nullptr;
        }

        static bool holds(const unique_any& self) noexcept
        {
            return !self.has_value();
        }
    };

    template <typename T>
    struct table
    {
        static const struct interface& instance()
        {
            static constexpr struct interface data = { &overload<T>::destroy };
            return data;
        }
    };

    template <typename T>
    const T *cast() const noexcept
    {
        return overload<T>::cast(storage);
    }

    template <typename T>
    T *cast() noexcept
    {
        return overload<T>::cast(storage);
    }
};

template <typename T>
const T * any_cast(const unique_any *self) noexcept
{
    return self->holds<T>() ? self->cast<T>() : nullptr;
}

template <typename T>
T * any_cast(unique_any *self) noexcept
{
    return self->holds<T>() ? self->cast<T>() : nullptr;
}

} // namespace v1

using v1::unique_any;
using v1::any_cast;

} // namespace lean

#endif // LEAN_ANY_HPP
