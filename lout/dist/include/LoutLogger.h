//
// Created by Per Malmberg on 2016-05-22.
//

#pragma once

#include "Lout.h"
#include <regex>

namespace lout {

// Class used to allow chaining of log data via operator << without creating a new log line for each argument.
class LoutLogger
{
public:
	LoutLogger() : myItems(), myCurrentMessage(), myCurrentLevel(std::numeric_limits<int>::max(), "NoLevel")
	{ }

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

	void AppendMsg( const std::string msg);
	void SetLevel( const loglevel::ILogLevel& level);

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
};


}