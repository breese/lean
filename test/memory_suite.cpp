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

int main()
{
    construct_suite::run();
    return 0;
}
