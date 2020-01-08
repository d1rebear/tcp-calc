#pragma once
#ifndef TCPCALC_CLIENT_CLIENT_HPP
#define TCPCALC_CLIENT_CLIENT_HPP

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/noncopyable.hpp>

#include <string>

namespace tcp_calc {
namespace client {

class Client: private boost::noncopyable
{
public:
    explicit Client( const std::string& address, const std::string& port );

    void requestCalculation( const std::string& expression );

private:
    boost::asio::io_context m_oIOContext;
    boost::asio::ip::tcp::socket m_oSocket;
};

} // namespace client
} // namespace tcp_calc

#endif // TCPCALC_CLIENT_CLIENT_HPP
