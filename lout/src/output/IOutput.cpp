//
// Created by Per Malmberg on  2016-05-21.
//

#include <string>
#include <loglevel/ILogLevel.h>
#include <output/IOutput.h>

namespace lout {
namespace output {

void
IOutput::Log(const loglevel::ILogLevel& level, const std::string& msg) noexcept
{
	try
	{
		++myMessageCount;
		LogActual( level, msg );
	}
	catch( std::exception& e )
	{
		FallbackLog( level, "", e.what() );
		FallbackLog( level, "", msg );
	}
	catch( ... )
	{
		FallbackLog( level, "", msg );
	}
}

void
IOutput::LogWithTag(const loglevel::ILogLevel& level, const std::string& tag, const std::string& msg) noexcept
{
	try
	{
		++myMessageCount;
		LogWithTagActual( level, tag, msg );
	}
	catch( std::exception& e )
	{
		FallbackLog( level, tag, e.what() );
		FallbackLog( level, tag, msg );
	}
	catch( ... )
	{
		FallbackLog( level, tag, msg );
	}
}

void
IOutput::FallbackLog(const loglevel::ILogLevel& level, const std::string& tag, const std::string& msg)
{
	try
	{
		if( myFallbackErrorStream && myFallbackErrorStream->good() )
		{
			*myFallbackErrorStream << "[" << level << "]";
			if( !tag.empty() )
			{
				*myFallbackErrorStream << "[" << tag << "]";
			}
			*myFallbackErrorStream << msg << std::endl;
		}
	}
	catch( ... )
	{
		// If we're having issues this deep down, we can't do anything about it.
	}
}


}
}
