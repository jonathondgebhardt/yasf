cmake_minimum_required(VERSION 3.14)

project(yasfViewer LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(yasf REQUIRED)
endif()

find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)

# ---- Viewer ----

add_executable(
  yasf_viewer
  source/main.cpp
)
target_link_libraries(
  yasf_viewer PRIVATE
  yasf::yasf
  SFML::Window
  SFML::Graphics
)
target_compile_features(yasf_viewer PRIVATE cxx_std_23)

