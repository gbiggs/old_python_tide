set(srcs channels.cpp)
set(hdrs include/tide/common/channels.h)

include_directories(include)

set(lib_name "tide_common")
add_library(${lib_name} ${TIDE_SHARED} ${srcs})
install(FILES ${hdrs} DESTINATION ${INCLUDE_INSTALL_DIR}/common
    COMPONENT headers)
install(TARGETS ${lib_name} LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    COMPONENT libs)

