###############################################################################
#
# Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

find_package(Threads REQUIRED)

function(lean_test name)
  add_executable(${name} ${ARGN})
  target_include_directories(${name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(${name} lean-core ${CMAKE_THREAD_LIBS_INIT})
  add_test(${name} ${EXECUTABLE_OUTPUT_PATH}/${name})
endfunction()

# any
lean_test(any_suite any_suite.cpp)

# atomic
lean_test(atomic_suite atomic_suite.cpp)

# checked
lean_test(checked_suite checked_suite.cpp)

# checked
lean_test(function_type_suite function_type_suite.cpp)

# throw_exception
lean_test(throw_suite throw_suite.cpp)

# tuple
lean_test(tuple_suite tuple_suite.cpp)

# type_traits
lean_test(type_traits_suite type_traits_suite.cpp)

# utility
lean_test(utility_suite utility_suite.cpp)
