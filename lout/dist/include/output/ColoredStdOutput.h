//
// Created by Per Malmberg on 2016-06-09.
//


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
	void LogActual( const loglevel::ILogLevel &level, const std::string &msg ) override;

	void LogWithCategoryActual( const loglevel::ILogLevel &level, const std::string &category,
								const std::string &msg ) override;

private:

	bool SetColorForLevel( const loglevel::ILogLevel &level );

	std::unordered_map<int, int> levelToColor;
};

}
}