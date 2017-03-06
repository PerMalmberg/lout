// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include <string>
#include <memory>
#include "lout/loglevel/ILogLevel.h"
#include "lout/formatting/IFormatter.h"
namespace lout {
namespace output {

///////////////////////////////////////////////////////////////////////////////
//
// Interface/base class for all Lout outputs.
// Note the noexcept on the methods - it is imperative that these functions
// do not leak exceptions. Leaking means std::terminate will be called.
//
///////////////////////////////////////////////////////////////////////////////
class IOutput
{
public:

	// The fallback parameter is as the name implies, a fallback in case the normal output is non-functioning.
	// You may pass in a nullptr if you don't want a fallback stream.
	IOutput( std::shared_ptr<formatting::IFormatter> formatter, std::ostream* fallback)
			: myFormatter( std::move( formatter ) ),
			myFallbackErrorStream( fallback )
	{
	}

	virtual ~IOutput()
	{
	}

	// Flushes the output, if applicable
	virtual void Flush() = 0;

	// Logs the message using the provided log level
	void Log( const time_t& timestamp, const loglevel::ILogLevel& level, const std::string& msg);

	// Logs the message using the provided category and log level
	void LogWithCategory( const time_t& timestamp, const loglevel::ILogLevel& level, const std::string& category, const std::string& msg);

	// Clear the log, if applicable for the output type.
	virtual void Clear() {}

	uint64_t GetMessageCount() const
	{ return myMessageCount; }

protected:
	virtual void LogActual( const time_t& timestamp, const loglevel::ILogLevel& level, const std::string& msg) = 0;

	virtual void LogWithCategoryActual( const time_t& timestamp, const loglevel::ILogLevel& level, const std::string& category, const std::string& msg) = 0;

	void FallbackLog( const time_t& timestamp, const loglevel::ILogLevel& level, const std::string& category, const std::string& msg);

	std::shared_ptr<formatting::IFormatter> myFormatter;
private:
	uint64_t myMessageCount = 0;
	std::ostream* myFallbackErrorStream = nullptr;
};


}
}