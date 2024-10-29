#pragma once
#ifndef TCPCALC_UTIL_TIMELOG_HPP
#define TCPCALC_UTIL_TIMELOG_HPP

#include <boost/chrono.hpp>
#include <string>

namespace tcp_calc {
namespace util {
namespace time {

using namespace boost::chrono;

class ScopedTimeLog
{
public:
    ScopedTimeLog( const std::string& name );
    ~ScopedTimeLog();

private:
    const std::string m_strName;
    const high_resolution_clock::time_point m_nStart;
};

inline ScopedTimeLog::ScopedTimeLog( const std::string& name ):
    m_strName( name ),
    m_nStart( high_resolution_clock::now() )
{
}

inline ScopedTimeLog::~ScopedTimeLog()
{
    std::printf( "[time log '%s']: %ld \u03BCs.\n",
                 m_strName.c_str(),
                 duration_cast< microseconds >(
                     high_resolution_clock::now()
                     - m_nStart ).count() );
}

} // namespace time
} // namespace util
} // namespace tcp_calc

#endif // TCPCALC_UTIL_TIMELOG_HPP
