set(cmake_modules tide_utils.cmake)

install(FILES ${cmake_modules} DESTINATION share/cmake/Modules
    COMPONENT cmakestuff)

set(PKG_DESC "TIDE logging library")
set(PKG_EXTERNAL_DEPS "")
set(pkg_conf_file ${CMAKE_CURRENT_BINARY_DIR}/tide.pc)
configure_file(tide.pc.in ${pkg_conf_file} @ONLY)
install(FILES ${pkg_conf_file}
    DESTINATION ${LIB_INSTALL_DIR}/pkgconfig/ COMPONENT pkgconfig)

