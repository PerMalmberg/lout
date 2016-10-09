// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include <regex>
#include <sstream>
#include "Lout.h"
#include "Flush.h"
#include "output/FileOutput.h"

namespace lout {

// Helper class used to allow chaining of log data via operator << without creating a new log line for each argument.
// Also guarantees that messages are logged as a single line in multi threaded environments.
class LoutLogger
{
public:
	LoutLogger()
			: myItems(), myCurrentMessage(), myCurrentLevel( std::numeric_limits<int>::max(), "NoLevel" ), myCategory()
	{ }

	LoutLogger(const std::string& category)
			:  LoutLogger()
	{
		myCategory = category;
	}

	~LoutLogger();

	LoutLogger& operator<<(const loglevel::ILogLevel& level);

	LoutLogger& operator<<(const std::string& msg);

	LoutLogger& operator<<(int8_t value);

	LoutLogger& operator<<(int16_t value);

	LoutLogger& operator<<(int32_t value);

	LoutLogger& operator<<(int64_t value);

	LoutLogger& operator<<(uint8_t value);

	LoutLogger& operator<<(uint16_t value);

	LoutLogger& operator<<(uint32_t value);

	LoutLogger& operator<<(uint64_t value);

	LoutLogger& operator<<(double value);

	LoutLogger& operator<<(long double value);

	LoutLogger& operator<<(float value);

	LoutLogger& operator<<(const lout::Flush&);

	void AppendMsg(const std::string msg);

	void SetLevel(const loglevel::ILogLevel& level);

private:

	class LogItem
	{
	public:
		virtual void Log(LoutLogger& l) = 0;
	};

	class StringItem : public LogItem
	{
	public:
		StringItem(const std::string& msg) : myMsg( msg )
		{ }

		void Log(LoutLogger& l) override;

	private:
		std::string myMsg;
	};

	class LevelItem : public LogItem
	{
	public:
		LevelItem(const loglevel::ILogLevel& level) : myLevel( level )
		{ }

		void Log(LoutLogger& l) override;

	private:
		loglevel::ILogLevel myLevel;
	};

	void Flush();

	std::vector<std::shared_ptr<LogItem>> myItems;
	std::stringstream myCurrentMessage;
	loglevel::ILogLevel myCurrentLevel;
	std::string myCategory;
};


}