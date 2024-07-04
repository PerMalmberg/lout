// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#if defined(_WIN32)
#define __STDC_WANT_LIB_EXT1__ 1 // For localtime_s
#endif

#include <array>
#include <chrono>
#include <cstring>
#include <ctime>
#include "output/DateTimeNameGiver.h"
#include <regex>
#include <sstream>

namespace lout::output
{

	DateTimeNameGiver::DateTimeNameGiver(const std::string& prefix) : myPrefix(prefix)
	{
		std::string expr = prefix + R"!!(\d{4}-\d{2}-\d{2}\ \d{6}\.log)!!";
		myMatcher = std::regex(expr);
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	std::string DateTimeNameGiver::GetNextName()
	{
		using std::chrono::system_clock;
		time_t now = system_clock::to_time_t(system_clock::now());

		std::stringstream formatted;
		formatted << myPrefix;

		tm local{};

		// TODO: provide constructor to choose between local time and UTC time. (gmtime_s)

		// std::localtime is not thread-safe so we have to use the _r or _s version.
#if defined(_WIN32)
		localtime_s(&local, &now);
#else
		localtime_r(&now, &local);
#endif
		std::array<char, 40> buff; // NOLINT
		std::fill(buff.begin(), buff.end(), 0);
		(void)strftime(buff.data(), buff.size() - 1, "%Y-%m-%d %H%M%S.log", &local);
		formatted << buff.data();

		return formatted.str();
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	bool DateTimeNameGiver::Matches(const std::string& fileName)
	{
		return std::regex_match(fileName, myMatcher);
	}

} // namespace lout::output
