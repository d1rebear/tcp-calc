#pragma once
#ifndef TCPCALC_SERVER_CONNECTION_HPP
#define TCPCALC_SERVER_CONNECTION_HPP

#include <boost/array.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace tcp_calc {
namespace server {

class ConnectionManager;

class Connection:
        public boost::enable_shared_from_this< Connection >,
        private boost::noncopyable
{
public:
    explicit Connection( boost::asio::io_context& context,
                         ConnectionManager& connectionManager );

    boost::asio::ip::tcp::socket& socket();
    void start();
    void stop();

private:
    void handleRead( const boost::system::error_code& error,
                     std::size_t bytesTransferred );
    void handleWrite( const boost::system::error_code& error );

    boost::asio::ip::tcp::socket m_oSocket;
    boost::array< char, 2048 > m_arrBuffer;
    ConnectionManager& m_oConnectionManager;
};

} // namespace server
} // namespace tcp_calc

#endif // TCPCALC_SERVER_CONNECTION_HPP
