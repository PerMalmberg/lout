// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#include <string>
#include <lout/loglevel/ILogLevel.h>
#include <lout/output/IOutput.h>

namespace lout {
namespace output {

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void
IOutput::Log( const time_t& timestamp, const loglevel::ILogLevel& level, const std::string& msg)
{
	// When we get here, we expect the level to be checked already - an output does not have knowledge about
	// categories so it has be be done by the callee.

	try
	{
		++myMessageCount;
		LogActual( timestamp, level, msg );
	}
	catch( std::exception& e )
	{
		FallbackLog( timestamp, level, "", e.what() );
		FallbackLog( timestamp, level, "", msg );
	}
	catch( ... )
	{
		FallbackLog( timestamp, level, "", msg );
	}
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void
IOutput::LogWithCategory( const time_t& timestamp, const loglevel::ILogLevel& level, const std::string& category, const std::string& msg)
{
	// When we get here, we expect the level to be checked already - an output does not have knowledge about
	// categories so it has be be done by the callee.

	try
	{
		++myMessageCount;
		LogWithCategoryActual( timestamp, level, category, msg );
	}
	catch( std::exception& e )
	{
		FallbackLog( timestamp, level, category, e.what() );
		FallbackLog( timestamp, level, category, msg );
	}
	catch( ... )
	{
		FallbackLog( timestamp, level, category, msg );
	}
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void
IOutput::FallbackLog( const time_t& timestamp, const loglevel::ILogLevel& level, const std::string& category, const std::string& msg)
{
	try
	{
		if( myFallbackErrorStream && myFallbackErrorStream->good() )
		{
			if( category.empty() ) {
				*myFallbackErrorStream << myFormatter->Format( timestamp, level, msg );
			}
			else {
				*myFallbackErrorStream << myFormatter->Format( timestamp, level, category, msg );
			}

			*myFallbackErrorStream << std::endl;
		}
	}
	catch( ... )
	{
		// If we're having issues this deep down, we can't do anything about it.
	}
}


}
}
