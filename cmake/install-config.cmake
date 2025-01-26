set(yasf_FOUND YES)

include(CMakeFindDependencyMacro)
find_dependency(boost_uuid)
find_dependency(spdlog)

if(yasf_FOUND)
  include("${CMAKE_CURRENT_LIST_DIR}/yasfTargets.cmake")
endif()
