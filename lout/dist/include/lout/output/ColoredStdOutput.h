// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.


#pragma once

#include "StdOutput.h"
#include <unordered_map>

namespace lout {
namespace output {

class ColoredStdOutput : public StdOutput {
public:
	ColoredStdOutput( std::shared_ptr<formatting::IFormatter> formatter );

	ColoredStdOutput( std::shared_ptr<formatting::IFormatter> formatter, std::ostream *fallbackStream );

	void SetLevelColor( const loglevel::ILogLevel& level, int color );

protected:
	void LogActual( const time_t& timestamp, const loglevel::ILogLevel &level, const std::string &msg ) override;

	void LogWithCategoryActual( const time_t& timestamp, const loglevel::ILogLevel &level, const std::string &category,
								const std::string &msg ) override;

private:

	bool SetColorForLevel( const loglevel::ILogLevel &level );

	std::unordered_map<int, int> levelToColor;
};

}
}