set(yasf_FOUND YES)

include(CMakeFindDependencyMacro)

if(yasf_FOUND)
  include("${CMAKE_CURRENT_LIST_DIR}/yasfTargets.cmake")
endif()
