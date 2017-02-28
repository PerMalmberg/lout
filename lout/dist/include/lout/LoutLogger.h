// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include <regex>
#include <sstream>
#include "Lout.h"
#include "Flush.h"
#include "lout/item/ILogItem.h"
#include "lout/output/FileOutput.h"

namespace lout {

// Helper class used to allow chaining of log data via operator << without creating a new log line for each argument.
// Also guarantees that messages are logged as a single line in multi threaded environments.
class LoutLogger
{
public:
	LoutLogger();
			

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

	LoutLogger& operator<<( std::shared_ptr<lout::item::ILogItem> item );

	LoutLogger& operator<<(const lout::Flush&);

	void AppendMsg(const std::string& msg);

	void SetLevel(const loglevel::ILogLevel& level);

private:
	void Flush();

	std::vector<std::shared_ptr<lout::item::ILogItem>> myItems;
	std::stringstream myCurrentMessage;
	loglevel::ILogLevel myCurrentLevel;
	std::string myCategory;
	time_t timestamp;
};


}