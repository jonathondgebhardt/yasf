set( FORMAT_PATTERNS
	source/*.cpp source/*.hpp
	include/*.hpp
	test/*.cpp test/*.hpp
	CACHE STRING
	"; separated patterns relative to the project source dir to grep"
)

set(BAD_WORDS "TODO;FIXME" CACHE STRING "Bad words to check")

add_custom_target(
	todo-check
	COMMAND "${CMAKE_COMMAND}"
	-D "BAD_WORDS=${BAD_WORDS}"
	-D "PATTERNS=${FORMAT_PATTERNS}"
	-P "${PROJECT_SOURCE_DIR}/cmake/todo.cmake"
	WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
	COMMENT "Looking for TODO in the code"
	VERBATIM
)
