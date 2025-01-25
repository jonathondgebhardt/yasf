cmake_minimum_required(VERSION 3.14)

macro(default name)
	if(NOT DEFINED "${name}")
		set("${name}" "${ARGN}")
	endif()
endmacro()

default(TODO_COMMAND grep)
default(PATTERNS
	source/*.cpp source/*.hpp
	include/*.hpp
	test/*.cpp test/*.hpp
)

set(flags "-n")

file(GLOB_RECURSE files ${PATTERNS})
set(contains_todo "")
set(output "")
string(LENGTH "${CMAKE_SOURCE_DIR}/" path_prefix_length)

foreach(file IN LISTS files)
	execute_process(
		COMMAND "${TODO_COMMAND}" "${flags}" "TODO" "${file}"
		WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
		RESULT_VARIABLE result
		OUTPUT_VARIABLE output
	)
	if(result EQUAL "0")
		message(WARNING "'${file}': found bad word\n${output}")

		string(SUBSTRING "${file}" "${path_prefix_length}" -1 relative_file)
		list(APPEND contains_todo "${relative_file}")
	endif()
	set(output "")
endforeach()

if(NOT contains_todo STREQUAL "")
	list(JOIN contains_todo "\n" bad_list)
	message("The following files contain TODO:\n\n${bad_list}\n")
endif()
