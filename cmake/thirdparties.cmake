cmake_minimum_required( VERSION 3.12 )

set( BOOST_ROOT "" CACHE PATH "Boost library path" )

set( Boost_NO_SYSTEM_PATHS ON CACHE BOOL "Do not search system for Boost" )
set( Boost_USE_STATIC_LIBS ON )

find_package( Boost 1.72 REQUIRED
    COMPONENTS
    chrono
    program_options
    system
)
