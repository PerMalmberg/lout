//
// Created by Per Malmberg on  2016-05-21.
//

#include <string>
#include <loglevel/ILogLevel.h>
#include <output/IOutput.h>

namespace lout {
namespace output {

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void
IOutput::LogWithCategory(const loglevel::ILogLevel& level, const std::string& category, const std::string& msg) noexcept
{
	try
	{
		++myMessageCount;
		LogWithCategoryActual( level, category, msg );
	}
	catch( std::exception& e )
	{
		FallbackLog( level, category, e.what() );
		FallbackLog( level, category, msg );
	}
	catch( ... )
	{
		FallbackLog( level, category, msg );
	}
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void
IOutput::FallbackLog(const loglevel::ILogLevel& level, const std::string& category, const std::string& msg) noexcept
{
	try
	{
		if( myFallbackErrorStream && myFallbackErrorStream->good() )
		{
			if( category.empty() ) {
				*myFallbackErrorStream << myFormatter->Format(level, msg );
			}
			else {
				*myFallbackErrorStream << myFormatter->Format(level, category, msg );
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
