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
#include <lean/tuple.hpp>

//-----------------------------------------------------------------------------

namespace apply_suite
{

template <typename T>
struct summerize
{
    template <typename... Args>
    T operator()(T head, Args&&... tail) { return head + operator()(std::forward<Args>(tail)...); }

    T operator()() { return {}; }
};

void apply_return()
{
    assert(lean::apply_r<int>(summerize<int>{}, std::make_tuple(1)) == 1);
    assert(lean::apply_r<int>(summerize<int>{}, std::make_tuple(1, 2)) == 3);
    assert(lean::apply_r<int>(summerize<int>{}, std::make_tuple(1, 2, 3)) == 6);
    assert(lean::apply_r<int>(summerize<int>{}, std::make_tuple(1, 2, 3, 4)) == 10);
}

void run()
{
    apply_return();
}

} // namespace apply_suite

//-----------------------------------------------------------------------------

int main()
{
    apply_suite::run();
    return 0;
}
