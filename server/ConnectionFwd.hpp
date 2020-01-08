#pragma once
#ifndef TCPCALC_SERVER_CONNECTIONFWD_HPP
#define TCPCALC_SERVER_CONNECTIONFWD_HPP

#include <boost/shared_ptr.hpp>

namespace tcp_calc {
namespace server {

class Connection;

typedef boost::shared_ptr< Connection > ConnectionPtr;

} // namespace server
} // namespace tcp_calc

#endif // TCPCALC_SERVER_CONNECTIONFWD_HPP
