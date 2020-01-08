#include "Server.hpp"

#include "Config.h"
#include "Connection.hpp"

#include <boost/asio/placeholders.hpp>
#include <boost/bind.hpp>

#include <iostream>

#include <signal.h>

namespace tcp_calc {
namespace server {

Server::Server( const std::string& address, const std::string& port ):
    m_oIOContext(),
    m_oSignalSet( m_oIOContext ),
    m_oAcceptor( m_oIOContext ),
    m_oConnectionManager(),
    m_pConnection()
{
    m_oSignalSet.add( SIGINT );
    m_oSignalSet.add( SIGTERM );
#if defined( SIGQUIT )
    m_oSignalSet.add( SIGQUIT );
#endif // defined( SIGQUIT )
    m_oSignalSet.async_wait( boost::bind( &Server::handleStop, this ) );

    using boost::asio::ip::tcp;

    tcp::resolver oResolver( m_oIOContext );
    tcp::endpoint oEndPoint = *oResolver.resolve( tcp::v4(), address, port ).begin();

    m_oAcceptor.open( oEndPoint.protocol() );
    m_oAcceptor.set_option( tcp::acceptor::reuse_address( true ) );
    m_oAcceptor.bind( oEndPoint );
    m_oAcceptor.listen();

    std::cout << "Running " << PROJECT_NAME << " at "
              << oEndPoint.address().to_string() << ":"
              << oEndPoint.port() << std::endl;

    startAccept();
}

void Server::run()
{
    m_oIOContext.run();
}

void Server::startAccept()
{
    m_pConnection.reset( new Connection( m_oIOContext, m_oConnectionManager ) );
    m_oAcceptor.async_accept( m_pConnection->socket(),
        boost::bind( &Server::handleAccept, this,
                     boost::asio::placeholders::error ) );
}

void Server::handleAccept( const boost::system::error_code& error )
{
    if( !m_oAcceptor.is_open() )
    {
        return;
    }

    if( !error )
    {
        m_oConnectionManager.start( m_pConnection );
    }

    startAccept();
}

void Server::handleStop()
{
    m_oAcceptor.close();
    m_oConnectionManager.stopAll();

    std::cout << "\n" << PROJECT_NAME << " stopped" << std::endl;
}

} // namespace server
} // namespace tcp_calc
