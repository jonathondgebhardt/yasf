cmake_minimum_required(VERSION 3.14)

project(yasfViewer LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(yasf REQUIRED)
endif()

find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)

# ---- Viewer ----

add_library(
  yasf_viewer
  source/graphics_window.cpp
  source/scene_manager.cpp
)
add_library(yasf::viewer ALIAS yasf_viewer)

include(GenerateExportHeader)
generate_export_header(
    yasf_viewer
    BASE_NAME yasf_viewer
    EXPORT_FILE_NAME export/yasf/viewer/yasf_viewer_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(yasf_yasf PUBLIC YASF_STATIC_DEFINE)
endif()

set_target_properties(
    yasf_viewer PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME yasf
    OUTPUT_NAME yasf
)

target_include_directories(
    yasf_viewer ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    yasf_viewer SYSTEM
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(yasf_viewer PUBLIC cxx_std_23)

target_link_libraries(
  yasf_viewer 
  PRIVATE
    yasf::yasf
  PUBLIC
    SFML::Window
    SFML::Graphics
    SFML::System
    ImGui-SFML::ImGui-SFML
)

# ---- End-of-file commands ----

add_folders(Viewer)
