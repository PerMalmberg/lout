// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#if defined(_WIN32)
	#define __STDC_WANT_LIB_EXT1__ 1 // For localtime_s
#endif

#include <time.h>
#include <cstring>
#include <chrono>
#include <iomanip>
#include <lout/output/DateTimeNameGiver.h>

namespace lout {
namespace output {


DateTimeNameGiver::DateTimeNameGiver( const std::string& prefix)
		: myPrefix( prefix), myMatcher()
{
	std::string expr = prefix + R"!!(\d{4}-\d{2}-\d{2}\ \d{6}\.log)!!";
	myMatcher = std::regex( expr );
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
std::string DateTimeNameGiver::GetNextName() const
{
	auto now = std::chrono::system_clock::now();

	std::stringstream formatted;
	formatted << myPrefix;

	time_t time = std::chrono::system_clock::to_time_t( now );
	tm t;

	// TODO: provide constructor to choose between local time and UTC time. (gmtime_s)

	// std::localtime is not thread-safe so we have to use the _r or _s version.
#if defined(_WIN32)
	localtime_s( &t, &time );
#else
	localtime_r( &time, &t );
#endif
	char buff[40];
	std::memset( buff, 0, sizeof( buff ) );
	strftime( buff, sizeof( buff ) - 1, "%Y-%m-%d %H%M%S.log", &t );
	formatted << buff;

	return formatted.str();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool DateTimeNameGiver::Matches(const std::string& fileName)
{
	return std::regex_match( fileName, myMatcher );	
}

}
}