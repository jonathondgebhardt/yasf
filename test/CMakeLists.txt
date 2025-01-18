cmake_minimum_required(VERSION 3.14)

project(yasfTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(yasf REQUIRED)
  enable_testing()
endif()

find_package(Catch2 REQUIRED)
include(Catch)

# ---- Tests ----

add_executable(
	yasf_test
	source/component_test.cpp
	source/entity_factory_test.cpp
	source/entity_test.cpp
	source/object_factory_test.cpp
	source/object_test.cpp
	source/position_test.cpp
	source/status_test.cpp
	source/uuid_test.cpp
	source/vec3d_test.cpp
	source/velocity_test.cpp
)
target_link_libraries(
    yasf_test PRIVATE
    yasf::yasf
    Catch2::Catch2WithMain
)
target_compile_features(yasf_test PRIVATE cxx_std_23)

catch_discover_tests(yasf_test)

# ---- End-of-file commands ----

add_folders(Test)
