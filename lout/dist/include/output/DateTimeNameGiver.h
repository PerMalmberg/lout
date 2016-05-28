//
// Created by Per Malmberg on 2016-05-25.
//

#pragma once

#include <string>
#include <regex>
#include "output/IRollingFileName.h"

namespace lout {
namespace output {

class DateTimeNameGiver : public IRollingFileName
{
public:
	DateTimeNameGiver(const std::string& prefix);

	// Returns the next log name to use
	std::string GetNextName() const override;

	bool Matches(const std::string& fileName) override;

private:
	std::string myPrefix;
	std::regex myMatcher;
};

}
}