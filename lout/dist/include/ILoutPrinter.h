//
// Created by perma on 2016-05-08.
//

#pragma once

namespace com {
namespace codezeal {
namespace logging {

template<typename TLogLevel>
class ILoutPrinter
{
public:
	virtual ~ILoutPrinter()
	{ }

	// Flushes the output, if applicable
	virtual void Flush() = 0;

	// Logs the message using the provided log level
	void Log(TLogLevel level, const std::string& msg);

	// Logs the message using the provided log level
	void LogWithTag(TLogLevel level, const std::string& tag, const std::string& msg);

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
ILoutPrinter<TLogLevel>::Log(TLogLevel level, const std::string& msg)
{
	++myMessageCount;
	LogActual( level, msg );
}

template<typename TLogLevel>
void
ILoutPrinter<TLogLevel>::LogWithTag(TLogLevel level, const std::string& tag, const std::string& msg)
{
	++myMessageCount;
	LogWithTagActual( level, tag, msg );
}

}
}
}