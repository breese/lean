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

get_filename_component(LEAN_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../" ABSOLUTE)
if (NOT DEFINED LEAN_BUILD_DIR)
  set(LEAN_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})
endif()
set(LIBRARY_OUTPUT_PATH ${LEAN_BUILD_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${LEAN_BUILD_DIR}/bin)

# Require at least C++11
set(LEAN_FEATURES cxx_std_11)

###############################################################################
# Lean
###############################################################################

add_library(lean INTERFACE)

set_target_properties(lean PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${LEAN_ROOT}/include"
  INTERFACE_COMPILE_FEATURES "${LEAN_FEATURES}")

install(DIRECTORY ${LEAN_ROOT}/include
  DESTINATION .
  FILES_MATCHING PATTERN "*.[hi]pp"
  )
