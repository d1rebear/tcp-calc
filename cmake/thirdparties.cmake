cmake_minimum_required( VERSION 3.12 )

set( BOOST_ROOT "" CACHE PATH "Boost library path" )

set( Boost_USE_STATIC_LIBS ON )

find_package( Boost REQUIRED
    COMPONENTS
    chrono
    program_options
    system
)
