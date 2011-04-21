set(srcs basic_stream_view.cpp
    basic_ra_view.cpp
    direct_writer.cpp
    )
set(hdrs include/tide/views/view.h
    include/tide/views/basic_stream_view.h
    include/tide/views/basic_ra_view.h
    include/tide/views/direct_writer.h
    )

include_directories(include
    ${PROJECT_SOURCE_DIR}/log/include)

set(lib_name "tide_views")
add_library(${lib_name} ${TIDE_SHARED} ${srcs})
install(FILES ${hdrs} DESTINATION ${INCLUDE_INSTALL_DIR}/views
    COMPONENT headers)
install(TARGETS ${lib_name} LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    COMPONENT libs)

