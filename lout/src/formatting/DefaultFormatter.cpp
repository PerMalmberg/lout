// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#include <lout/formatting/DefaultFormatter.h>
#include <sstream>
#include <time.h>

namespace lout {
namespace formatting {

std::string
DefaultFormatter::Format( const time_t& timestamp, const lout::loglevel::ILogLevel &level, const std::string &msg)
{
	std::stringstream s;
	s << "[" << GetTimestamp( timestamp ) << "][" << level << "]" << msg;
	return s.str();
}

std::string
DefaultFormatter::Format( const time_t& timestamp, const lout::loglevel::ILogLevel &level, const std::string &category, const std::string &msg)
{	
	std::stringstream s;
	s << "[" << GetTimestamp( timestamp ) << "][" << level << "/" << category << "]" << msg;
	return s.str();
}

std::string
DefaultFormatter::GetTimestamp( const time_t& timestamp ) const
{
	tm t;
#ifdef _WIN32
	localtime_s( &t, &timestamp );
#else
	localtime_r( &timestamp, &t );
#endif

	char buff[50];
	strftime( buff, 20, "%Y-%m-%d %H:%M:%S", &t );
	return std::string( buff );
}

}
}