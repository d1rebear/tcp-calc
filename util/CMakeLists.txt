cmake_minimum_required( VERSION 3.12 )

project( tcp-calc-utils
    VERSION ${TCPCALC_VERSION}
    LANGUAGES CXX
)

add_library( ${PROJECT_NAME} INTERFACE )

target_include_directories( ${PROJECT_NAME}
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources( ${PROJECT_NAME}
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/TimeLog.hpp
)

target_link_libraries( ${PROJECT_NAME}
    INTERFACE
    Boost::chrono
)
