//
// Created by Per Malmberg on 2016-05-17.
//

#pragma once

#include "IOutput.h"
#include <fstream>

namespace lout {
namespace output {

class StdOutput : public IOutput
{
public:
	StdOutput(std::shared_ptr<formatting::IFormatter> formatter);

	StdOutput( std::shared_ptr<formatting::IFormatter> formatter, std::ostream* fallbackStream );

	void LogActual(const loglevel::ILogLevel& level, const std::string& msg) override;
	void LogWithCategoryActual(const loglevel::ILogLevel& level, const std::string& category, const std::string& msg) override;
	void Flush() noexcept override;
};

}
}