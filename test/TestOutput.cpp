// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#include <memory>
#include <time.h>
#include "TestOutput.h"

TestOutput::TestOutput() :
		IOutput( std::make_shared<lout::formatting::DefaultFormatter>(),  nullptr ),
		myOutput()
{ }


void TestOutput::LogActual( const time_t& timestamp, const lout::loglevel::ILogLevel& level, const std::string& msg)
{
	std::stringstream s;
	s << "[" << GetTimestamp( timestamp ) << "][" << level << "]" << msg;
	myOutput.push_back( s.str() );
}

void TestOutput::LogWithCategoryActual( const time_t& timestamp, const lout::loglevel::ILogLevel& level, const std::string& category,
								   const std::string& msg)
{
	std::stringstream s;
	s << "[" << GetTimestamp( timestamp ) << "][" << level << "/" << category << "]" << msg;
	myOutput.push_back( s.str() );
}

std::string TestOutput::GetMsg(size_t ix)
{
	return myOutput.at( ix );
}

std::string
TestOutput::GetTimestamp( const time_t& timestamp ) const
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

