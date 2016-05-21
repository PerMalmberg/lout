//
// Created by Per Malmberg on 2016-05-06.
//

#pragma once

#include <memory>
#include <vector>
#include <exception>
#include <set>
#include "output/IOutput.h"
#include "loglevel/ILogLevel.h"

namespace lout {

class Lout
{
public:
	Lout();

	virtual ~Lout();

	// Resets the logger
	void Reset()
	{
		RemoveAllOutputs();
		SetThreshold( loglevel::ILogLevel( 0, "NoLevel" ) );
		myActiveTags.clear();
		myMandatoryTags.clear();
	}

	// Gets the singleton instance
	static Lout& Get()
	{
		static Lout instance;
		return instance;
	}

	// Adds an output to the logger
	void AddOutput(std::shared_ptr<output::IOutput> output);

	// Removes all outputs
	void RemoveAllOutputs();

	// Logs using the provided level
	void Log(const loglevel::ILogLevel& level, const std::string& msg);

	// Logs using the provided level and tag. Only tags that have been activated will be logged.
	void LogWithTag(const loglevel::ILogLevel& level, const std::string& tag, const std::string& msg);

	// Sets the log level threshold. No level higher than the one set will be allowed.
	void SetThreshold(const loglevel::ILogLevel& newLevel);

	// Gets the current threshold level
	const loglevel::ILogLevel& GetThreshold() const
	{
		return myCurrentThreshold;
	}

	// Activates a tag
	void ActivateTag(const std::string& tag);

	// Activates a mandatory tag, meaning that any log message with this tag will be logged regardless of level.
	void ActivateMandatoryTag(const std::string& tag);

	// Returns the number of outputs currently in use
	size_t GetPrinterCount() const
	{
		return myOutput.size();
	}

	// Sets the log level used for operator <<(const std::string&)
	Lout& operator<<(const loglevel::ILogLevel& level);

	// Logs the provided message using the log level set using operator<<(const loglevel::ILogLevel&)
	Lout& operator<<(const std::string& msg);

	Lout(const Lout&) = delete;

	Lout& operator=(Lout&) = delete;

private:
	loglevel::ILogLevel myCurrentThreshold;
	loglevel::ILogLevel myCurrentLoggingLevel;
	std::vector<std::shared_ptr<output::IOutput>> myOutput;
	std::set<std::string> myActiveTags;
	std::set<std::string> myMandatoryTags;

	bool IsLevelActive(const loglevel::ILogLevel& level)
	{
		// We allow logging up to and including the currently set level.
		return level <= myCurrentThreshold;
	}

	void FlushAll();
};

}