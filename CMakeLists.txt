cmake_minimum_required( VERSION 3.30 )

set( TCPCALC_VERSION 1.0.0 )

project( tcp-calc
    VERSION ${TCPCALC_VERSION}
    LANGUAGES CXX
)

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set( CMAKE_EXPORT_COMPILE_COMMANDS 1)
set( CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR} )

# ignore BOOST deprecated headers
add_definitions("-DBOOST_ALLOW_DEPRECATED_HEADERS")
add_definitions("-DBOOST_BIND_GLOBAL_PLACEHOLDERS")

option( BUILD_SERVER "Build server" ON )
option( BUILD_CLIENT "Build client" ON )

message( "Build server: ${BUILD_SERVER}" )
message( "Build client: ${BUILD_CLIENT}" )

include( cmake/thirdparties.cmake )

add_subdirectory( util )

if( BUILD_SERVER )
    add_subdirectory( server )
endif()

if( BUILD_CLIENT )
    add_subdirectory( client )
endif()
