// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include "Flush.h"
#include "item/ILogItem.h"
#include "loglevel/ILogLevel.h"
#include <memory>
#include <sstream>
#include <vector>

namespace lout
{

	// Helper class used to allow chaining of log data via operator << without creating a new log line for each
	// argument. Also guarantees that messages are logged as a single line in multi threaded environments.
	class LoutLogger
	{
	  public:
		LoutLogger();

		LoutLogger(const LoutLogger&) = delete;
		LoutLogger(LoutLogger&&) = delete;
		LoutLogger& operator=(const LoutLogger&) = delete;
		LoutLogger& operator=(LoutLogger&&) = delete;

		explicit LoutLogger(const std::string& category) : LoutLogger()
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

#if !__x86_64__ || __APPLE__
		// Don't compile this on 64 bit platforms since it is the same as uint64_t
		LoutLogger& operator<<(unsigned long value);
#endif

		LoutLogger& operator<<(double value);

		LoutLogger& operator<<(long double value);

		LoutLogger& operator<<(float value);

		LoutLogger& operator<<(const std::shared_ptr<lout::item::ILogItem>& item);

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
} // namespace lout
