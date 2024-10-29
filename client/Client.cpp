#include "Client.hpp"

#include <boost/asio/connect.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>

#include <iostream>

namespace tcp_calc {
namespace client {

Client::Client( const std::string& address, const std::string& port ):
    m_oIOContext(),
    m_oSocket( m_oIOContext )
{
    using boost::asio::ip::tcp;

    //TODO: proper error handling
    tcp::resolver oResolver( m_oIOContext );
    tcp::resolver::results_type arrEndPoints = oResolver.resolve( address, port );
    boost::asio::connect( m_oSocket, arrEndPoints );
}

void Client::requestCalculation( const std::string& expression )
{
    /*
     * NOTE: Despite the fact that Telnet protocol is a requirement,
     *  as far as I can tell, it's not really needed here.
     *  Reasons are:
     *  - no options negotiation required to simply
     *   send an expression and print the result;
     *  - 'interactivity' is not a requirement.
     */

    boost::asio::streambuf oRequest;
    std::ostream oRequestStream( &oRequest );
    oRequestStream << expression;
    boost::asio::write( m_oSocket, oRequest );

    boost::asio::streambuf oResponse;
    boost::system::error_code oError;
    while( boost::asio::read( m_oSocket, oResponse,
                              boost::asio::transfer_at_least( 1 ),
                              oError ) )
    {
        std::cout << &oResponse << std::endl;
    }

    if( oError != boost::asio::error::eof )
    {
        throw boost::system::system_error( oError );
    }
}

} // namespace client
} // namespace tcp_calc
