//
// Created by Per Malmberg on 2016-06-09.
//


#pragma once

#include "StdOutput.h"

namespace lout {
namespace output {

class ColoredStdOutput : public StdOutput {
	ColoredStdOutput( std::shared_ptr<formatting::IFormatter> formatter );

	ColoredStdOutput( std::shared_ptr<formatting::IFormatter> formatter, std::ostream *fallbackStream );

	void LogActual( const loglevel::ILogLevel &level, const std::string &msg ) override;

	void LogWithCategoryActual( const loglevel::ILogLevel &level, const std::string &category,
								const std::string &msg ) override;
};

}
}