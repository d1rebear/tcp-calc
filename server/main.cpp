#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "Config.h"
#include "Server.hpp"

#include <boost/program_options.hpp>

int main( int argc, char** argv )
{
    namespace bpo = boost::program_options;
    bpo::variables_map vm;

    try
    {
        bpo::options_description description( "Server-side of client-server "
                                              "calculator.\nOptions" );
        description.add_options()
                ( "address,a", bpo::value< std::string >()->default_value( "" ),
                  "| TCP socket address" )
                ( "port,p", bpo::value< std::string >()->default_value( "23" ),
                  "| TCP socket port" )
                ( "version,v", "| display version and exit" )
                ( "help,h", "| display help message and exit" );

        bpo::store( bpo::parse_command_line( argc, argv, description ), vm );
        bpo::notify( vm );

        if( vm.count( "help" ) > 0 )
        {
            std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
            std::cout << description;
            return EXIT_SUCCESS;
        }

        if( vm.count( "version" ) > 0 )
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
        tcp_calc::server::Server server( vm["address"].as< std::string >(),
                                         vm["port"].as< std::string >() );
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
