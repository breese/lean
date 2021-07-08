#ifndef LEAN_DETAIL_CONFIG_HPP
#define LEAN_DETAIL_CONFIG_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

# define LEAN_CXX14 201402L
# define LEAN_CXX17 201703L
# define LEAN_CXX20 202002L

#if __cplusplus >= LEAN_CXX20
# define LEAN_ENABLE_CXX20(x) x
#else
# define LEAN_ENABLE_CXX20(x)
#endif

#if __cplusplus >= LEAN_CXX17
# define LEAN_ENABLE_CXX17(x) x
#else
# define LEAN_ENABLE_CXX17(x)
#endif

#if __cplusplus >= LEAN_CXX14
# define LEAN_ENABLE_CXX14(x) x
#else
# define LEAN_ENABLE_CXX14(x)
#endif

#define LEAN_CONSTEXPR_CXX14 LEAN_ENABLE_CXX14(constexpr)
#define LEAN_CONSTEXPR_CXX17 LEAN_ENABLE_CXX17(constexpr)
#define LEAN_CONSTEXPR_CXX20 LEAN_ENABLE_CXX20(constexpr)

#endif // LEAN_DETAIL_CONFIG_HPP
