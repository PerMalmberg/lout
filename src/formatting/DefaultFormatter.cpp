// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#include "formatting/DefaultFormatter.h"
#include "loglevel/ILogLevel.h"
#include <array>
#include <ctime>
#include <sstream>
#include <string>

namespace lout::formatting
{

	std::string DefaultFormatter::Format(const time_t& timestamp,
	                                     const lout::loglevel::ILogLevel& level,
	                                     const std::string& msg)
	{
		std::stringstream sstr;
		sstr << "[" << GetTimestamp(timestamp) << "][" << level << "]" << msg;
		return sstr.str();
	}

	std::string DefaultFormatter::Format(const time_t& timestamp,
	                                     const lout::loglevel::ILogLevel& level,
	                                     const std::string& category,
	                                     const std::string& msg)
	{
		std::stringstream sstr;
		sstr << "[" << GetTimestamp(timestamp) << "][" << level << "/" << category << "]" << msg;
		return sstr.str();
	}

	std::string DefaultFormatter::GetTimestamp(const time_t& timestamp)
	{
		tm now{};
#ifdef _WIN32
		localtime_s(&now, &timestamp);
#else
		localtime_r(&timestamp, &now);
#endif
		const int buffSize = 50;
		const int dateSize = 20;
		std::array<char, buffSize> buff{};
		(void)strftime(buff.data(), dateSize, "%Y-%m-%d %H:%M:%S", &now);
		return {buff.data()};
	}

} // namespace lout::formatting
