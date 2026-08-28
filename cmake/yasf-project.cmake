function(yasf_add_library LIB_NAME)
	set(multiValueArgs SOURCES INCLUDE_DIRS LINKS)
	cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

	add_library(yasf_${LIB_NAME} ${ARG_SOURCES})
	add_library(yasf::${LIB_NAME} ALIAS yasf_${LIB_NAME})

	include(GenerateExportHeader)
	generate_export_header(
		yasf_${LIB_NAME}
		BASE_NAME yasf_${LIB_NAME}
		EXPORT_FILE_NAME export/yasf/${LIB_NAME}/yasf_${LIB_NAME}_export.hpp
		CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
	)

	if(NOT BUILD_SHARED_LIBS)
		target_compile_definitions(yasf_${LIB_NAME} PUBLIC YASF_STATIC_DEFINE)
	endif()

	set_target_properties(
		yasf_${LIB_NAME} PROPERTIES
		CXX_VISIBILITY_PRESET hidden
		VISIBILITY_INLINES_HIDDEN YES
		VERSION "${PROJECT_VERSION}"
		SOVERSION "${PROJECT_VERSION_MAJOR}"
		EXPORT_NAME yasf_${LIB_NAME}
		OUTPUT_NAME yasf_${LIB_NAME}
	)

	target_include_directories(
		yasf_${LIB_NAME} ${warning_guard}
		PUBLIC
		"\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
	)

	target_include_directories(
		yasf_${LIB_NAME} SYSTEM
		PUBLIC
		"\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
	)

	target_compile_features(yasf_${LIB_NAME} PUBLIC cxx_std_23)

	if(ARG_LINKS)
		target_link_libraries(yasf_${LIB_NAME} PRIVATE ${ARG_LINKS})
	endif()
endfunction()

function(yasf_add_test TEST_NAME)
	set(multiValueArgs SOURCES INCLUDE_DIRS LINKS)
	cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

	add_executable(yasf_${TEST_NAME}_test ${ARG_SOURCES})

	target_compile_features(yasf_${TEST_NAME}_test PRIVATE cxx_std_23)

	if(ARG_LINKS)
		target_link_libraries(yasf_${TEST_NAME}_test PRIVATE ${ARG_LINKS})
	endif()

	target_link_libraries(
		yasf_${TEST_NAME}_test PRIVATE
		Catch2::Catch2WithMain
	)

	catch_discover_tests(yasf_${TEST_NAME}_test)
endfunction()
