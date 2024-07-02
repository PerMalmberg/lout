// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#include <ctime>
#include <iostream>
#include "formatting/IFormatter.h"
#include "loglevel/ILogLevel.h"
#include "output/IOutput.h"
#include "output/StdOutput.h"
#include <memory>
#include <string>
#include <utility>

namespace lout::output
{
	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	StdOutput::StdOutput(std::shared_ptr<formatting::IFormatter> formatter) : IOutput(std::move(formatter), &std::cerr)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	StdOutput::StdOutput(std::shared_ptr<formatting::IFormatter> formatter, std::ostream* fallbackStream)
	    : IOutput(std::move(formatter), fallbackStream)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void StdOutput::LogActual(const time_t& timestamp, const loglevel::ILogLevel& level, const std::string& msg)
	{
		std::cout << myFormatter->Format(timestamp, level, msg) << std::endl;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void StdOutput::LogWithCategoryActual(const time_t& timestamp,
	                                      const loglevel::ILogLevel& level,
	                                      const std::string& category,
	                                      const std::string& msg)
	{
		std::cout << myFormatter->Format(timestamp, level, category, msg) << std::endl;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void StdOutput::Flush() noexcept
	{
		std::cout.flush();
	}
} // namespace lout::output

