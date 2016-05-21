//
// Created by Per Malmberg on 2016-05-08.
//

#pragma once

#include <string>
#include "loglevel/ILogLevel.h"
namespace lout {
namespace output {

///////////////////////////////////////////////////////////////////////////////
//
// Interface for all Lout output printers.
// Note the noexcept on the methods - it is imperative that these functions
// do not leak exceptions. Leaking means std::terminate will be called.
//
///////////////////////////////////////////////////////////////////////////////
class IOutput
{
public:

	IOutput(std::ostream* fallback)
			: myFallbackErrorStream( fallback )
	{
	}

	virtual ~IOutput()
	{
	}

	// Flushes the output, if applicable
	virtual void Flush() noexcept = 0;

	// Logs the message using the provided log level
	void Log(const loglevel::ILogLevel& level, const std::string& msg) noexcept;

	// Logs the message using the provided log level
	void LogWithTag(const loglevel::ILogLevel& level, const std::string& tag, const std::string& msg) noexcept;

	uint64_t GetMessageCount() const
	{ return myMessageCount; }

protected:
	virtual void LogActual(const loglevel::ILogLevel& level, const std::string& msg) = 0;

	virtual void LogWithTagActual(const loglevel::ILogLevel& level, const std::string& tag, const std::string& msg) = 0;

	void FallbackLog(const loglevel::ILogLevel& level, const std::string& tag, const std::string& msg);

private:
	uint64_t myMessageCount = 0;
	std::ostream* myFallbackErrorStream = nullptr;
};


}
}