// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include "IRollingFileName.h"
#include <regex>
#include <string>

namespace lout::output
{
	class DateTimeNameGiver : public IRollingFileName
	{
	  public:
		explicit DateTimeNameGiver(const std::string& prefix);

		// Returns the next log name to use
		std::string GetNextName() override;

		bool Matches(const std::string& fileName) override;

	  private:
		std::string myPrefix;
		std::regex myMatcher;
	};
} // namespace lout::output
