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

	static Lout& Get()
	{
		static Lout instance;
		return instance;
	}

	void AddOutput(std::shared_ptr<output::ILoutOutput> output );

	void RemoveAllOutputs();

	void Log(const loglevel::ILogLevel& level, const std::string& msg);

	void LogWithTag(const loglevel::ILogLevel& level, const std::string& tag, const std::string& msg);

	void SetLevel(const loglevel::ILogLevel& newLevel);

	const loglevel::ILogLevel& GetLevel() const
	{ return myCurrentLevel; }

	void ActivateTag(const std::string& tag);

	size_t GetPrinterCount() const
	{ return myOutput.size(); }

	Lout& operator<<(const ILogLevel& level);


	Lout(const Lout&) = delete;
	Lout& operator=(Lout&) = delete;

private:
	loglevel::ILogLevel myCurrentLevel;
	std::vector<std::shared_ptr<output::ILoutOutput>> myOutput;
	std::set<std::string> myActiveTags;

	bool IsLevelActive(const loglevel::ILogLevel& level)
	{
		// We allow logging up to and including the currently set level.
		return level <= myCurrentLevel;
	}

	void FlushAll();
};

}