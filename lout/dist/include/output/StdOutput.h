//
// Created by Per Malmberg on 2016-05-17.
//

#pragma once

#include "IOutput.h"
#include <fstream>

namespace lout {
namespace output {

class StdOutPrinter : public IOutput
{
public:
	StdOutPrinter();

	StdOutPrinter( std::ostream* fallbackStream );

	void LogActual(const loglevel::ILogLevel& level, const std::string& msg) override;
	void LogWithCategoryActual(const loglevel::ILogLevel& level, const std::string& category, const std::string& msg) override;
	void Flush() noexcept override;
};

}
}