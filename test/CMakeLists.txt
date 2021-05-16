###############################################################################
#
# Copyright (C) 2021 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

function(lean_test name)
  add_executable(${name} ${ARGN})
  target_link_libraries(${name} lean)
  add_test(${name} ${EXECUTABLE_OUTPUT_PATH}/${name})
endfunction()

lean_test(unique_any_suite unique_any_suite.cpp)
