cmake_minimum_required(VERSION 3.14)

project(behaviorTree LANGUAGES CXX)

include(../../cmake/project-is-top-level.cmake)
include(../../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(yasf COMPONENTS viewer CONFIG REQUIRED)
endif()

# ---- Tests ----

add_executable(
  behavior_tree
  source/main.cpp
  source/node_drawable.cpp
)
target_link_libraries(
    behavior_tree PRIVATE
    yasf::yasf
    yasf::viewer
)
target_compile_features(behavior_tree PRIVATE cxx_std_23)

# ---- End-of-file commands ----

add_folders(Examples)

