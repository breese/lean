add_library(lean-core
  platform.cpp
  )

target_include_directories(lean-core PRIVATE .)
target_link_libraries(lean-core lean)
