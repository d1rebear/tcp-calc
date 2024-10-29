#include <cstdlib>
#include <iostream>

#include "Config.h"
#include "Server.hpp"

#include <boost/program_options.hpp>

int main( int argc, char** argv )
{
    using namespace boost::program_options;
    variables_map variables;

    try
    {
        options_description description( "Server-side of client-server "
                                         "calculator.\nOptions" );
        description.add_options()
                ( "address,a", value< std::string >()->default_value( "" ),
                  "| TCP socket address" )
                ( "port,p", value< std::string >()->default_value( "23" ),
                  "| TCP socket port" )
                ( "version,v", "| display version and exit" )
                ( "help,h", "| display help message and exit" );

        store( parse_command_line( argc, argv, description ), variables );
        notify( variables );

        if( variables.count( "help" ) > 0 )
        {
            std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
            std::cout << description;
            return EXIT_SUCCESS;
        }

        if( variables.count( "version" ) > 0 )
        {
            std::cout << PROJECT_NAME << " version: "
                      << PROJECT_VERSION << std::endl;
            return EXIT_SUCCESS;
        }
    }
    catch( const std::exception& ex )
    {
        std::cerr << "Server options error: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch( ... )
    {
        std::cerr << "Unknown server options error" << std::endl;
        return EXIT_FAILURE;
    }

    try
    {
        tcp_calc::server::Server server( variables["address"].as< std::string >(),
                                         variables["port"].as< std::string >() );
        server.run();
    }
    catch( const std::exception& ex )
    {
        std::cerr << "Server error: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch( ... )
    {
        std::cerr << "Unknown server error" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
