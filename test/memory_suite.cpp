///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include "test_assert.hpp"
#include <lean/memory.hpp>

//-----------------------------------------------------------------------------

struct trivial_dtor
{
    ~trivial_dtor() = default;
};

struct nontrivial_dtor
{
    ~nontrivial_dtor() {}
};

struct virtual_dtor
{
    virtual ~virtual_dtor() = default;
};

//-----------------------------------------------------------------------------

namespace addressof_suite
{

using namespace lean::v1;

int variable = 0;

static_assert(addressof(variable) == &variable, "");

} // namespace addressof_suite

//-----------------------------------------------------------------------------

namespace construct_suite
{

using namespace lean::v1;

void construct_int()
{
    using type = int;
    unsigned char buffer[sizeof(type)];
    auto ptr = construct_at(reinterpret_cast<type *>(&buffer), 42);
    assert(ptr = reinterpret_cast<type *>(&buffer));
    assert(*ptr == 42);
    destroy_at(ptr);
}

void construct_const_int()
{
    using type = const int;
    unsigned char buffer[sizeof(type)];
    auto ptr = construct_at(reinterpret_cast<type *>(&buffer), 42);
    assert(ptr = reinterpret_cast<type *>(&buffer));
    assert(*ptr == 42);
    destroy_at(ptr);
}

void construct_trivial()
{
    using type = trivial_dtor;
    unsigned char buffer[sizeof(type)];
    auto ptr = construct_at(reinterpret_cast<type *>(&buffer));
    assert(ptr = reinterpret_cast<type *>(&buffer));
    destroy_at(ptr);
}

void construct_nontrivial()
{
    using type = nontrivial_dtor;
    unsigned char buffer[sizeof(type)];
    auto ptr = construct_at(reinterpret_cast<type *>(&buffer));
    assert(ptr = reinterpret_cast<type *>(&buffer));
    destroy_at(ptr);
}

void construct_virtual()
{
    using type = virtual_dtor;
    unsigned char buffer[sizeof(type)];
    auto ptr = construct_at(reinterpret_cast<type *>(&buffer));
    assert(ptr = reinterpret_cast<type *>(&buffer));
    destroy_at(ptr);
}

void construct_const_virtual()
{
    using type = const virtual_dtor;
    unsigned char buffer[sizeof(type)];
    auto ptr = construct_at(reinterpret_cast<type *>(&buffer));
    assert(ptr = reinterpret_cast<type *>(&buffer));
    destroy_at(ptr);
}

void run()
{
    construct_int();
    construct_const_int();
    construct_trivial();
    construct_nontrivial();
    construct_virtual();
    construct_const_virtual();
}

} // namespace construct_suite

//-----------------------------------------------------------------------------

namespace inplace_storage_suite
{

using namespace lean::v1;

static_assert(std::is_nothrow_default_constructible<inplace_storage<int>>(),
              "default constructible");
static_assert(!std::is_copy_constructible<inplace_storage<int>>(),
              "not copyable");
static_assert(!std::is_move_constructible<inplace_storage<int>>(),
              "not movable");

static_assert(std::is_same<typename inplace_storage<int>::value_type, int>(), "");
static_assert(std::is_same<typename inplace_storage<const int>::value_type, int>(), "");

void api_construct_default()
{
    {
        inplace_storage<int> storage;
        (void)storage; // Uninitialized, nothing to destroy
    }
    {
        inplace_storage<const int> storage;
        (void)storage; // Uninitialized, nothing to destroy
    }
    {
        inplace_storage<int> storage;
        construct_at(storage.data(), 42);
        assert(*storage.data() == 42);
        destroy_at(storage.data());
    }
    {
        inplace_storage<const int> storage;
        construct_at(storage.data(), 42);
        assert(*storage.data() == 42);
        destroy_at(storage.data());
    }
}

void api_construct_value()
{
    {
        inplace_storage<int> storage(42);
        assert(*storage.data() == 42);
        destroy_at(storage.data());
    }
    {
        inplace_storage<const int> storage(42);
        assert(*storage.data() == 42);
        destroy_at(storage.data());
    }
}

void api_copy()
{
    {
        inplace_storage<int> storage(42);
        inplace_storage<int> clone;
        construct_at(clone.data(), *storage.data());
        assert(*storage.data() == 42);
        assert(*clone.data() == 42);
        destroy_at(clone.data());
        destroy_at(storage.data());
    }
    {
        inplace_storage<const int> storage(42);
        inplace_storage<const int> clone;
        construct_at(clone.data(), *storage.data());
        assert(*storage.data() == 42);
        assert(*clone.data() == 42);
        destroy_at(clone.data());
        destroy_at(storage.data());
    }
}

void api_move()
{
    {
        inplace_storage<int> storage(42);
        assert(*storage.data() == 42);
        inplace_storage<int> clone;
        construct_at(clone.data(), std::move(*storage.data()));
        assert(*clone.data() == 42);
        destroy_at(clone.data());
        destroy_at(storage.data());
    }
    {
        inplace_storage<const int> storage(42);
        assert(*storage.data() == 42);
        inplace_storage<const int> clone;
        construct_at(clone.data(), std::move(*storage.data()));
        assert(*clone.data() == 42);
        destroy_at(clone.data());
        destroy_at(storage.data());
    }
}

void run()
{
    api_construct_default();
    api_construct_value();
    api_copy();
    api_move();
}

} // namespace inplace_storage_suite

//-----------------------------------------------------------------------------

namespace inplace_union_suite
{

using namespace lean::v1;

static_assert(std::is_nothrow_default_constructible<inplace_union<int>>(),
              "default constructible");
static_assert(std::is_nothrow_default_constructible<inplace_union<int, double>>(),
              "default constructible");
static_assert(!std::is_copy_constructible<inplace_union<int>>(),
              "not copyable");
static_assert(!std::is_move_constructible<inplace_union<int>>(),
              "not movable");

static_assert(std::is_same<typename inplace_union<int>::value_type, int>(), "");
static_assert(std::is_same<typename inplace_union<char, int>::value_type, int>(), "");
static_assert(std::is_same<typename inplace_union<char, int, double>::value_type, double>(), "");

void api_construct_default()
{
    {
        inplace_union<char, int, double> storage;
        (void)storage; // Uninitialized, nothing to destroy
    }
    {
        inplace_union<char, int, double> storage;
        construct_at(storage.data<char>(), 'A');
        assert(*storage.data<char>() == 'A');
        destroy_at(storage.data<char>());
    }
    {
        inplace_union<char, int, double> storage;
        construct_at(storage.data<int>(), 42);
        assert(*storage.data<int>() == 42);
        destroy_at(storage.data<int>());
    }
    {
        inplace_union<char, int, double> storage;
        construct_at(storage.data<double>(), 42.);
        assert(*storage.data<double>() == 42.);
        destroy_at(storage.data<double>());
    }
}

void api_construct_value()
{
    {
        inplace_union<char, int, double> storage(42); // Stored as default value_type
        assert(*storage.data<decltype(storage)::value_type>() == 42);
        destroy_at(storage.data<decltype(storage)::value_type>());
    }
}

void run()
{
    api_construct_default();
    api_construct_value();
}

} // namespace inplace_union_suite

//-----------------------------------------------------------------------------

int main()
{
    construct_suite::run();
    inplace_storage_suite::run();
    inplace_union_suite::run();
    return 0;
}
