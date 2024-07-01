// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include <lout/loglevel/ILogLevel.h>

namespace lout::formatting
{
	class IFormatter
	{
	  public:
		IFormatter() = default;
		IFormatter(const IFormatter&) = delete;
		IFormatter(IFormatter&&) = delete;
		IFormatter& operator=(const IFormatter&) = delete;
		IFormatter& operator=(IFormatter&&) = delete;
		virtual ~IFormatter() = default;

		virtual std::string Format(const time_t& timestamp,
		                           const loglevel::ILogLevel& level,
		                           const std::string& category,
		                           const std::string& msg) = 0;
		virtual std::string Format(const time_t& timestamp,
		                           const loglevel::ILogLevel& level,
		                           const std::string& msg) = 0;
	};
} // namespace lout::formatting
