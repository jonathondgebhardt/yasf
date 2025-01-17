if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/yasf-${PROJECT_VERSION}"
      CACHE STRING ""
  )
  set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
# should match the name of variable set in the install-config.cmake script
set(package yasf)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT yasf_Development
)

install(
    TARGETS yasf_yasf
    EXPORT yasfTargets
    RUNTIME #
    COMPONENT yasf_Runtime
    LIBRARY #
    COMPONENT yasf_Runtime
    NAMELINK_COMPONENT yasf_Development
    ARCHIVE #
    COMPONENT yasf_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    yasf_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE yasf_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(yasf_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${yasf_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT yasf_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${yasf_INSTALL_CMAKEDIR}"
    COMPONENT yasf_Development
)

install(
    EXPORT yasfTargets
    NAMESPACE yasf::
    DESTINATION "${yasf_INSTALL_CMAKEDIR}"
    COMPONENT yasf_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
