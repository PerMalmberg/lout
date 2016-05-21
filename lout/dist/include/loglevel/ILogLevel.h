//
// Created by Per Malmberg on 2016-05-21.
//

#pragma once

#include <ostream>

namespace lout {
namespace loglevel {

///////////////////////////////////////////////////////////////////////////////
//
// Base class for log levels used by Lout. Inherit from this to provide custom levels
//
///////////////////////////////////////////////////////////////////////////////
class ILogLevel
{
public:
	ILogLevel(int level, const std::string levelAsText) : myLevel( level ), myLevelAsText( levelAsText )
	{ }

	bool operator<=(const ILogLevel& rhs) const
	{
		return myLevel <= rhs.myLevel;
	}

	bool operator==(const ILogLevel& rhs) const
	{
		return myLevel == rhs.GetLevel();
	}

	int GetLevel() const
	{
		return myLevel;
	}

	const std::string& GetText() const
	{
		return myLevelAsText;
	}

private:
	int myLevel;
	std::string myLevelAsText;
};

}
}

std::ostream& operator<<(std::ostream& stream, const lout::loglevel::ILogLevel& );