//
// Created by perma on 2016-05-08.
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

private:
	uint64_t myMessageCount = 0;
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
		// TODO: Provide IFC to where these errors are to be logged
	}
	catch( ... )
	{
		// TODO: Provide IFC to where these errors are to be logged
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
		// TODO: Provide IFC to where these errors are to be logged
	}
	catch( ... )
	{
		// TODO: Provide IFC to where these errors are to be logged
	}
}

}
}
}