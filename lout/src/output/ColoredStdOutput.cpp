// Copyright (c) 2016 Per Malmberg
// Licensed under MIT, see LICENSE file.
// Give credit where credit is due.

#include "output/ColoredStdOutput.h"
#include "rlutil/rlutil.h"

namespace lout {
namespace output {

using namespace rlutil;

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
ColoredStdOutput::ColoredStdOutput( std::shared_ptr<formatting::IFormatter> formatter )
		: StdOutput( formatter )
{
	saveDefaultColor();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
ColoredStdOutput::ColoredStdOutput( std::shared_ptr<formatting::IFormatter> formatter, std::ostream *fallbackStream )
		: StdOutput( formatter, fallbackStream )
{
	saveDefaultColor();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void ColoredStdOutput::SetLevelColor( const loglevel::ILogLevel& level, int color )
{
	levelToColor.emplace(level.GetLevel(), color);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool ColoredStdOutput::SetColorForLevel( const loglevel::ILogLevel &level )
{
	auto color = levelToColor.find(level.GetLevel());
	bool hasColor = color != levelToColor.end();

	if( hasColor ) {
		setColor( (*color).second );
	}

	return hasColor;
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void ColoredStdOutput::LogActual( const loglevel::ILogLevel &level, const std::string &msg )
{
	bool hadColor = SetColorForLevel( level );

	StdOutput::LogActual( level, msg );

	if( hadColor ) {
		resetColor();
	}

}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void ColoredStdOutput::LogWithCategoryActual( const loglevel::ILogLevel &level, const std::string &category,
											  const std::string &msg )
{
	bool hadColor = SetColorForLevel( level );

	StdOutput::LogWithCategoryActual( level, category, msg );

	if( hadColor ) {
		resetColor();
	}
}

}
}