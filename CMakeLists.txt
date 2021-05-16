###############################################################################
#
# Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

cmake_minimum_required(VERSION 3.8)
project(lean CXX)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(cmake)

if (MSVC)
  target_compile_options(lean INTERFACE /W3)
else()
  target_compile_options(lean INTERFACE -Wall -Wextra -pedantic -Werror=return-type)
endif()

enable_testing()
add_subdirectory(test)
