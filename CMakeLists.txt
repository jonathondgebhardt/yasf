cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    yasf
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    yasf_yasf
	source/component.cpp
    source/object.cpp
)
add_library(yasf::yasf ALIAS yasf_yasf)

include(GenerateExportHeader)
generate_export_header(
    yasf_yasf
    BASE_NAME yasf
    EXPORT_FILE_NAME export/yasf/yasf_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(yasf_yasf PUBLIC YASF_STATIC_DEFINE)
endif()

set_target_properties(
    yasf_yasf PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME yasf
    OUTPUT_NAME yasf
)

target_include_directories(
    yasf_yasf ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    yasf_yasf SYSTEM
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(yasf_yasf PUBLIC cxx_std_23)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT yasf_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of yasf"
  )
endif()

include(cmake/dev-mode.cmake)
