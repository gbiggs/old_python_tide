set(srcs view_base.cpp
    basic_stream_view.cpp
    basic_ra_view.cpp
    )
set(hdrs include/tide/views/view_base.h
    include/tide/views/basic_stream_view.h
    include/tide/views/basic_ra_view.h
    )

include_directories(include
    ${PROJECT_SOURCE_DIR}/log/include)

set(lib_name "tide_views")
add_library(${lib_name} ${TIDE_SHARED} ${srcs})
install(FILES ${hdrs} DESTINATION ${INCLUDE_INSTALL_DIR}/views
    COMPONENT headers)
install(TARGETS ${lib_name} LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    COMPONENT libs)

