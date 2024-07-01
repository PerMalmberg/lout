// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include "IFormatter.h"

namespace lout::formatting
{

	class DefaultFormatter : public IFormatter
	{
	  public:
		DefaultFormatter() = default;
		DefaultFormatter(const DefaultFormatter&) = delete;
		DefaultFormatter(DefaultFormatter&&) = delete;
		DefaultFormatter& operator=(const DefaultFormatter&) = delete;
		DefaultFormatter& operator=(DefaultFormatter&&) = delete;
		~DefaultFormatter() override = default;

		std::string Format(const time_t& timestamp, const loglevel::ILogLevel& level, const std::string& msg) override;
		std::string Format(const time_t& timestamp,
		                   const loglevel::ILogLevel& level,
		                   const std::string& category,
		                   const std::string& msg) override;

	  private:
		[[nodiscard]] std::string GetTimestamp(const time_t& timestamp) const;
	};

} // namespace lout::formatting
