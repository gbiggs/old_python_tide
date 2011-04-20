set(srcs channels.cpp
    entry_index_base.cpp
    memory_log.cpp
    )
set(hdrs include/tide/log/channels.h
    include/tide/log/log_base.h
    include/tide/log/entry_index_base.h
    include/tide/log/memory_log.h
    )

include_directories(include)

set(lib_name "tide_log")
add_library(${lib_name} ${TIDE_SHARED} ${srcs})
install(FILES ${hdrs} DESTINATION ${INCLUDE_INSTALL_DIR}/log
    COMPONENT headers)
install(TARGETS ${lib_name} LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    COMPONENT libs)

