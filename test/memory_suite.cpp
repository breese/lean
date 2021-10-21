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

void api_construct() {
    {
        inplace_storage<int> storage;
        using inplace = inplace_traits<decltype(storage)>;
        inplace::construct(&storage, 42);
        assert(*storage.data() == 42);
        inplace::destroy(&storage);
    }
    {
        inplace_storage<const int> storage;
        using inplace = inplace_traits<decltype(storage)>;
        inplace::construct(&storage, 42);
        assert(*storage.data() == 42);
        inplace::destroy(&storage);
    }
}

void api_copy() {
    {
        inplace_storage<int> storage;
        using inplace = inplace_traits<decltype(storage)>;
        inplace::construct(&storage, 42);
        assert(*storage.data() == 42);
        inplace_storage<int> clone;
        inplace::construct(&clone, storage);
        assert(*storage.data() == 42);
        assert(*clone.data() == 42);
        inplace::destroy(&clone);
        inplace::destroy(&storage);
    }
    {
        inplace_storage<const int> storage;
        using inplace = inplace_traits<decltype(storage)>;
        inplace::construct(&storage, 42);
        assert(*storage.data() == 42);
        inplace_storage<const int> clone;
        inplace::construct(&clone, storage);
        assert(*storage.data() == 42);
        assert(*clone.data() == 42);
        inplace::destroy(&clone);
        inplace::destroy(&storage);
    }
}

void api_move() {
    {
        inplace_storage<int> storage;
        using inplace = inplace_traits<decltype(storage)>;
        inplace::construct(&storage, 42);
        assert(*storage.data() == 42);
        inplace_storage<int> clone;
        inplace::construct(&clone, std::move(storage));
        assert(*clone.data() == 42);
        inplace::destroy(&clone);
        inplace::destroy(&storage);
    }
    {
        inplace_storage<const int> storage;
        using inplace = inplace_traits<decltype(storage)>;
        inplace::construct(&storage, 42);
        assert(*storage.data() == 42);
        inplace_storage<const int> clone;
        inplace::construct(&clone, std::move(storage));
        assert(*clone.data() == 42);
        inplace::destroy(&clone);
        inplace::destroy(&storage);
    }
}

void run()
{
    api_construct();
    api_copy();
    api_move();
}

} // namespace inplace_storage_suite

//-----------------------------------------------------------------------------

int main()
{
    construct_suite::run();
    inplace_storage_suite::run();
    return 0;
}
