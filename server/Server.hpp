#pragma once
#ifndef TCPCALC_SERVER_SERVER_HPP
#define TCPCALC_SERVER_SERVER_HPP

#include "ConnectionFwd.hpp"
#include "ConnectionManager.hpp"

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/noncopyable.hpp>

#include <string>

namespace tcp_calc {
namespace server {

class Server: private boost::noncopyable
{
public:
    explicit Server( const std::string& address, const std::string& port );

    void run();

private:
    void startAccept();
    void handleAccept( const boost::system::error_code& error );
    void handleStop();

    boost::asio::io_context m_oIOContext;
    boost::asio::signal_set m_oSignalSet;
    boost::asio::ip::tcp::acceptor m_oAcceptor;
    ConnectionManager m_oConnectionManager;
    ConnectionPtr m_pConnection;
};

} // namespace server
} // namespace tcp_calc

#endif // TCPCALC_SERVER_SERVER_HPP
