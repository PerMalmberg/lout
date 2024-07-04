// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include "ILogLevel.h"
#include <limits>

namespace lout::loglevel
{
	static constexpr int level_info = 10;
	static constexpr int level_warn = 20;
	static constexpr int level_error = 30;
	static constexpr int level_verbose = 40;
	static constexpr int level_debug = 50;

	///////////////////////////////////////////////////////////////////////////////
	//
	// Default log levels provided for convenience
	//
	///////////////////////////////////////////////////////////////////////////////

	class NoLogging : public ILogLevel
	{
	  public:
		NoLogging() : ILogLevel(std::numeric_limits<int>::min(), "NoLogging")
		{
		}
	};

	class Info : public ILogLevel
	{
	  public:
		Info() : ILogLevel(level_info, "Info")
		{
		}
	};

	class Warning : public ILogLevel
	{
	  public:
		Warning() : ILogLevel(level_warn, "Warning")
		{
		}
	};

	class Error : public ILogLevel
	{
	  public:
		Error() : ILogLevel(level_error, "Error")
		{
		}
	};

	class Verbose : public ILogLevel
	{
	  public:
		Verbose() : ILogLevel(level_verbose, "Verbose")
		{
		}
	};

	class Debug : public ILogLevel
	{
	  public:
		Debug() : ILogLevel(level_debug, "Debug")
		{
		}
	};

} // namespace lout::loglevel

