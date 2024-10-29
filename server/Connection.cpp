#include "Connection.hpp"

#include "ConnectionManager.hpp"
#include "ExpressionEvaluator.hpp"

#include <boost/asio/placeholders.hpp>
#include <boost/bind.hpp>

#include <iostream>

namespace tcp_calc {
namespace server {

Connection::Connection( boost::asio::io_context& context,
                        ConnectionManager& connectionManager ):
    m_oSocket( context ),
    m_oConnectionManager( connectionManager )
{
}

boost::asio::ip::tcp::socket& Connection::socket()
{
    return m_oSocket;
}

void Connection::start()
{
    m_oSocket.async_read_some( boost::asio::buffer( m_arrBuffer ),
         boost::bind( &Connection::handleRead, shared_from_this(),
                      boost::asio::placeholders::error,
                      boost::asio::placeholders::bytes_transferred ) );
}

void Connection::stop()
{
    boost::system::error_code oIgnoredError;
    boost::system::error_code _ = m_oSocket.shutdown(
            boost::asio::ip::tcp::socket::shutdown_both, oIgnoredError );
    m_oSocket.close();
}

void Connection::handleRead( const boost::system::error_code& error,
                             std::size_t bytesTransferred )
{
    if( !error )
    {
        const std::string strExpression( m_arrBuffer.begin(),
                                         m_arrBuffer.begin()
                                         + bytesTransferred );

        std::cout << "Evaluating expression '"
                  << strExpression << "'" << std::endl;

        std::string strResult;
        expression_evaluator::evaluateExpression( strExpression,
                                                  strResult );

        std::cout << "Result: '"
                  << strResult << "'" << std::endl;

        m_oSocket.async_write_some( boost::asio::buffer( strResult ),
                  boost::bind( &Connection::handleWrite, shared_from_this(),
                               boost::asio::placeholders::error ) );
    }
    else if( error != boost::asio::error::operation_aborted )
    {
        m_oConnectionManager.stop( shared_from_this() );
    }
}

void Connection::handleWrite( const boost::system::error_code& /*error*/ )
{
    m_oConnectionManager.stop( shared_from_this() );
}

} // namespace server
} // namespace tcp_calc
