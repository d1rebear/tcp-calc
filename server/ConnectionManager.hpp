#pragma once
#ifndef TCPCALC_SERVER_CONNECTIONMANAGER_HPP
#define TCPCALC_SERVER_CONNECTIONMANAGER_HPP

#include "ConnectionFwd.hpp"

#include <boost/noncopyable.hpp>

#include <set>

namespace tcp_calc {
namespace server {

class ConnectionManager: private boost::noncopyable
{
public:
    void start( ConnectionPtr connection );
    void stop( ConnectionPtr connection );
    void stopAll();

private:
    std::set< ConnectionPtr > m_oConnections;
};

} // namespace server
} // namespace tcp_calc

#endif // TCPCALC_SERVER_CONNECTIONMANAGER_HPP
