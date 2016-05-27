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

	// Logs the message using the provided category and log level
	void LogWithCategory(const loglevel::ILogLevel& level, const std::string& category, const std::string& msg) noexcept;

	uint64_t GetMessageCount() const
	{ return myMessageCount; }

protected:
	virtual void LogActual(const loglevel::ILogLevel& level, const std::string& msg) = 0;

	virtual void LogWithCategoryActual(const loglevel::ILogLevel& level, const std::string& category, const std::string& msg) = 0;

	void FallbackLog(const loglevel::ILogLevel& level, const std::string& category, const std::string& msg) noexcept;

private:
	uint64_t myMessageCount = 0;
	std::ostream* myFallbackErrorStream = nullptr;
};


}
}