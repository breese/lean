#ifndef LEAN_TEST_ASSERT_HPP
#define LEAN_TEST_ASSERT_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#undef NDEBUG
#include <cassert>

#define assert_throw(expression) do { try { expression; assert(false); } catch(...) {}; } while(false)
#define assert_nothrow(expression) do { try { expression; } catch (...) { assert(false); } } while(false)
#define assert_throw_with(expression,exception) do { try { expression; assert(false); } catch(const exception&) {}; } while(false)

#endif // LEAN_TEST_ASSERT_HPP
