// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include "formatting/DefaultFormatter.h"
#include "output/IOutput.h"
#include <vector>

class TestOutput : public lout::output::IOutput
{
  public:
	TestOutput();

	void Flush() noexcept override
	{
	}

	void LogActual(const time_t& timestamp, const lout::loglevel::ILogLevel& level, const std::string& msg) override;

	void LogWithCategoryActual(const time_t& timestamp,
	                           const lout::loglevel::ILogLevel& level,
	                           const std::string& category,
	                           const std::string& msg) override;

	std::string GetMsg(size_t ix);

  private:
	std::vector<std::string> myOutput;

	static std::string GetTimestamp(const time_t& timestamp);
};
