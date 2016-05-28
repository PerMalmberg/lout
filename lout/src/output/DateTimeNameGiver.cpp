//
// Created by perma on 2016-05-25.
//

#include "output/DateTimeNameGiver.h"

//#define __STDC_WANT_LIB_EXT1__ 1 // For localtime_s
#include <time.h>
#include <cstring>

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
	time_t now;
	time( &now );

	tm localTime;
	// TODO: provide constructor to choose between local time and UTC time. (gmtime_s)
	localtime_s( &localTime, &now );

	char buff[40];
	std::memset( buff, 0, sizeof( buff ) );
	strftime( buff, sizeof( buff ) - 1, "%Y-%m-%d %H%M%S.log", &localTime );

	return myPrefix + std::string( buff );

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