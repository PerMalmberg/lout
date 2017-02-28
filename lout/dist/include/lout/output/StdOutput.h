// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#pragma once

#include "IOutput.h"
#include <fstream>

namespace lout {
namespace output {

class StdOutput : public IOutput
{
public:
	explicit StdOutput(std::shared_ptr<formatting::IFormatter> formatter);

	StdOutput( std::shared_ptr<formatting::IFormatter> formatter, std::ostream* fallbackStream );

	void LogActual( const time_t& timestamp, const loglevel::ILogLevel &level, const std::string &msg ) override;

	void LogWithCategoryActual( const time_t& timestamp, const loglevel::ILogLevel &level, const std::string &category,
								const std::string &msg ) override;
	void Flush();
};

}
}