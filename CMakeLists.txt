cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(TIDE)
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)

include(${PROJECT_SOURCE_DIR}/cmake/tide_utils.cmake)

# Set version and OS-specific settings
set(TIDE_VERSION 1.0.0 CACHE STRING "TIDE version")
DISSECT_VERSION()
GET_OS_INFO()

# Add an "uninstall" target
CONFIGURE_FILE ("${PROJECT_SOURCE_DIR}/cmake/uninstall_target.cmake.in"
    "${PROJECT_BINARY_DIR}/uninstall_target.cmake" IMMEDIATE @ONLY)
ADD_CUSTOM_TARGET (uninstall "${CMAKE_COMMAND}" -P
    "${PROJECT_BINARY_DIR}/uninstall_target.cmake")

# Global options
option(BUILD_SHARED "Build shared libraries." ON)
if(BUILD_SHARED)
    set(TIDE_SHARED "SHARED")
else(BUILD_SHARED)
    set(TIDE_SHARED "STATIC")
endif(BUILD_SHARED)

# Subdirectories
add_subdirectory(common)
#add_subdirectory(log)
add_subdirectory(views)
#add_subdirectory(utils)

# Package creation
include(InstallRequiredSystemLibraries)
set(TIDE_DESCRIPTION "TIDE logging library")
set(TIDE_VENDOR "RETF")
configure_file("${PROJECT_SOURCE_DIR}/cmake/cpack_options.cmake.in"
    "${PROJECT_BINARY_DIR}/cpack_options.cmake" @ONLY)
set(CPACK_PROJECT_CONFIG_FILE "${PROJECT_BINARY_DIR}/cpack_options.cmake")
include(CPack)

