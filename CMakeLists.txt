cmake_minimum_required( VERSION 3.12 )

set( TCPCALC_VERSION 1.0.0 )

project( tcp-calc
    VERSION ${TCPCALC_VERSION}
    LANGUAGES CXX
)

set( CMAKE_CXX_STANDARD 98 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_VISIBILITY_PRESET hidden )
set( CMAKE_VISIBILITY_INLINES_HIDDEN ON )

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
