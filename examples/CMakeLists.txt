include_directories(${PROJECT_SOURCE_DIR}/log/include
    ${PROJECT_SOURCE_DIR}/views/include)

set(mem_log mem_log.cpp)
add_executable(tide_memlog_sample ${mem_log})
target_link_libraries(tide_memlog_sample tide_log tide_views)
install(TARGETS tide_memlog_sample RUNTIME DESTINATION ${BIN_INSTALL_DIR}
    COMPONENT examples)

