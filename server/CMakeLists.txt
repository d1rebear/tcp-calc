cmake_minimum_required( VERSION 3.30 )

project( tcp-calc-server
    VERSION ${TCPCALC_VERSION}
    LANGUAGES CXX
)

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/Config.h.in Config.h @ONLY )

set( SERVER_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Connection.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ConnectionFwd.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ConnectionManager.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpressionEvaluator.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.hpp
)

set( SERVER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Connection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ConnectionManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ExpressionEvaluator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.cpp
)

add_executable( ${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${SERVER_HEADERS}
    ${SERVER_SOURCES}
)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
    ${Boost_INCLUDE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
    Boost::program_options
    Boost::system
)

install( TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
