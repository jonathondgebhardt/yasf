cmake_minimum_required(VERSION 3.14)

project(gravitySim LANGUAGES CXX)

include(../../cmake/project-is-top-level.cmake)
include(../../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(yasf COMPONENTS viewer CONFIG REQUIRED)
endif()

# ---- Tests ----

add_executable(
  gravity_sim
  source/main.cpp
)
target_link_libraries(
    gravity_sim PRIVATE
    yasf::yasf
    yasf::viewer
)
target_compile_features(gravity_sim PRIVATE cxx_std_23)

# ---- End-of-file commands ----

add_folders(Examples)
