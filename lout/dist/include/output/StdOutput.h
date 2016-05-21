//
// Created by Per Malmberg on 2016-05-17.
//

#pragma once

#include "ILoutOutput.h"
#include <fstream>

namespace lout {
namespace output {

class StdOutPrinter : public ILoutOutput
{
public:
	StdOutPrinter();
	void LogActual(const loglevel::ILogLevel& level, const std::string& msg) override;
	void LogWithTagActual(const loglevel::ILogLevel& level, const std::string& tag, const std::string& msg) override;
	void Flush() noexcept override;
};

}
}