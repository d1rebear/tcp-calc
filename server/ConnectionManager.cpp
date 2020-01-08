#include "ConnectionManager.hpp"

#include "Connection.hpp"

#include <boost/bind.hpp>

#include <algorithm>

namespace tcp_calc {
namespace server {

void ConnectionManager::start( ConnectionPtr connection )
{
    m_oConnections.insert( connection );
    connection->start();
}

void ConnectionManager::stop( ConnectionPtr connection )
{
    m_oConnections.erase( connection );
    connection->stop();
}

void ConnectionManager::stopAll()
{
    std::for_each( m_oConnections.begin(), m_oConnections.end(),
                   boost::bind( &Connection::stop, _1 ) );
    m_oConnections.clear();
}

} // namespace server
} // namespace tcp_calc
