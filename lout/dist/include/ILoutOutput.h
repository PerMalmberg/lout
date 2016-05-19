//
// Created by Per Malmberg on 2016-05-08.
//

#pragma once

#include <string>

namespace com {
namespace codezeal {
namespace logging {

///////////////////////////////////////////////////////////////////////////////
//
// Interface for all Lout output printers.
// Note the noexcept on the methods - it is imperative that these functions
// do not leak exceptions. Leaking means std::terminate will be called.
//
///////////////////////////////////////////////////////////////////////////////
template<typename TLogLevel>
class ILoutOutput
{
public:

	ILoutOutput(std::ostream* fallback)
			: myFallbackErrorStream( fallback )
	{
	}

	virtual ~ILoutOutput()
	{
	}

	// Flushes the output, if applicable
	virtual void Flush() noexcept = 0;

	// Logs the message using the provided log level
	void Log(TLogLevel level, const std::string& msg) noexcept;

	// Logs the message using the provided log level
	void LogWithTag(TLogLevel level, const std::string& tag, const std::string& msg) noexcept;

	uint64_t GetMessageCount() const
	{ return myMessageCount; }

protected:
	virtual void LogActual(TLogLevel level, const std::string& msg) = 0;

	virtual void LogWithTagActual(TLogLevel level, const std::string& tag, const std::string& msg) = 0;

	void FallbackLog(TLogLevel level, const std::string& tag, const std::string& msg);

private:
	uint64_t myMessageCount = 0;
	std::ostream* myFallbackErrorStream = nullptr;
};

template<typename TLogLevel>
void
ILoutOutput<TLogLevel>::Log(TLogLevel level, const std::string& msg) noexcept
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

template<typename TLogLevel>
void
ILoutOutput<TLogLevel>::LogWithTag(TLogLevel level, const std::string& tag, const std::string& msg) noexcept
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

template<typename TLogLevel>
void
ILoutOutput<TLogLevel>::FallbackLog(TLogLevel level, const std::string& tag, const std::string& msg)
{
	try
	{
		if( myFallbackErrorStream && myFallbackErrorStream->good() )
		{
			*myFallbackErrorStream << "[" << static_cast<int>( level) << "]";
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
}