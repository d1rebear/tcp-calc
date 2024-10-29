cmake_minimum_required( VERSION 3.30 )

project( tcp-calc-client
    VERSION ${TCPCALC_VERSION}
    LANGUAGES CXX
)

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/Config.h.in Config.h @ONLY )

set( CLIENT_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Client.hpp
)

set( CLIENT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Client.cpp
)

add_executable( ${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CLIENT_HEADERS}
    ${CLIENT_SOURCES}
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
    tcp-calc-utils
)

install( TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
