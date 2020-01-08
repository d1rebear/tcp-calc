#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "Config.h"
#include "Client.hpp"

#include <TimeLog.hpp>

#include <boost/program_options.hpp>

void printHelp( boost::program_options::options_description& description )
{
    std::cout << "Usage: " << PROJECT_NAME << " [options]" << std::endl;
    std::cout << description;
}

int main( int argc, char** argv )
{
    tcp_calc::util::time::ScopedTimeLog timelog( "whole client" );
    (void) timelog;

    namespace bpo = boost::program_options;
    bpo::variables_map vm;

    try
    {
        bpo::options_description description( "Client-side of client-server "
                                              "calculator.\nOptions" );
        description.add_options()
                ( "address,a", bpo::value< std::string >(),
                  "| Server TCP socket address (required)" )
                ( "port,p", bpo::value< std::string >()->default_value( "21" ),
                  "| Server TCP socket port" )
                ( "expression,e", bpo::value< std::string >(),
                  "| Expression to calculate (required; single quoted)" )
                ( "version,v", "| display version and exit" )
                ( "help,h", "| display help message and exit" );

        bpo::store( bpo::parse_command_line( argc, argv, description ), vm );
        bpo::notify( vm );

        if( vm.count( "help" ) > 0 )
        {
            printHelp( description );
            return EXIT_SUCCESS;
        }

        if( vm.count( "version" ) > 0 )
        {
            std::cout << PROJECT_NAME << " version: "
                      << PROJECT_VERSION << std::endl;
            return EXIT_SUCCESS;
        }

        if( vm.count( "address" ) == 0 )
        {
            std::cerr << "Server TCP socket address "
                         "is required but missing" << std::endl;
            printHelp( description );
            return EXIT_FAILURE;
        }

        if( vm.count( "expression" ) == 0 )
        {
            std::cerr << "Expression to calculate "
                         "is required but missing" << std::endl;
            printHelp( description );
            return EXIT_FAILURE;
        }
    }
    catch( const std::exception& ex )
    {
        std::cerr << "Client options error: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch( ... )
    {
        std::cerr << "Unknown client options error" << std::endl;
        return EXIT_FAILURE;
    }

    try
    {
        tcp_calc::client::Client client( vm["address"].as< std::string >(),
                                         vm["port"].as< std::string >() );
        client.requestCalculation( vm["expression"].as< std::string >() );
    }
    catch( const std::exception& ex )
    {
        std::cerr << "Client error: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch( ... )
    {
        std::cerr << "Unknown client error" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
