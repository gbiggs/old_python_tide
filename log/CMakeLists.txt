set(srcs log_base.cpp
    )
set(hdrs include/tide/log/log_base.h
    )

include_directories(include
    ${PROJECT_SOURCE_DIR}/common/include)

set(lib_name "tide_log")
add_library(${lib_name} ${TIDE_SHARED} ${srcs})
install(FILES ${hdrs} DESTINATION ${INCLUDE_INSTALL_DIR}/log
    COMPONENT headers)
install(TARGETS ${lib_name} LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    COMPONENT libs)

