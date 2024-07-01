// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#include "TestOutput.h"
#include <ctime>
#include <memory>

TestOutput::TestOutput() : IOutput(std::make_shared<lout::formatting::DefaultFormatter>(), nullptr)
{
}

void TestOutput::LogActual(const time_t& timestamp, const lout::loglevel::ILogLevel& level, const std::string& msg)
{
	std::stringstream sstr;
	sstr << "[" << GetTimestamp(timestamp) << "][" << level << "]" << msg;
	myOutput.push_back(sstr.str());
}

void TestOutput::LogWithCategoryActual(const time_t& timestamp,
                                       const lout::loglevel::ILogLevel& level,
                                       const std::string& category,
                                       const std::string& msg)
{
	std::stringstream sstr;
	sstr << "[" << GetTimestamp(timestamp) << "][" << level << "/" << category << "]" << msg;
	myOutput.push_back(sstr.str());
}

std::string TestOutput::GetMsg(size_t ix)
{
	return myOutput.at(ix);
}

std::string TestOutput::GetTimestamp(const time_t& timestamp) const
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
